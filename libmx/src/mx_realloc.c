#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    if (size == 0 && ptr) {
        free(ptr);
        return NULL;
    }
    if (!ptr && size)
        return malloc(size);

    size_t ptr_size = malloc_size(ptr);

    if (ptr_size > size)
        size = ptr_size;
    
    void *new_ptr = (void *) malloc(size);

    if (!new_ptr)
        return NULL;
    
    new_ptr = mx_memmove(new_ptr, ptr, ptr_size);

    free(ptr);

    return new_ptr;
}
