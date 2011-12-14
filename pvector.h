#ifndef _PVECTOR_H
#define _PVECTOR_H
#include <string.h>
#include <stdlib.h>
#include "debug.h"


/* vector of void pointers main
 * data structure
 */
struct pvector
{
    void **data;
    size_t size;
};


typedef struct pvector pvector;


/* pvector_data_resize(data, old, new)
 * resize the data to new size (size being the 
 * amount of pointers) using realloc or malloc
 */
void **pvector_data_resize(void **data, size_t size);
