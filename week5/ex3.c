#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int is_prime(int n) {
    if (n <= 1)
        return 0;
    for (int d = 2; d * d <= n; d++)
        if (n % d == 0)
            return 0;
    return 1;
}

int primes_count_in_interval(int start, int finish) {
    int ret = 0;
    for (int i = start; i < finish; i++)
        if (is_prime(i) != 0)
            ret++;
    return ret;
}

typedef struct prime_counter_request {
    int start, end;
} prime_counter_request;

void *prime_counter(void *_args) {
    prime_counter_request *request = (prime_counter_request *) _args;
    int result = primes_count_in_interval(request->start, request->end);
    int *res = malloc(sizeof(*res));
    *res = result;
    pthread_exit(res);
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int n_threads = atoi(argv[2]);
    int segment_size = n / n_threads;

    pthread_t *threads = malloc(n_threads * sizeof(pthread_t));

    prime_counter_request *requests = malloc(n_threads * sizeof(prime_counter_request));

    for (int i = 0; i < n_threads; i++) {
        int start_index = segment_size * i;
        int end_index = segment_size * (i + 1);
        if (i == n - 1) end_index = n;

        requests[i].start = start_index;
        requests[i].end = end_index;

        pthread_create(&threads[i], NULL, prime_counter, &requests[i]);
    }

    int res;

    for (int i = 0; i < n_threads; i++) {
        void *return_value;
        pthread_join(threads[i], &return_value);
        res += *(int *) return_value;
        free(return_value);
    }

    free(threads);
    free(requests);

    printf("%d\n", res);

    exit(EXIT_SUCCESS);
}