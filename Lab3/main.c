#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "build_tree.h"

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
        printf("\n");
        printf("\n");
    }
    return 0;
}
