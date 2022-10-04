#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    char *line;
    size_t len;
    int fd;
    char *myfifo = "/tmp/ex1";

    mkfifo(myfifo, 0666);

    while (true) {
        getline(&line, &len, stdin);
        fd = open(myfifo, O_WRONLY);
        write(fd, line, len + 1);
        close(fd);
    }

    return EXIT_SUCCESS;
}