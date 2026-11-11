#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "backend.h"

int regtable[NUMREG];  // reg[i] contains current number of uses of register i
int vartable[NUMVAR];  // var[i] contains register to which var is assigned

void init_regtable(void) 
{
    for (int i = 0; i < NUMREG; i++)
        regtable[i] = 0;
}

void init_vartable(void)
{
    for (int i = 0; i < NUMVAR; i++)
        vartable[i] = -1;
}
    
int reuse_reg(int reg)
{
    if (regtable[reg] == 1)
        return(1);
    if (regtable[reg] > 1)
        return(0);
    printf("Error: called reuse_reg on unused register\n");
    return(-1);  // shouldn't happen
}

int assign_reg(int var)
{ 
        if ((var != -1) && (vartable[var] != -1)) {
            regtable[vartable[var]]++; // variable is already assigned a register
            return(vartable[var]);
        } else {
            for (int i = 5; i < NUMREG; i++)     // find unassigned register
                if (regtable[i] == 0) {
                    regtable[i]++;
                    if (var != -1) {
                        vartable[var] = i;
                    }
                    return(i);;
            }
            return(-1);  // out of registers
        }
}  

int release_reg(int reg)
{
    if (regtable[reg] > 0) {
        regtable[reg]--;
        return(0);
    } else
        return(-1);
}    

void printregtable(void)
{
    printf("register table -- number of uses of each register\n");
    for (int i = 0; i < NUMREG; i++)
      if (regtable[i])
        printf("register: x%d, uses: %d\n", i, regtable[i]);
}

void printvartable(void)
{
    printf("variable table -- register to which var is assigned\n");
    for (int i = 0; i < NUMVAR; i++)
      if (vartable[i] != -1)
        printf("variable: %c, register: x%d\n", 'a'+i, vartable[i]);
}

int power_of_two(unsigned int n)
{
    int log = 0;

    if (n == 0 || (n & (n - 1)) != 0)   
        return 0;
    while (n > 1) {
        n >>= 1;
        log++;
    }
    return log;
}
//actual risc-v part 

static int fits_in_12(int n)
{
    return (n >= -2048 && n <= 2047);
}

static int alloc_reg(void) //allocate a new register
{
    int r = assign_reg(-1);
    if (r == -1) {
        printf("Error: out of registers\n");
        exit(-1);
    }
    return r;
}

static void make_const(struct node *root, int v)//for handling large constants
{
    root->type = CONST;
    root->data = v;
    root->left = root->right = NULL;
}

static void load_const(int reg, int v)
{
    if (fits_in_12(v)) {
        printf("addi x%d, x0, %d\n", reg, v);
    } else {
        uint32_t u = (uint32_t) v;
        uint32_t hi = ((u + 0x800u) >> 12) & 0xFFFFFu;   // +0x800 compensates for sign-extended low part
        int32_t  lo = (int32_t) (u - (hi << 12));         // always in [-2048, 2047]
        printf("lui  x%d, %u\n", reg, (unsigned) hi);
        if (lo != 0)
            printf("addi x%d, x%d, %d\n", reg, reg, lo);
    }
}

static void emit_r(const char *name, int rd, int rs1, int rs2)
{
    printf("%s  x%d, x%d, x%d\n", name, rd, rs1, rs2);
}

static void emit_i(const char *name, int rd, int rs1, int imm)
{
    if (strcmp(name, "srai") == 0)       // spacing matches the provided output2b.txt
        printf("%s  x%d, x%d, %d\n", name, rd, rs1, imm);
    else
        printf("%s x%d, x%d, %d\n", name, rd, rs1, imm);
}

static int is_commutative(int op)
{
    return op == ADD || op == MUL || op == AND || op == OR || op == XOR;
}

static int fold(int op, int a, int b, int *res)
{
    uint32_t ua = (uint32_t) a, ub = (uint32_t) b;
    switch (op) {
        case ADD: *res = (int)(ua + ub); break;
        case SUB: *res = (int)(ua - ub); break;
        case MUL: *res = (int)(ua * ub); break;
        case DIV: if (b == 0 || (a == INT32_MIN && b == -1)) return 0;
                  *res = a / b; break;
        case AND: *res = a & b; break;
        case OR:  *res = a | b; break;
        case XOR: *res = a ^ b; break;
        case SLL: *res = (int)(ua << (ub & 31)); break;
        case SRL: *res = (int)(ua >> (ub & 31)); break;
        default:  return 0;
    }
    return 1;
}



//gets the registesr

static const char *imm_form(int op, int imm, int *immout)
{
    int lg;
    *immout = imm;
    switch (op) {
        case ADD: return fits12(imm) ? "addi" : NULL;
        case SUB: if (imm != INT32_MIN && fits12(-imm)) { *immout = -imm; return "addi"; }
                  return NULL;
        case AND: return fits12(imm) ? "andi" : NULL;
        case OR:  return fits12(imm) ? "ori"  : NULL;
        case XOR: return fits12(imm) ? "xori" : NULL;
        case SLL: return (imm >= 0 && imm < 32) ? "slli" : NULL;
        case SRL: return (imm >= 0 && imm < 32) ? "srli" : NULL;
        case MUL: if (imm > 0 && (lg = power_of_two((unsigned) imm)) > 0) {   // strength reduction
                      *immout = lg; return "slli";
                  }
                  return NULL;
        case DIV: if (imm > 0 && (lg = power_of_two((unsigned) imm)) > 0) {
                      *immout = lg; return "srai";
                  }
                  return NULL;
    }
    return NULL;
}

static void gen_reg_reg(struct node *root, struct node *left, struct node *right)
{
    int destreg;
    char instr[20];

    if (reuse_reg(left->data) == 1) {
        destreg = left->data;
        release_reg(right->data);
    } else if (reuse_reg(right->data) == 1) {
        destreg = right->data;
        release_reg(left->data);
    } else {
        destreg = alloc_reg();
        release_reg(left->data);
        release_reg(right->data);
    }
    sprintf(instr, "%s  x%d, x%d, x%d", optable[root->data].instr, destreg,
            left->data, right->data);
    printf("%s\n", instr);
    free(left);
    free(right);
    root->type = REG;
    root->data = destreg;
}

static void gen_reg_const(struct node *root, struct node *left, struct node *right)
{
    int op = root->data, imm = right->data, immv, rd, reused;
    const char *form;

    if ((op == MUL || op == DIV) && imm == 1) {
        root->type = REG; root->data = left->data;
        free(left); free(right);
        return;
    }
    if (op == MUL && imm == 0) {
        release_reg(left->data);
        free(left); free(right);
        make_const(root, 0);
        return;
    }
    if (op == DIV && imm == 0) {
        printf("Error: division by zero\n");
        exit(-1);
    }

    reused = (reuse_reg(left->data) == 1);
    rd = reused ? left->data : alloc_reg();

    form = imm_form(op, imm, &immv);
    if (form) {
        emit_i(form, rd, left->data, immv);
    } else {                                             // constant needs a register
        int tmp = alloc_reg();
        load_const(tmp, imm);
        emit_r(optable[op].instr, rd, left->data, tmp);
        release_reg(tmp);
    }
    if (!reused)
        release_reg(left->data);
    free(left); free(right);
    root->type = REG;
    root->data = rd;
}

static void gen_const_reg(struct node *root, struct node *left, struct node *right)
{
    int op = root->data, rd, tmp, reused;

    reused = (reuse_reg(right->data) == 1);
    rd = reused ? right->data : alloc_reg();
    tmp = alloc_reg();
    load_const(tmp, left->data);
    emit_r(optable[op].instr, rd, tmp, right->data);
    release_reg(tmp);
    if (!reused)
        release_reg(right->data);
    free(left); free(right);
    root->type = REG;
    root->data = rd;
}


static void gen_binary(struct node *root, struct node *left, struct node *right)
{
    int res;

    if (left->type == CONST && right->type == CONST) {   // constant folding
        if (!fold(root->data, left->data, right->data, &res)) {
            printf("Error: division by zero\n");
            exit(-1);
        }
        free(left); free(right);
        make_const(root, res);
    } else if (left->type == REG && right->type == REG) {
        gen_reg_reg(root, left, right);
    } else if (left->type == REG && right->type == CONST) {
        gen_reg_const(root, left, right);
    } else if (left->type == CONST && right->type == REG) {
        if (is_commutative(root->data))
            gen_reg_const(root, right, left);            // swap so the constant is on the right
        else
            gen_const_reg(root, left, right);
    }
}



static void gen_unary(struct node *root, struct node *left)
{
    int destreg;
    char instr[20];

    if (left->type == CONST) {                           // fold
        int v = left->data;
        free(left);
        make_const(root, root->data == UMINUS ? (int)(0u - (uint32_t) v) : ~v);
    } else if (left->type == REG) {
        if (reuse_reg(left->data) == 1) {
            destreg = left->data;
        } else {
            destreg = alloc_reg();
            release_reg(left->data);
        }
        if (root->data == UMINUS)
            sprintf(instr, "sub  x%d, x0, x%d", destreg, left->data);
        else
            sprintf(instr, "xori x%d, x%d, -1", destreg, left->data);
        printf("%s\n", instr);
        free(left);
        root->type = REG;
        root->data = destreg;
    }
}

struct node *generate_code(struct node *root) //split ito a bunch of helper methods because I suck at reading long blocks
{
    struct node *left = NULL, *right = NULL;

    if (root) {
        if (root->left)
            left = generate_code(root->left);
        if (root->right)
            right = generate_code(root->right);
        if (root->type == REG || root->type == CONST)
            return(root);
        else if (root->type == VAR) {
            root->type = REG;
            root->data = vartable[root->data];
            return(root);
        } else if (root->type == BINARYOP)
            gen_binary(root, left, right);
        else if (root->type == UNARYOP)
            gen_unary(root, left);
    }
    return(root);
}

