#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

int is_prime(int n) {
    if (n <= 1)
        return 0;
    for (int d = 2; d * d <= n; d++)
        if (n % d == 0)
            return 0;
    return 1;
}

int n = 0;

pthread_mutex_t global_lock = PTHREAD_MUTEX_INITIALIZER;

int next_number_to_check = 0;
int primes_found_so_far = 0;

int get_number_to_check() {
    int ret = next_number_to_check;
    if (next_number_to_check != n)
        next_number_to_check++;
    return ret;
}

void increment_primes() {
    primes_found_so_far++;
}

void *check_primes(void *arg) {
    while (true) {
        pthread_mutex_lock(&global_lock);
        int number = get_number_to_check();
        if (number == n) {
            pthread_mutex_unlock(&global_lock);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&global_lock);

        if (is_prime(number)) {
            pthread_mutex_lock(&global_lock);
            increment_primes();
            pthread_mutex_unlock(&global_lock);
        }
    }
}

int main(int argc, char *argv[]) {
    n = atoi(argv[1]);
    int n_threads = atoi(argv[2]);

    pthread_t *threads = malloc(n_threads * sizeof(pthread_t));
    for (int i = 0; i < n_threads; i++) {
        pthread_create(&threads[i], NULL, check_primes, NULL);
    }
    for (int i = 0; i < n_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    pthread_mutex_destroy(&global_lock);

    printf("%d\n", primes_found_so_far);
    exit(EXIT_SUCCESS);
}