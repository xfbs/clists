/*  File: pvec.h
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

#ifndef _PVEC_H
#define _PVEC_H

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pvec
{
    void **data;
    size_t size;
    size_t alloc;
} pvec_t;

pvec_t *pvec_new(size_t size);
pvec_t *pvec_copy(pvec_t *vec);
int pvec_init(pvec_t *vec);
int pvec_purge(pvec_t *vec);
int pvec_free(pvec_t *vec);
int pvec_equal(pvec_t *veca, pvec_t *vecb);
int pvec_reserve(pvec_t *vec, size_t size);

int pvec_append(pvec_t *vec, void *data);
int pvec_prepend(pvec_t *vec, void *data);
int pvec_insert(pvec_t *vec, size_t pos, void *data);
int pvec_remove(pvec_t *vec, size_t pos);
int pvec_set(pvec_t *vec, size_t pos, void *data);

void *pvec_get(pvec_t *vec, size_t pos);
void *pvec_pop(pvec_t *vec);

#ifdef __cplusplus
}
#endif
#endif /* include guard */
