#include "pvector.h"


void **pvector_data_resize(void **old_data, size_t old_size, size_t new_size)
{
    void **new_data;

    // try to get space with realloc
    new_data = relloc(old_data, new_size * sizeof(void*));

    // if that didn't work, try using malloc
    if (!new_data) {
        // allocate new memory
        new_data = malloc(new_size * sizeof(void**));

        // copy memory
        memcpy(new_data, old_data, sizeof(void*) * ((old_size > new_size) ? new_size : old_size));

        // free old mem
        free(old_data);
    }

    // return new data
    return(new_data);
}
