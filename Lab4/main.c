#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "backend.h"

int get_str(char s[], int lim)
{
    int c, i;
    
    i = 0;
    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    s[i] = '\0';
    return i;
}
  
void postorder(struct node *root)
{
    if (root != NULL) {
        postorder(root->left);  //recursively go left
        postorder(root->right); //recursively go right
        if (root->type == VAR)  //variable
            printf("%c", root->data + 'a'); 
        else if (root->type == CONST) //prints value
            printf("%d", root->data);
        else
            printf("%s", optable[root->data].symbol);
    }
}


int main()
{
    char expr1[MAXEXPRLENGTH];
    struct node *root;

    while (get_str(expr1, MAXEXPRLENGTH)) {   
        printf("Expression to parse: %s\n", expr1);
        root = build_tree(expr1);
        printf("Postfix: ");
        postorder(root);
        printf("\n\n");
        
        init_regtable(); // register table i hope works
        init_vartable();

        int assigned[NUMVAR] = {0};
        for (int i = 0; expr1[i] != '\0'; i++) {
            if (expr1[i] >= 'a' && expr1[i] < 'a' + NUMVAR) {
                int var = expr1[i] - 'a';
                if (!assigned[var]) {
                    if (assign_reg(var) == -1) {
                        printf("Error: out of registers\n");
                        break;
                    }
                    assigned[var] = 1;
                }
            }
        }

        printf("Generated code:\n");
        root = generate_code(root);
    }

    return 0;
}
