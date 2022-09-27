#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    char *line;
    size_t len = 0;
    while (1) {
        getline(&line, &len, stdin);
        int pid = fork();
        if (pid == 0) {
            system(line);
            exit(EXIT_SUCCESS);
        }
    }
    return EXIT_SUCCESS;
}