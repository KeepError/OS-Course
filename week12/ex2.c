#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <linux/input.h>

#define LOCKFILE "/dev/input/by-path/platform-i8042-serio-0-event-kbd"

int main() {
    struct input_event event;

    int pfd = open(LOCKFILE, O_RDONLY);
    if (pfd == -1) {
        return EXIT_FAILURE;
    }

    while (true) {
        read(pfd, &event, sizeof event);
        if (event.type == EV_KEY && event.value >= 0 && event.value <= 1) {
            char *s = "";
            if (event.value == 0) s = "RELEASED";
            else if (event.value == 1) s = "PRESSED";
            printf("%s 0x%04x (%d)\n", s, event.code, event.code);
        }
    }

    return EXIT_SUCCESS;
}