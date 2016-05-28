/*  File: bitvec.c
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

#include "clists/bitvec.h"
#include <assert.h>

/* BASIC DATA ACCESS */

size_t bitvec_size(const bitvec_t *vec) {
    return vec->size;
}

size_t bitvec_count(const bitvec_t *vec) {
    // TODO
    return 0;
}

bitvec_word *bitvec_raw(bitvec_t *vec) {
    return vec->data;
}

/* CREATION/DESTRUCTION FUNCTIONS */

bitvec_t *bitvec_new(size_t size, bool val) {
    bitvec_t *vec = malloc(sizeof(bitvec_t));

    // make sure allocation worked
    if(vec == NULL) {
        return NULL;
    }

    // set the size
    vec->size = size;

    // calculate how many bitvec_words we need,
    // looks awkward because we need to round
    // up.
    vec->alloc = (size + sizeof(bitvec_word) - 1) / sizeof(bitvec_word);

    // alloc being 0 can only happen when size is 0.
    if(vec->alloc == 0) {
        vec->data = NULL;
        return vec;
    }

    // allocate data
    vec->data = malloc(vec->alloc * sizeof(bitvec_word));

    // make sure the allocation worked
    if(vec->data == NULL) {
        free(vec);
        return NULL;
    }

    // initialise the bits
    if(val == false) {
        memset(vec->data, 0, sizeof(bitvec_word) * vec->alloc);
    } else {
        memset(vec->data, 255, sizeof(bitvec_word) * vec->alloc);
    }

    return vec;
}

bitvec_t *bitvec_init(bitvec_t *vec, size_t size, bool val) {
    // set size and calculate how many bitvec_words
    // we need for the given size
    vec->size = size;
    vec->alloc = (size + sizeof(bitvec_word) - 1) / sizeof(bitvec_word);

    // if alloc is 0, size muse be 0, and we're done.
    if(vec->alloc == 0) {
        vec->data = NULL;
        return vec;
    }

    // allocate data
    vec->data = malloc(vec->alloc * sizeof(bitvec_word));

    // make sure the allocation worked
    if(vec->data == NULL) {
        return NULL;
    }

    // initialise the bits
    if(val == false) {
        memset(vec->data, 0, sizeof(bitvec_word) * vec->alloc);
    } else {
        memset(vec->data, 255, sizeof(bitvec_word) * vec->alloc);
    }

    return vec;
}

bitvec_t *bitvec_resize(bitvec_t *vec, size_t size, bool val);

bitvec_t *bitvec_purge(bitvec_t *vec);

int bitvec_free(bitvec_t *vec) {
    if(vec->data != NULL) {
        free(vec->data);
    }

    free(vec);

    return 0;
}

/* INSERTION/REMOVAL OF BITS */

void *bitvec_append (bitvec_t *vec, bool val);

void *bitvec_prepend(bitvec_t *vec, bool val);

void *bitvec_insert (bitvec_t *vec, size_t pos, bool data);

int   bitvec_remove (bitvec_t *vec, size_t pos);

/* ACCESS/MODIFICATION OF BITS */

int bitvec_set(bitvec_t *vec, size_t pos, bool data);

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
