/*! @file alist.h
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
#include "dlist.h"

#ifdef __cplusplus
extern "C" {
#endif

struct alist_element
{
    size_t size;
    size_t used;
    char data[0];
};

typedef struct alist_node alist_node_t;

struct alist
{
    dlist_t list;
};

typedef struct alist alist_t;

typedef int alist_compare_elements(void *a, void *b);

/* BASIC DATA ACCESS */

size_t alist_size(const alist_t *list);

size_t alist_length(const alist_t *list);

void *alist_first(const alist_t *list);

void *alist_last(const alist_t *list);

/* CREATION/DESTRUCTION FUNCTIONS */

alist_t *alist_new(size_t size);

alist_t *alist_init(alist_t *list, size_t size);

alist_t *alist_purge(alist_t *list);

int     alist_free (alist_t *list);

void *alist_append (alist_t *list, const void *data);

void *alist_prepend(alist_t *list, const void *data);

void *alist_insert (alist_t *list, size_t pos, const void *data);

int   alist_remove (alist_t *list, size_t pos);

void *alist_set(alist_t *list, size_t pos, const void *data);

void *alist_get(const alist_t *list, size_t pos, void *data);

void *alist_pop(alist_t *list, void *data);

int alist_swap(alist_t *list, size_t a, size_t b);

alist_t *alist_split(alist_t *list, size_t pos);

alist_t *alist_join(alist_t *dest, alist_t *src);

alist_t *alist_copy(const alist_t *list);

int alist_compare(alist_t *a, alist_t *b, alist_compare_elements *cmp);

int alist_verify(const alist_t *list);

#ifdef __cplusplus
}
#endif
