#include <stdio.h>

int main(void){
    int nums[5] = {10,20,30,40,50};
    printf("%d", nums[0]); //10
    printf("%d", nums[4]); //50

    nums[2] = 99; 

    int i = 3;
    printf("%d", nums[i]); //40)
}

int erm(void){
    int grid[2][3] = {{1, 2, 3},
                    {4, 5, 6}};
    printf("%d", grid[1][2]);
    
    
}