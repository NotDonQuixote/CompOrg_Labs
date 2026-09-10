#include <stdio.h>

int main(void){
    for (int i =0; i <= 20; i++){

        if (i == 15){
            break;
            return 0;
        }
        if (i % 3 ==0){
            continue;
        }
        else{

        printf("%d\n", i);
        }
    }
}