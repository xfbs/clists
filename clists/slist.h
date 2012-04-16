/*  File: slist.h
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


#ifndef _SLIST_H
#define _SLIST_H

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct slist_node
{
    struct slist_node *next;
    void *data;
} slist_node_t;

typedef struct slist
{
    struct slist_node *head;
    struct slist_node *tail;
    size_t size;
} slist_t;

#define slist_size(list) ((list) ? (list)->size : 0)
#define slist_first(list) (((list)->head) ? (list)->head->data : NULL)
#define slist_last(list) (((list)->tail) ? (list)->tail->data : NULL)

slist_t *slist_new();
int slist_init(slist_t *list);
int slist_purge(slist_t *list);
int slist_free(slist_t *list);

int slist_append(slist_t *list, void *data);
int slist_prepend(slist_t list*, void *data);
int slist_insert(slist_t *list, size_t pos, void *data);
int slist_remove(slist_t *list, size_t pos);
int slist_set(slist_t *list, size_t pos, void *data);

void *slist_get(slist_t *list, size_t) pos;
void *slist_pop(slist_t *list);

int slist_equal(slist_t *lista, slist_t *listb);
int slist_merge(slist_t *dst, slist_t *src);
slist_t *slist_copy(slist_t *list);
//slist_node_t *slist_get_node(slist_t *list, size_t pos);

#ifdef __cplusplus
}
#endif
#endif /* include guard */
