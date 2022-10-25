#include <stdlib.h>
#include <string.h>
#include <malloc.h>

void *realloc_new(void *ptr, size_t size) {
    void *new_ptr = malloc(size);
    if (new_ptr == NULL) {
        return NULL;
    }

    memcpy(new_ptr, ptr, (size > malloc_usable_size(ptr)) ? malloc_usable_size(ptr) : size);

    free(ptr);
    return new_ptr;
}


int main() {

    return EXIT_SUCCESS;
}