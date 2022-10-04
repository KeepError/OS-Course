#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
    int fd[2];
    int pid;
    char buffer[2048];

    pipe(fd);

    pid = fork();
    char *line;
    size_t len;

    if (pid == 0) {
        close(fd[0]);
        while (true) {
            getline(&line, &len, stdin);
            write(fd[1], line, (len + 1));
        }
    } else {
        close(fd[1]);

        while (true) {
            read(fd[0], buffer, sizeof(buffer));
            printf("%s", buffer);
        }
    }

    return EXIT_SUCCESS;
}