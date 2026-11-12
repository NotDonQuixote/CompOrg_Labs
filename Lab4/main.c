#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "backend.h"
  
void postorder(struct node *root){
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


int main(){
    char expr1[MAXEXPRLENGTH];
    struct node *root;
    while (fgets(expr1, MAXEXPRLENGTH, stdin) != NULL) {   
        expr1[strcspn(expr1, "\r\n")] = '\0'; //strip newline
        if (expr1[0] == '\0') //skip blanks
            continue;
        printf("Expression to parse: %s\n", expr1);
            //init regtable and vartable used to be here DONT FUCKING FORGET
        root = build_tree(expr1);
        if (root == NULL) {
            printf("Error in expression tree\n");
            continue;
        }
        init_regtable(); //initialize register table i hope this owrks
        init_vartable();
        printvartable();
        printregtable();
        printf("Postfix: ");
        postorder(root);
        printf("\n");
        
        //printf("Generated code:\n");
        root = generate_code(root);
        if (root->type == REG)
            printf("root: x%d\n", root->data);
        else
            printf("root: %d\n", root->data);
        //printregtable(); it was printing twice here
        printf("\n");
    }
    return 0;
}
