#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

struct Thread {
    pthread_t *id;
    int i;
    char message[256];
};
typedef struct Thread Thread;

void *thread_exec(void *_args) {
    Thread *thread = (Thread *) _args;
    printf("%s (ID: %ld)\n", thread->message, (long) *thread->id);
    return NULL;
}

int main() {
    int n;
    Thread *threads[256];
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Thread *thread = malloc(sizeof(Thread));
        thread->i = i;
        sprintf(thread->message, "Hello from thread %d", i);
        pthread_t *thread_id = malloc(sizeof(pthread_t));
        thread->id = thread_id;
        pthread_create(thread_id, NULL, thread_exec, thread);
        printf("Thread %d is created\n", i);
        pthread_join(*thread_id, NULL);
        threads[i] = thread;
    }

    for (int i = 0; i < n; i++) {
        free(threads[i]->id);
        free(threads[i]);
    }
    return EXIT_SUCCESS;
}
