/*  File: pvector.c
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

#include "clists/pvector.h"

pvec_t *pvec_new(size_t size)
{
    pvec_t *vec = malloc(sizeof(pvec_t));
    if(vec == NULL) {
        return NULL;
    }

    memset(vec, 0, sizeof(pvec_t));

    if(size != 0) {
        vec->data = malloc(size * sizeof(void*));
        if(vec->data != NULL) {
            vec->alloc = size;
        }
    }

    return vec;
}

pvec_t *pvec_copy(pvec_t *vec)
{
    pvec_t *cpy = pvec_new(vec->size);
    if(cpy == NULL || cpy->alloc < vec->size) {
        return NULL;
    }

    if(vec->size != 0) {
        memcpy(cpy->data, vec->data, vec->size * sizeof(void*));
        cpy->size = vec->size;
    }

    return cpy;
}

int pvec_init(pvec_t *vec)
{
    memset(vec, 0, sizeof(pvec_t));
    return 0;
}

int pvec_purge(pvec_t *vec)
{
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->alloc = 0;
    return 0;
}

int pvec_free(pvec_t *vec)
{
    int ret;
    ret = pvec_purge(vec);
    free(vec);
    return ret;
}

int pvec_equal(pvec_t *veca, pvec_t *vecb)
{
    if(veca->size != vecb->size) {
        return -1;
    }

    if(memcmp(veca->data, vecb->data, veca->size) != 0) {
        return -1;
    }

    return 0;
}

int pvec_reserve(pvec_t *vec, size_t size)
{
    return -1; // TODO
}

int pvec_append(pvec_t *vec, void *data)
{
    if(pvec_reserve(vec, vec->size + 1) != 0) {
        return -1;
    }

    vec->data[vec->size] = data;
    vec->size++;
    return 0;
}

int pvec_prepend(pvec_t *vec, void *data)
{
    if(pvec_reserve(vec, vec->size + 1) != 0) {
        return -1;
    }

    if(vec->size > 0) {
        memmove(&vec->data[1], &vec->data[0], vec->size * sizeof(void*));
    }

    vec->data[0] = data;
    vec->size++;
    return 0;
}

int pvec_insert(pvec_t *vec, size_t pos, void *data)
{
    if(pos == 0) {
        return pvec_prepend(vec, data);
    } else if(pos == vec->size) {
        return pvec_append(vec, data);
    } else {
        if(pvec_reserve(vec, vec->size + 1) != 0) {
            return -1;
        }

        memmove(&vec->data[pos+1], &vec->data[pos], vec->size - pos);
        vec->data[pos] = data;
        vec->size++;
    }

    return 0;
}

int pvec_remove(pvec_t *vec, size_t pos)
{
    memmove(&vec->data[pos], &vec->data[pos+1], vec->size - pos - 1);
    vec->size--;
    return 0;
}

int pvec_set(pvec_t *vec, size_t pos, void *data)
{
    if(pos >= vec->size) {
        return -1;
    } else {
        vec->data[pos] = data;
    }

    return 0;
}

void *pvec_get(pvec_t *vec, size_t pos)
{
    if(pos >= vec->size) {
        return NULL;
    } else {
        return vec->data[pos];
    }
}
