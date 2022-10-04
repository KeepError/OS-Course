#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int is_prime(int n)
{
    if (n <= 1)
        return 0;
    for (int d = 2; d * d <= n; d++)
        if (n % d == 0)
            return 0;
    return 1;
}

int primes_count_in_interval(int start, int finish)
{
    int ret = 0;
    for (int i = start; i < finish; i++)
        if (is_prime(i) != 0)
            ret++;
    return ret;
}

struct PrimeNumberCountThread {
    int *primes_number;
    int start;
    int end;
};
typedef struct PrimeNumberCountThread PrimeNumberCountThread;

void *thread_calculate_pm_count(void *_args) {
    PrimeNumberCountThread *pm_thread = (PrimeNumberCountThread *) _args;
    int primes_count = primes_count_in_interval(pm_thread->start, pm_thread->end);
    pm_thread->primes_number = &primes_count;

    return NULL;
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    PrimeNumberCountThread *pm_threads[m];
    pthread_t thread_id;

    int part_size = n / m;
    for (int i = 0; i < m; i++) {
        PrimeNumberCountThread *pm_thread = malloc(sizeof(PrimeNumberCountThread));
        int start_index = part_size * i;
        int end_index = part_size * (i + 1);
        if (i == n - 1) end_index = n;

        pm_thread->start = start_index;
        pm_thread->end = end_index;

        pthread_create(&thread_id, NULL, thread_calculate_pm_count, pm_thread);
    }

    for (int i = 0; i < n; i++)
        pthread_join();

    int total_result = 0;
    for (int i = 0; i < n; i++)
        total_result += *pm_threads[i]->primes_number;

    printf("%d", total_result);

    return EXIT_SUCCESS;
}