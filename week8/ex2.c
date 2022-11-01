#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    // Explanation for Exercise 2:
    // SI (Swap In) and SO (Swap Out) are swap status. In my case they are always 0, because free memory is enough and swap is not used.

    // Explanation for Exercise 3:
    // Top also shows that swap is not used. Also, it can be noticed that free memory decreases and used memory increases due to allocation.

    void *data[10];

    for (int i = 0; i < 10; ++i) {
        data[i] = malloc(10 * 1024 * 1024);
        memset(data[i], 0, 10 * 1024 * 1024);
        sleep(1);
    }
    for (int i = 0; i < 10; i++)
        free(data[i]);

    return EXIT_SUCCESS;
}