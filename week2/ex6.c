#include <stdio.h>
#include <stdlib.h>

void print_pattern_1(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void print_pattern_2(int n) {
    for (int i = 1; i <= n; i++) {
        int symbols = i;
        if (i > (n / 2)) symbols = n - i + 1;
        for (int j = 0; j < symbols; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void print_pattern_3(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            printf("*");
        }
        printf("\n");
    }
}

int main(void) {
    print_pattern_1(7);
    printf("\n");
    print_pattern_2(7);
    printf("\n");
    print_pattern_3(7);
    printf("\n");
    return 0;
}