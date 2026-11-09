#ifndef BACKEND_H
#define BACKEND_H

#include "build_tree.h"

void init_regtable(void);
void init_vartable(void);
int assign_reg(int var);
void printregtable(void);
void printvartable(void);
struct node *generate_code(struct node *root);

#endif
