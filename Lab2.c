#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char* hex_to_binary(char a){ //might need to change from int to char so i can use it to risc v
    char * hex_letter[] = {"0000", "0001", "0010", "0011", "0100", 
        "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    switch(a){
        case '0':
            return hex_letter[0];
        case '1':
            return hex_letter[1];
        case '2':
            return hex_letter[2]; 
        case '3':
            return hex_letter[3];
        case '4':
            return hex_letter[4];
        case '5':
            return hex_letter[5];
        case '6':
            return hex_letter[6];
        case '7':
            return hex_letter[7];
        case '8':
            return hex_letter[8];
        case '9':
            return hex_letter[9];
        case 'A':
            return hex_letter[10];
        case 'B':
            return hex_letter[11];
        case 'C':
            return hex_letter[12];
        case 'D':
            return hex_letter[13];
        case 'E':
            return hex_letter[14];
        case 'F':
            return hex_letter[15];
    }
    return NULL;
}

const char* hex_string_to_binary(const char *hex) { //i give up
    static char binary_string[77];
    int binary_index = 0;

    for (int i = 0; hex[i] != '\0'; i++) {
        char digit = (char)toupper((unsigned char)hex[i]);
        const char *binary_digit = hex_to_binary(digit);

        if (binary_digit == NULL) {
            continue;
        }

        for (int j = 0; j < 4; j++) {
            binary_string[binary_index++] = binary_digit[j];
        }
    }

    binary_string[binary_index] = '\0';
    return binary_string;
}

void split_string(char *hex) {
    int first = 1;

    printf("[");
    for (int i = 0; hex[i] != '\0'; i++) {
        if (hex[i] == '{' || hex[i] == '}' || hex[i] == ' ' || (hex[i] == '0' && hex[i+1] == 'X')) {
            //printf("if statement at line 36");
            continue;
        }

        if (!first) {
            printf(", ");
            //printf("!first statement at line 40");
        }

        printf("%c", hex[i]);
        //call to binary here. hex[i] works
        //printf("\n", "binary representation: ", "%d", hex_to_binary(hex[i]));
        printf(" -> %s", hex_to_binary(hex[i]));

        first = 0;
    }
    //printf("end of for loop");
    printf("]\n");
}

static int32_t sign_extend(uint32_t value, int bits) {
    uint32_t sign_bit = 1U << (bits - 1);
    return (int32_t)((value ^ sign_bit) - sign_bit);
}

void binary_to_riscv(const char *binary) {
    uint32_t instruction = 0;
    uint32_t opcode;
    uint32_t funct3;
    uint32_t funct7;
    unsigned int rd;
    unsigned int rs1;
    unsigned int rs2;
    int32_t immediate;

    if (strlen(binary) != 32) {
        printf("Error: string is not 32 bits.\n");
        main();
        return;
    }

    for (int i = 0; i < 32; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            printf("Error: unexpected character.\n");
            main();
            return;
        }
        instruction = (instruction << 1) | (uint32_t)(binary[i] - '0');
    }

    opcode = instruction & 0x7f;
    rd = (instruction >> 7) & 0x1f;
    funct3 = (instruction >> 12) & 0x7;
    rs1 = (instruction >> 15) & 0x1f;
    rs2 = (instruction >> 20) & 0x1f;
    funct7 = (instruction >> 25) & 0x7f;

    switch (opcode) {
        case 0x33:
            if (funct7 == 0x00) {
                const char *names[] = {"add", "sll", "slt", "sltu", "xor", "srl", "or", "and"};
                if (funct3 <= 7) {
                    printf("%s x%u, x%u, x%u\n", names[funct3], rd, rs1, rs2);
                    return;
                }
            } else if (funct7 == 0x20 && (funct3 == 0 || funct3 == 5)) {
                printf("%s x%u, x%u, x%u\n", funct3 == 0 ? "sub" : "sra", rd, rs1, rs2);
                return;
            } else if (funct7 == 0x01) {
                const char *names[] = {"mul", "mulh", "mulsu", "mulu", "div", "divu", "rem", "remu"};
                printf("%s x%u, x%u, x%u\n", names[funct3], rd, rs1, rs2);
                return;
            }
            break;

        case 0x13:
            immediate = sign_extend(instruction >> 20, 12);
            if (funct3 == 1 || funct3 == 5) {
                const char *name = funct3 == 1 ? "slli" : (funct7 == 0x20 ? "srai" : "srli");
                printf("%s x%u, x%u, %u\n", name, rd, rs1, (unsigned)(instruction >> 20) & 0x1f);
                return;
            }
            {
                const char *names[] = {"addi", NULL, "slti", "sltiu", "xori", NULL, "ori", "andi"};
                if (funct3 != 1 && funct3 != 5 && names[funct3] != NULL) {
                    printf("%s x%u, x%u, %d\n", names[funct3], rd, rs1, immediate);
                    return;
                }
            }
            break;

    }

    printf("Unknown or unsupported RISC-V instruction.\n");
}

int main() {
    char hex[20];

    printf("Please enter a hex code: ");
    scanf("%19s", hex);

    split_string(hex);
    printf("binary string: %s\n", hex_string_to_binary(hex));
    binary_to_riscv(hex_string_to_binary(hex));
    return 0;
}