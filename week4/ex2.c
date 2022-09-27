#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


#define VECTOR_SIZE 120

int dot_product(const int u[], const int v[], int i_start, int i_end) {
    int result = 0;

    for (int i = i_start; i < i_end; i++) {
        result += u[i] * v[i];
    }

    return result;
}

int main() {
    srand(time(NULL)); // For better random
    FILE *file;
    int main_pid = getpid();

    file = fopen("temp.txt", "w");
    int u[VECTOR_SIZE];
    int v[VECTOR_SIZE];
    int n, created_process;
    for (int i = 0; i < VECTOR_SIZE; i++) {
        u[i] = rand() % 100;
        v[i] = rand() % 100;
    }
    scanf("%d", &n);
    int p[n];
    int part_size = VECTOR_SIZE / n;
    for (int i = 0; i < n; i++) {
        if (getpid() != main_pid) continue;
        created_process = fork();
        if (created_process > 0) {
            p[i] = created_process;
            continue;
        }

        int start_index = part_size * i;
        int end_index = part_size * (i + 1);
        if (i == n - 1) end_index = VECTOR_SIZE;

        int result = dot_product(u, v, start_index, end_index);
        fprintf(file, "%d ", result);
    }

    if (getpid() != main_pid) exit(EXIT_SUCCESS);
    for (int i = 0; i < n; i++) waitpid(p[i], NULL, 0);
    fclose(file);

    file = fopen("temp.txt", "r");
    int number, sum;
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d ", &number);
        sum += number;
    }
    printf("Result of dot product: %d\n", sum);

    return EXIT_SUCCESS;
}