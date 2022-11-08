#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define COUNTER_BITS 32

typedef struct {
    int page_num;
    unsigned int counter;
} Page;

int find_page_index(Page *pages, int page_frames_number, int page_num) {
    for (int i = 0; i < page_frames_number; i++) {
        if (page_num == pages[i].page_num) {
            return i;
        }
    }
    return -1;
}

int get_oldest_page_index(Page *pages, int page_frames_number) {
    int oldest_index = 0;
    for (int i = 1; i < page_frames_number; i++) {
        if (pages[i].counter < pages[oldest_index].counter) {
            oldest_index = i;
        }
    }
    return oldest_index;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("You have to pass number of page frames.");
        return EXIT_FAILURE;
    }

    int hits = 0;
    int misses = 0;
    int page_frames_number = atoi(argv[1]);

    FILE *file = fopen("Lab 09 input.txt", "r");
    if (file == NULL) {
        printf("Can't open file.");
        return EXIT_FAILURE;
    }

    Page *pages = malloc(page_frames_number * sizeof(Page));

    int page_num;
    while (!feof(file)) {
        fscanf(file, "%d", &page_num);
        if (feof(file)) continue;

        int page_index = find_page_index(pages, page_frames_number, page_num);

        if (page_index != -1) {
            pages[page_index].counter |= 1 << (COUNTER_BITS - 1);
            hits++;
        } else {
            misses++;
            int oldest_page_index = get_oldest_page_index(pages, page_frames_number);
            pages[oldest_page_index].page_num = page_num;
            pages[oldest_page_index].counter |= 1 << (COUNTER_BITS - 1);
        }

        for (int i = 1; i < page_frames_number; i++) {
            pages[i].counter >>= 1;
        }
    }

    printf("Hit: %d\n", hits);
    printf("Miss: %d\n", misses);
    printf("Ratio: %f\n", (float) hits / (float) misses);

    return EXIT_SUCCESS;
}