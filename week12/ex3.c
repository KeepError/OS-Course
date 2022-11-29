#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <linux/input.h>

#define LOCKFILE "/dev/input/by-path/platform-i8042-serio-0-event-kbd"

#define KEYS_MAX 6

bool keys_match(int required_keys[], int required_keys_size, int pressed_keys[]) {
    for (int i = 0; i < required_keys_size; ++i) {
        bool found = false;
        for (int j = 0; j < KEYS_MAX; ++j) {
            if (pressed_keys[j] == required_keys[i]) found = true;
        }
        if (found == false) return false;
    }
    return true;
}

int main() {
    printf("%s", "1");
    struct input_event event;

    int pfd = open(LOCKFILE, O_RDONLY);
    if (pfd == -1) {
        return EXIT_FAILURE;
    }

    int pressed_keys[KEYS_MAX];
    while (true) {
        read(pfd, &event, sizeof event);
        if (event.type == EV_KEY && event.value >= 0 && event.value <= 2) {
            if (event.value == 1) {
                for (int i = 0; i < KEYS_MAX - 1; ++i) {
                    pressed_keys[i] = pressed_keys[i + 1];
                }
                pressed_keys[KEYS_MAX - 1] = event.code;
            }
        }
        int keys1[] = {KEY_P, KEY_E};
        if (keys_match(keys1, 2, pressed_keys)) {
            fprintf(stdout, "I passed the Exam!");
        }
        int keys2[] = {KEY_C, KEY_A, KEY_P};
        if (keys_match(keys2, 3, pressed_keys)) {
            fprintf(stdout, "Get some cappucino!");
        }
     }

    return EXIT_SUCCESS;
}