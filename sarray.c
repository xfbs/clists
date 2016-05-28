/*  File: sarray.c
 *  
 *  Copyright (C) 2011, Patrick M. Elsen
 *
 *  This file is part of CLists (http://github.com/xfbs/CLists)
 *  Author: Patrick M. Elsen <pelsen.vn (a) gmail.com>
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "clists/sarray.h"
#include <assert.h>
#include <limits.h>

#define sarray_word_size sizeof(sarray_word)

#define sarray_word_bit_count (sarray_word_size * CHAR_BIT)

#define sarray_element_size(size) \
    ((size + sarray_word_size - 1) / \
     sarray_word_size)

#define sarray_bitfield_count(capacity) \
    ((capacity + sarray_word_bit_count - 1) / \
     sarray_word_bit_count)

#define sarray_element_offset(index, size) \
    ((index / sarray_word_bit_count) + \
     (index * sarray_element_size(size)))

#define sarray_cluster_size(size) \
    (1 + sarray_word_bit_count * sarray_element_size(size))

#define sarray_bitfield_offset(index, size) \
    (index * sarray_cluster_size(size))

inline size_t sarray_popcount(sarray_word w) {
    size_t result = 0;
    while(w > 0) {
        result++;
        w &= w - 1;
    }

    return result;
}

/* BASIC DATA ACCESS */

size_t sarray_size(const sarray_t *array) {
    return array->size;
}

size_t sarray_length(const sarray_t *array) {
    size_t length = 0;

    for(int bitfield = 0; bitfield < sarray_bitfield_count(array->capacity); bitfield++) {
        length += sarray_popcount(array->data[sarray_bitfield_offset(bitfield, array->size)]);
    }

    return length;
}

size_t sarray_capacity(const sarray_t *array) {
    return array->capacity;
}

void *sarray_first(const sarray_t *array);

void *sarray_last(const sarray_t *array);

/* CREATION/DESTRUCTION FUNCTIONS */

sarray_t *sarray_new(size_t size, size_t capacity) {
    sarray_t *array = malloc(sizeof(sarray_t));

    if(array == NULL) {
        return NULL;
    }

    return sarray_init(array, size, capacity);
}

sarray_t *sarray_init(sarray_t *array, size_t size, size_t capacity) {
    array->size = size;
    array->capacity = capacity;

    if(capacity == 0) {
        array->data = NULL;
        return array;
    }

    size_t bitfields = (capacity + (sarray_word_size * CHAR_BIT) - 1) /
                       (sarray_word_size * CHAR_BIT);
    size_t element_size = (size + sarray_word_size - 1) /
                          sarray_word_size;
    size_t total_size = bitfields + (capacity * element_size);

    array->data = malloc(total_size * sarray_word_size);

    if(array->data == NULL) {
        array->size = 0;
        array->capacity = 0;
        return NULL;
    }

    return array;
}

sarray_t *sarray_purge(sarray_t *array);

int sarray_free (sarray_t *array) {
    if(array->data != NULL) {
        free(array->data);
    }

    free(array);

    return 0;
}

/* INSERTION/REMOVAL */

void *sarray_append (sarray_t *array, const void *data);

void *sarray_prepend(sarray_t *array, const void *data);

void *sarray_insert (sarray_t *array, size_t pos, const void *data);

int   sarray_remove (sarray_t *array, size_t pos);

/* ACCESSS/MODIFICATION */

void *sarray_set(sarray_t *array, size_t pos, const void *data);

void *sarray_get(const sarray_t *array, size_t pos, void *data);

void *sarray_pop(sarray_t *array, void *data);

int sarray_swap(sarray_t *array, size_t a, size_t b);

/* MODIFICATION OF SARRAY */

sarray_t *sarray_split(sarray_t *array, size_t pos);

sarray_t *sarray_join(sarray_t *dest, sarray_t *src);

sarray_t *sarray_copy(const sarray_t *array);
