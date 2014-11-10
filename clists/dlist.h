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
 *
 *  Design Specifications
 *  - implementation of double linked lists in C
 *  - simple
 *  - efficient
 *  - intuitive
 *  - stores void pointers for maximum flexibility
 *
 *  Implementation
 *  => dlist_t
 *   - central double linked list datatype
 *   - stores some parameters for efficiency (size, tail node)
 *  => dlist_node_t
 *   - actual double linked list node
 *   - not typically 'seen' by user
 *   - automatically allocated/freed on insertion/deletion
 */

#ifndef _DLIST_H
#define _DLIST_H

#include <stdlib.h>
#include <string.h>

/* simple data access functions are implemented as macros for speed */
#define dlist_size(list) ((list) ? (list)->size : 0)
#define dlist_first(list) (((list)->head) ? (list)->head->data : NULL)
#define dlist_last(list) (((list)->tail) ? (list)->tail->data : NULL)
#define dlist_foreach(list, __data) \
    for(void *__node = list->head, *__data = ((list->head) ? \
                list->head->data : \
                NULL); \
            __node != NULL; \
            __data = ((__node = (void*)((dlist_node_t*)__node)->next) ? \
                ((dlist_node_t*)__node)->data : \
                NULL))
#define dlist_foreach_backwards(list, __data) \
    for(void *__node = list->tail, *__data = ((list->tail) ? \
                list->tail->data : \
                NULL); \
            __node != NULL; \
            __data = ((__node = (void*)((dlist_node_t*)__node)->prev) ? \
                ((dlist_node_t*)__node)->data : \
                NULL))

#ifdef __cplusplus
extern "C" {
#endif

/* double linked lists are made up of nodes, which apart
 * from data have pointers to the previous and the next
 * node. this allows efficient forwards/backwards traversal,
 * and since the nodes are linked only by pointers, deletion
 * and insertion are also constant-time functions. this is
 * the central node structure for double linked lists:
 */
typedef struct dlist_node
{
    struct dlist_node *prev;
    struct dlist_node *next;
    void *data;
} dlist_node_t;

/* this is the dlist datatype, the one that is being 'handled'
 * by the user. it contains pointers to the first and last
 * nodes (this is done for efficiency) as well as the size of
 * the list (again, for efficiency). the library functions
 * work with pointers to this structure
 */
typedef struct dlist
{
    struct dlist_node *head;
    struct dlist_node *tail;
    size_t size;
} dlist_t;

/* dlist creation/destruction functions
 */
dlist_t *dlist_new  (void);
int      dlist_init (dlist_t *list);
int      dlist_purge(dlist_t *list);
int      dlist_free (dlist_t *list);

int dlist_append (dlist_t *list, void *data);
int dlist_prepend(dlist_t *list, void *data);
int dlist_insert (dlist_t *list, size_t pos, void *data);
int dlist_remove (dlist_t *list, size_t pos);


int   dlist_set(dlist_t *list, size_t pos, void *data);
void *dlist_get(dlist_t *list, size_t pos);
void *dlist_pop(dlist_t *list);

dlist_t *dlist_chop(dlist_t *list, size_t pos);
dlist_t *dlist_join(dlist_t *dest, slist_t *src);

dlist_t *dlist_copy      (dlist_t *list);
dlist_t *dlist_from_slist(slist_t *list);
dlist_t *dlist_from_array(void   **array, size_t size);
void   **dlist_to_array  (dlist_t *list);

#ifdef __cplusplus
}
#endif
#endif
