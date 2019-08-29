#include <stdio.h>
#include <math.h>

void buildTriangle(int a);

int main(void) {
    int amount;
    printf("Enter an integer>\n");
    scanf("%d", &amount);
    if (amount > 0) {
    buildTriangle(amount);}
    else printf("Input must be greater or equal to 1\n");
    return 0;
}

void buildTriangle(int a) {
    int size = a;
    int i, space;
    for (i = 1; i<= a; i++) {
        for (space = 1; space<=size; space++) printf(" ");
            size--;
        for (space = 1; space<2*i; space++) {printf("*");}
        printf("\n");
    }
}