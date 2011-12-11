#ifndef _DEBUG_H
#define _DEBUG_H
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void *log_malloc(size_t size, const char *file, unsigned int line, const char *func);
void log_free(void *data, const char *file, unsigned int line, const char *func);

#ifndef _DEBUG_C
#define malloc(size) log_malloc(size, __FILE__, __LINE__, __func__)
#define free(data) log_free(data, __FILE__, __LINE__, __func__)
#endif

#endif
