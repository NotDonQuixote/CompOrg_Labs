#include <stdio.h>
#include <string.h>

    //read a word into char word [50] and print it back.
    //count its characters with loop that stops at '\0'
    //print count from strlen to check they match

int main(void){
    char word[50];
    int vowels = 0;
    
    scanf("%s", word);
    printf("printing back = %s\n", word);
    int count;
    for(count=0; word[count]!= '\0'; count++){
    printf("%d\n", count);
    int length = strlen(word);
    printf("length = %d\n", length);
    
    for(int i = length-1; i>=0; i++){
        printf("%c", word[i]);
        if (word[i] == 'a' || word[i] == 'e' || word[i] == 'i' || word[i] == 'o' || word[i] == 'u')
            vowels++;
        }
    }
    printf("\n");
    printf("Vowels = $d\n", vowels);
}