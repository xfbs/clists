/*! @file bitvec.h
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
 *
 *  ### Design Specifications
 *    - simple C bit vector
 *    - efficient
 *    - flexible
 *
 *  @todo test the code extensively
 */

#pragma once

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

struct bitvec
{
    //! The size of the bit vector
    size_t size;

    //! How many bytes were allocated
    size_t alloc;

    //! The actual bits
    char *data;
};

typedef struct bitvec bitvec_t;

/* BASIC DATA ACCESS */

size_t bitvec_size(const bitvec_t *list);

void *bitvec_first(const bitvec_t *list);

void *bitvec_last(const bitvec_t *list);

int bitvec_count(const bitvec_t *vec);

/* CREATION/DESTRUCTION FUNCTIONS */

bitvec_t *bitvec_new(size_t size);

bitvec_t *bitvec_init(bitvec_t *list, size_t size, bool val);

bitvec_t *bitvec_resize(bitvec_t *vec, size_t size, bool val);

bitvec_t *bitvec_purge(bitvec_t *list);

int     bitvec_free (bitvec_t *list);

void *bitvec_append (bitvec_t *list, bool val);

void *bitvec_prepend(bitvec_t *list, bool val);

void *bitvec_insert (bitvec_t *list, size_t pos, bool data);

int   bitvec_remove (bitvec_t *list, size_t pos);

void *bitvec_set(bitvec_t *list, size_t pos, bool data);

void bitvec_flip(bitvec_t *vec, size_t pos);

bool bitvec_get(const bitvec_t *list, size_t pos);

int bitvec_swap(bitvec_t *list, size_t a, size_t b);

char *bitvec_raw(bitvec_t *vec);

bitvec_t *bitvec_split(bitvec_t *list, size_t pos);

bitvec_t *bitvec_join(bitvec_t *dest, bitvec_t *src);

bitvec_t *bitvec_copy(const bitvec_t *list);

int bitvec_compare(bitvec_t *a, bitvec_t *b, bitvec_compare_elements *cmp);

int bitvec_verify(const bitvec_t *list);

#ifdef __cplusplus
}
#endif
