#include <stdio.h>
int main(void) {
    printf("Enter the number of seconds: ");
    int secs;
    scanf("%d", &secs);
    float mins = secs / 60.0;
    printf("%d seconds is %.2f minutes", secs, mins);
    return 0;
}