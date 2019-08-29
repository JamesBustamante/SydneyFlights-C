#include <stdio.h>
#include <math.h>
#include <stdbool.h> 
#include <string.h>

void append(char* s, char c);

int main(void) {
    char wordInput[50];
    char charList[20];
    int i = 0; 
    printf("Enter a word>\n");
    scanf("%s", wordInput);
    int j = 0;
    int occurance = 0;
    int doneBefore = 0;
    int duplicate = 0;
    while (wordInput[i] != '\0') {
        for (j = 0; wordInput[j] != '\0' ; j++) {
            if (wordInput[i] == wordInput[j]) {
                occurance++;
            }
        }
        
            int counter = 0;
            for (counter =0; wordInput[counter]; counter++) {
                if (wordInput[i] == charList[counter]) {
                doneBefore = 1;
            }
            }
            append(charList, wordInput[i]);
        if (occurance >= 2 && doneBefore == 0) {
            duplicate = 1;
            printf("Duplicate letter: %c, Occurrences: %d\n", wordInput[i], occurance); 
        }
        occurance = 0;
        i++;
        doneBefore = 0;
    }
    if (duplicate == 0) {
        printf("No duplicates found\n");
    }
    return 0;
}

void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}