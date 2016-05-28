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
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int bitvec_word;

struct bitvec
{
    //! The size of the bit vector
    size_t size;

    //! How many bitvec_words were allocated
    size_t alloc;

    //! The actual bits
    bitvec_word *data;
};

typedef struct bitvec bitvec_t;

/* BASIC DATA ACCESS */

size_t bitvec_size(const bitvec_t *vec);

size_t bitvec_count(const bitvec_t *vec);

bitvec_word *bitvec_raw(bitvec_t *vec);

/* CREATION/DESTRUCTION FUNCTIONS */

bitvec_t *bitvec_new(size_t size, bool val);

bitvec_t *bitvec_init(bitvec_t *vec, size_t size, bool val);

bitvec_t *bitvec_resize(bitvec_t *vec, size_t size, bool val);

bitvec_t *bitvec_purge(bitvec_t *vec);

int     bitvec_free (bitvec_t *vec);

/* INSERTION/REMOVAL OF BITS */

void *bitvec_append (bitvec_t *vec, bool val);

void *bitvec_prepend(bitvec_t *vec, bool val);

void *bitvec_insert (bitvec_t *vec, size_t pos, bool data);

int   bitvec_remove (bitvec_t *vec, size_t pos);

/* ACCESS/MODIFICATION OF BITS */

int bitvec_set(bitvec_t *vec, size_t pos, bool data);

int bitvec_set_all(bitvec_t *vec, bool data);

void bitvec_flip(bitvec_t *vec, size_t pos);

bool bitvec_get(const bitvec_t *vec, size_t pos);

int bitvec_swap(bitvec_t *vec, size_t a, size_t b);

/* MODIFICATION OF BITVECS */

bitvec_t *bitvec_split(bitvec_t *vec, size_t pos);

bitvec_t *bitvec_join(bitvec_t *dest, bitvec_t *src);

bitvec_t *bitvec_copy(const bitvec_t *vec);

int bitvec_compare(bitvec_t *a, bitvec_t *b);

/* DEBUG METHODS */

int bitvec_verify(const bitvec_t *vec);

#ifdef __cplusplus
}
#endif
