#include <stdio.h>

int tribonacci(int n) {
    int t1 = 0;
    int t2 = 1;
    int t3 = 1;
    if (n == 0) return t1;

    for (int i = 3; i <= n; i++) {
        int new = t1 + t2 + t3;
        t1 = t2;
        t2 = t3;
        t3 = new;
    }

    return t3;
}

int main(void) {
    printf("%d\n", tribonacci(4));
    printf("%d\n", tribonacci(36));
    return 0;
}