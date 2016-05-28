/*! @file sarray.h
 *  @author Patrick Elsen
 *  @date 9 Sep 2012
 *  @copyright 2011, Patrick M. Elsen
 *  This file is part of CLists (http://github.com/xfbs/CLists)
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

#pragma once

#include <stdlib.h>
#include <string.h>
#include "bitvec.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int sarray_word;

struct sarray
{
    size_t size;

    size_t capacity;

    sarray_word *data;
};

typedef struct sarray sarray_t;

/* BASIC DATA ACCESS */

size_t sarray_size(const sarray_t *array);

size_t sarray_length(const sarray_t *array);

size_t sarray_capacity(const sarray_t *array);

void *sarray_first(const sarray_t *array);

void *sarray_last(const sarray_t *array);

/* CREATION/DESTRUCTION FUNCTIONS */

sarray_t *sarray_new(size_t size, size_t capacity);

sarray_t *sarray_init(sarray_t *array, size_t size, size_t capacity);

sarray_t *sarray_purge(sarray_t *array);

int     sarray_free (sarray_t *array);

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

#ifdef __cplusplus
}
#endif
