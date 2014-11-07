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
 *
 *  ==About==
 *  SList is an implementation of a single linked list, in which
 *  nodes have a pointer to the next node, thereby linking them.
 *  Technically, you only need to know the position of the first
 *  node to work with a single linked list, but in this implementation
 *  single linked lists are represented with a dedicated data
 *  structure (slist_t), which stores not only the first node,
 *  but also the last node as well as the list size. This is done
 *  for efficiency, as otherwise the whole list has to be traversed
 *  to know it's size.
 *
 *  All functions that work with the SList data structure take a
 *  pointer to an slist struct (slist_t*). Such a pointer can come
 *  from the slist_new() function, which creates a new object on
 *  the heap, initializes it and returns it's pointer, or an object
 *  on the stack can be initialized with slist_init(&obj). See the
 *  following examples:
 *  
 *      // create an slist on the heap (internally uses malloc)
 *      slist_t *one = slist_new();
 *
 *      // create an slist on the stack and initialize it
 *      slist_t two;
 *      slist_init(&two);
 *
 *      // add some data to both lists
 *      int num = 6;
 *      slist_append(one,  (void*)&num);
 *      slist_append(&two, (void*)&num);
 *
 *  For more information, see the comments above each function or
 *  in the implementation.
 */

#ifndef _SLIST_H
#define _SLIST_H

#include <stdlib.h>
#include <string.h>

#define slist_size(list) ((list) ? (list)->size : 0)
#define slist_first(list) (((list)->head) ? (list)->head->data : NULL)
#define slist_last(list) (((list)->tail) ? (list)->tail->data : NULL)
#define slist_foreach(list, __data) \
    for(void *__node = list->head, *__data = ((list->head) ? \
                list->head->data : \
                NULL); \
            __node != NULL; \
            __data = ((__node = (void*)((slist_node_t*)__node)->next) ? \
                ((slist_node_t*)__node)->data : \
                NULL))

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

slist_t *slist_new(void);
int slist_init(slist_t *list);
int slist_purge(slist_t *list);
int slist_free(slist_t *list);

int slist_append(slist_t *list, void *data);
int slist_prepend(slist_t *list, void *data);
int slist_insert(slist_t *list, size_t pos, void *data);
int slist_remove(slist_t *list, size_t pos);
int slist_set(slist_t *list, size_t pos, void *data);

void *slist_get(slist_t *list, size_t pos);
void *slist_pop(slist_t *list);

int slist_equal(slist_t *lista, slist_t *listb);
slist_t *slist_copy(slist_t *list);

// [TODO] converstion functions
//dlist_t *slist_to_dlist(slist_t *list);
//pvec_t *slist_to_pvec(slist_t *list);
void **slist_to_array(slist_t *list);

#ifndef slist_size
size_t slist_size(slist_t *list);
#endif

#ifndef slist_first
void *slist_first(slist_t *list);
#endif

#ifndef slist_last
void *slist_last(slist_t *list);
#endif

#ifdef __cplusplus
}
#endif
#endif /* include guard */
