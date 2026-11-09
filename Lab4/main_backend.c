#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "backend.h"

int get_str(char s[], int lim)
{
    int c, i;

    i = 0;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    s[i] = '\0';
    return i;
}

void postorder(struct node *root)
{
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        if (root->type == VAR)
            printf("%c", root->data + 'a');
        else if (root->type == CONST)
            printf("%d", root->data);
        else
            printf("%s", optable[root->data].symbol);
    }
}

int power_of_two(int n)
{
    if (n % 2 != 0)
        return 0;
    else if (n == 0)
        return 1;
    else
        return power_of_two(n / 2);
}

int main(void)
{
    char expr1[MAXEXPRLENGTH];
    struct node *root;

    while (get_str(expr1, MAXEXPRLENGTH)) {
        int assigned[NUMVAR] = {0};
        int i;

        printf("Expression to parse: %s\n", expr1);
        root = build_tree(expr1);
        if (root == NULL) {
            printf("Unable to build expression tree\n\n");
            continue;
        }

        printf("Postfix: ");
        postorder(root);
        printf("\n\nGenerated code:\n");

        init_regtable();
        init_vartable();
        for (i = 0; expr1[i] != '\0'; i++) {
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

        if (expr1[i] == '\0')
            root = generate_code(root);
        printf("\n");
    }

    return 0;
}
