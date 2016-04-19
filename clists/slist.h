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
 *  Design Specifications
 *  - implementation of single linked lists in C
 *  - simple
 *  - efficient
 *  - intuitive
 *  - stores data in place but can also be used to store
 *    arbitrary pointers
 *
 *  Implementation
 *  => slist_t
 *   - used to represent a linked list
 *   - stores some important parameters (head of list, size of data)
 *   - stores additional data for efficiency (tail of list, length)
 *  => slist_node_t
 *   - actual list node
 *   - stores pointer to next node as well as a user-defined amount
 *     of arbitrary data
 *   - ideally not exposed to user
 *
 *  ToDo
 *   - implement map/reduce functions (?)
 *   - test things
 *   - make it thread safe
 */

#pragma once

#include <stdlib.h>
#include <string.h>

/* forward declaration of data types, since dlist
 * has functions working on them they need to be
 * declared before including the header
 */
typedef struct slist      slist_t;
typedef struct slist_node slist_node_t;

#include "dlist.h"

/* simple data access functions are implemented as macros for speed */
#define slist_size(list) ((list) ? (list)->size : 0)
#define slist_first(list) (((list)->head) ? (list)->head->data : NULL)
#define slist_last(list) (((list)->tail) ? (list)->tail->data : NULL)

/*  foreach loop implementation for slist, use like this, assuming the
 *  list that is to be iterated is called 'list' and of type slist_t*:
 *
 *  FIXME: this is broken right now due to a change in the way the
 *  data is handled in the lists.
 *
 *      void *item;
 *      slist_foreach(list, item) {
 *          printf("%p", item);
 *      }
#define slist_foreach(list, __data) \
    for(void *__node = list->head, *__data = ((list->head) ? \
                list->head->data : \
                NULL); \
            __node != NULL; \
            __data = ((__node = (void*)((slist_node_t*)__node)->next) ? \
                ((slist_node_t*)__node)->data : \
                NULL))
*/

#ifdef __cplusplus
extern "C" {
#endif

/*  the key feature of single linked lists is that the data
 *  is represented by nodes, each node posessing a pointer to
 *  the next node. this is the node structure used by slist.
 *
 *  FIXME: zero length array is kinda iffy. can we do this better?
 */
struct slist_node
{
    struct slist_node *next;
    char data[0];
};

/*  the main slist struct. it stores a pointer to the first
 *  and the last nodes in the list, as well as the size of
 *  the list (since obtaining that is computationally expensive
 *  linear to the size of the list, as all nodes need to be
 *  traversed)
 *
 *  FIXME: length and size may be confusing. (one is length of
 *  the list, the other is the size of the arbitrary data in
 *  each node).
 */
struct slist
{
    // head of the list (first node)
    struct slist_node *head;

    // tail of the list (last node, for efficiency)
    struct slist_node *tail;

    // length of the list (how many nodes, for for efficency)
    size_t length;

    // size of data in each node (same for all nodes)
    size_t size;
};

/*  creation/destruction functions
 *
 *  the new function creates a new slist object on the heap
 *   (using malloc), initializes it and returns a pointer to
 *   it. 
 *  this object (as well as all the nodes) can be freed
 *   using the free function.
 *
 *  init is meant for initializing an slist object, for
 *   example a stack object. 
 *  the purge function works like the free function, but it 
 *   only frees the nodes and not the memory of the object 
 *   itself.
 */
slist_t *slist_new  (size_t size);
int      slist_init (slist_t *list, size_t size);
int      slist_purge(slist_t *list);
int      slist_free (slist_t *list);

/*  insertion and removal of data from a list
 *
 *  append adds data to the end of the list.
 *  prepend adds data to the beginning of the list,
 *   shifting everything to the right.
 *  insert adds data in between existing data.
 *   elements (so that the new element is as pos and
 *   everything after it is shifted one to the right).
 *  remove shifts all data after the element one to the
 *   left.
 */
int slist_append (slist_t *list, void *data);
int slist_prepend(slist_t *list, void *data);
int slist_insert (slist_t *list, size_t pos, void *data);
int slist_remove (slist_t *list, size_t pos);

/* data setting/accessing functions
 *
 * get returns the data at pos
 * pop removes and returns the first element of the list
 * set changes the data at pos to the supplied value
 */
int   slist_set(slist_t *list, size_t pos, void *data);
void *slist_get(slist_t *list, size_t pos);
void *slist_pop(slist_t *list);

/* list mangling functions
 * chop splits the list, leaving elements [0,pos-1] in the
 *  original list and returning [pos,...] as a new one
 * join adds all data from src to dest, leaving src as an
 *  empty list, and returns dest.
 */
slist_t *slist_chop(slist_t *list, size_t pos);
slist_t *slist_join(slist_t *dest, slist_t *src);

/*  conversion functions
 *  copy creates a new slist with the same data as the
 *   one it is passed. 
 *  the from_* functions convert some other data type
 *   to a slist.
 *  the to_array function returns a pointer to an array
 *   that contains the same data as is in the slist. this
 *   array needs to be freed by the user.
 */
slist_t *slist_copy      (slist_t *list);
slist_t *slist_from_dlist(dlist_t *list);
slist_t *slist_from_array(void   **array, size_t length, size_t size);
void   **slist_to_array  (slist_t *list);

#ifdef __cplusplus
}
#endif
