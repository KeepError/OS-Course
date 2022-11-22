#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int main() {
    DIR *dir = opendir("/");
    if (dir == NULL) {
        return EXIT_FAILURE;
    }
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        printf("%s\n", entry->d_name);
    }

    closedir(dir);

    return EXIT_SUCCESS;
}