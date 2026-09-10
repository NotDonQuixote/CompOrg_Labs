#include <stdio.h>
int square(int n);

int getCube(int x){
    return x *x *x;
}

int main(void){
    int num;
    printf("Please enter a number: ");
    scanf("%d", &num);

    printf("The cube of %d is %d. \n", num, getCube(num));
    return 0;
}
