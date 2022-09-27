#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main() {
    int parent_pid = getpid();
    clock_t t_start, t_end;
    int n;
    t_start = clock();
    for (int i = 0; i < 2; i++) {
        n = 0;
        if (getpid() == parent_pid) {
            n = fork();
            if (n == 0) t_start = clock();
        }
    }
    t_end = clock();
    double time_ms = ((double) t_end - (double) t_start) / CLOCKS_PER_SEC * 1000;
    printf("PID: %d\tPPID: %d\tTime taken: %lf ms\n", getpid(), getppid(), time_ms);

    return EXIT_SUCCESS;
}