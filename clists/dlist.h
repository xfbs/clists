/*  File: dlist.h
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

#ifndef _DLIST_H
#define _DLIST_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dlist_node
{
    struct dlist_node *prev;
    struct dlist_node *next;
    void *data;
} dlist_node_t;

typedef struct dlist
{
    struct dlist_node *head;
    struct dlist_node *tail;
    size_t size;
} dlist_t;

#define dlist_size(list) ((list) ? (list)->size : 0)
#define dlist_first(list) (((list)->head) ? (list)->head->data : NULL)
#define dlist_last(list) (((list)->tail) ? (list)->tail->data : NULL)

dlist_t *dlist_new();
int dlist_init(dlist_t *);
int dlist_purge(dlist_t *);
int dlist_free(dlist_t *);

int dlist_append(dlist_t *, void *);
int dlist_prepend(dlist_t *, void *);
int dlist_insert(dlist_t *, size_t, void *);
int dlist_set(dlist_t *, size_t, void *);

void *dlist_get(dlist_t *, size_t);
void *dlist_pop(dlist_t *);
void *dlist_poll(dlist_t *);
void *dlist_remove(dlist_t *, size_t);

int dlist_equal(dlist_t *, dlist_t *);
int dlist_merge(dlist_t *, dlist_t *);
dlist_t *dlist_copy(dlist_t *);
//dlist_node *dlist_node_get(dlist *list, size_t pos);

#ifdef __cplusplus
}
#endif
#endif
