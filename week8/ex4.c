#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdio.h>

int main() {
    void *data[10];
    struct rusage usage;

    for (int i = 0; i < 10; ++i) {
        data[i] = malloc(10 * 1024 * 1024);
        memset(data[i], 0, 10 * 1024 * 1024);

        getrusage(RUSAGE_SELF, &usage);
        printf("Maximum RSS (Resident Set Size): %ld\n", usage.ru_maxrss);

        sleep(1);
    }
    for (int i = 0; i < 10; i++)
        free(data[i]);

    return EXIT_SUCCESS;
}