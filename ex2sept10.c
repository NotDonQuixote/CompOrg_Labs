#include <stdio.h>

int n, i;
scanf("%d", &n);

int *arr = malloc(n * sizeof(int));

if arr == NULL{ //always check
    printf("out of memory\n");
    return 1;
}

for (i = 0; i < n; i++){
    arr[i] = i * i;     //normal array use
}

free(arr);  //give it back