#include <stdio.h>

int main(void){
    int nums[5];
    int i;

    for (i=0; i < 5; i++){
        printf("value %d: ", i);
        scanf("%d", &nums[i]);
    }

    int max = nums[0];
    printf("\n");
   
    for (int i=0; i<5; i++){
        if(max < nums[i]){
            max = nums[i];
        }
    }
    printf("The largest number in the array is: %d", max);

}
