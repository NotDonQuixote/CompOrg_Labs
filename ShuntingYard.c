#include <stdio.h>

int   
//infix = a + b * c
//postfix = a b c * +
//operand sends straight to the output
//open bracket (  push onto the stack
//closed bracket )  pop operators to the output untill you meet the open bracket
// and operator o while the top of the stack is an operator that binds tighter than o - or binds equally and o is left associative- pop it to the output then push o
//End of input  pop everything left on the stack to the output
