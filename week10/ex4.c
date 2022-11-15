#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int main() {
    DIR *dir = opendir("tmp");
    if (dir == NULL) {
        return EXIT_FAILURE;
    }
    struct dirent *entries[256];

    int entriesNumber = 0;
    struct dirent *entry;
    struct stat info;
    while ((entry = readdir(dir)) != NULL) {
        char currentPath[256];
        strcpy(currentPath, "tmp/");
        strcat(currentPath, entry->d_name);
        if (stat(currentPath, &info) != 0) {
            closedir(dir);
            return EXIT_FAILURE;
        }
        entries[entriesNumber] = entry;
        entriesNumber++;
    }

    closedir(dir);

    printf("File - Hard Links\n");
    for (int i = 0; i < entriesNumber; ++i) {
        int count = 0;
        for (int j = 0; j < entriesNumber; ++j)
            if (entries[i]->d_ino == entries[j]->d_ino)
                count++;

        if (count >= 2) {
            printf("%s - ", entries[i]->d_name);

            for (int j = 0; j < entriesNumber; ++j)
                if (entries[i]->d_ino == entries[j]->d_ino)
                    printf("%s ", entries[j]->d_name);
            printf("\n");
        }
    }

    return 0;
}