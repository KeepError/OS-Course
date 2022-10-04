#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    char *line;
    int fd;
    char *myfifo = "/tmp/ex1";

    mkfifo(myfifo, 0666);

    while (true) {
        fd = open(myfifo, O_RDONLY);
        read(fd, line, 2048);
        printf("%s", line);
        close(fd);
    }

    return EXIT_SUCCESS;
}