#include <stdio.h>

int main(void){
    int n;
    printf("how many numbers: ");
    scanf("%d", &n);
    int *arr = malloc(n * sizeof(int));
    if(arr == NULL){
        printf("error allocating memory\n");
        return 1;
    }
    printf("enter numbers: ");
    for (int i = 0; i < n; i++){
        scanf("%d", arr[i]);
    }
    int sum =0;
    printf("printing numbers: \n");
    for (int i = 0; i < n; i++){
        printf("%d\n", arr[i]);
        sum += arr[i];
    }
    printf("sum of numbers: %d\n", sum);
    arr = realloc(arr, (n+1) * sizeof(int));
    arr[n] = 10;
    sum += arr[n];
    printf("printing the new sum: %d\n", sum);
    free(arr);
}  