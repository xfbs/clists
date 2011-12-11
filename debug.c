#define _DEBUG_C
#include "debug.h"

void *log_malloc(size_t size, const char *file, unsigned int line, const char *func)
{
    void *data = malloc(size);
    //printf("malloc(%3u) => %p [%s:%u in %s()]\n", (unsigned int)size, data, file, line, func);
    return data;
}

void log_free(void *data, const char *file, unsigned int line, const char *func)
{
    //printf("free(%p) [%s:%u in %s()]\n", data, file, line, func);
    free(data);
}
