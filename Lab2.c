#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* hex_to_binary(char a){ //might need to change from int to char so i can use it to risc v
    char* hex_letter[] = {"0000", "0001", "0010", "0011", "0100", 
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

int main() {
    char hex[20];

    printf("Please enter a hex code: ");
    scanf("%19s", hex);

    split_string(hex);

    for (int i = 0; hex[i] != '\0'; i++) {
        char ch = toupper(hex[i]);
        if (ch == '{' || ch == '}' || ch == ' ' || (ch == '0' && hex[i+1] == 'X')) {
            continue;
        }
        //printf("line 82 test");
        printf("%c ----> %s\n", ch, hex_to_binary(ch));
    }

    return 0;
}

//When i was a young boy my father took me into the city to see a marching band. He said, "Son when you grow up, would you be the savior of the broken, the beaten and the damned?" He said, "Will you defeat them, your demons, and all the non-believers, the plans that they have made?" Because one day I'll leave you a phantom to lead you in the summer, to join the black parade."