/*! File: slist.h
 *  @file slist.h
 *  @author Patrick Elsen
 *  @date 9 Sep 2012
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
typedef struct slist      slist_t;
typedef struct slist_node slist_node_t;
#include "dlist.h"

/* simple data access functions are implemented as macros for speed */
#define slist_size(list) ((list) ? (list)->size : 0)
#define slist_length(list) ((list) ? (list)->length : 0)
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

/* CREATION/DESTRUCTION FUNCTIONS */

/*! Creates a new slist_t object on the heap with 
 *  elements of the given size.
 *  
 *  ### Example
 *
 *  ```c
 *  slist_t *list = slist_new(sizeof(int));
 *
 *  if(list == NULL) {
 *      // error!
 *  }
 *  ```
 *
 *  @param size the size of the elements that this
 *      list contains
 *  @return returns a pointer to the allocated list
 *      or NULL in case there has been an error
 */
slist_t *slist_new  (size_t size);

/*! Initializes a given slist object for use with
 *  objects of the given size.
 *
 *  If the list contains data, it should be
 *  slist_purge()'d first, otherwise it will
 *  leak memory.
 *
 *  ### Example
 *
 *  ```c
 *  slist_t list;
 *  
 *  if(NULL == slist_init(&list, sizeof(int))) {
 *      // error!
 *  }
 *  ```
 *
 *  @param list the list to be initialized
 *  @param size the size of the elements that the
 *      list should hold
 *  @return a pointer to the initialized list on
 *      success, or NULL on error
 */
slist_t *slist_init (slist_t *list, size_t size);

/*! Takes an existing (already initialized) list,
 *  removes all it's elements and frees it.
 *
 *  Make sure that the list has been initialized
 *  and that it has been allocated (is not on the
 *  stack) as this function will call `free()` on
 *  it!
 *
 *  ### Example
 *
 *  ```c
 *  slist_t list;
 *  slist_init(&list, sizeof(int));
 *  
 *  int i = 5;
 *  slist_append(list, &i);
 *
 *  if(NULL == slist_purge(list)) {
 *      // error!
 *  }
 *  ```
 *
 *  @param list the list to be purged
 *  @return the purged list or NULL on error
 */
slist_t *slist_purge(slist_t *list);

/*! Takes an existing list that has been allocated 
 *  on the heap (for example withwith slist_new()),
 *  free()s all of the data and then the list itself.
 *
 *  Make sure not to call this on lists that are
 *  on the stack!
 *
 *  ### Example
 *
 *  ```c
 *  slist_t *list = slist_new(sizeof(int));
 *  
 *  int i = 5;
 *  slist_append(list, &5);
 *
 *  if(0 != slist_free(list)) {
 *      // error!
 *  }
 *  ```
 */
int      slist_free (slist_t *list);

/* insertion and removal of data from a list
 *
 * slist_append(list, data) appends data to the end
 *  of the list. if data is not NULL, it copies from
 *  the data, otherwise it does not initialize the
 *  new data. it returns a pointer to the data on
 *  success, and NULL on error.
 *
 * slist_prepend(list, data) prepends data to the
 *  beginning of the list. if data is not NULL, it
 *  copies the given data into the list, otherwise
 *  it does not initialize the new data. it returns
 *  a pointer to the new data on success, and NULL
 *  on error.
 *
 * slist_insert(list, pos, data) inserts data at a 
 *  given position in the list. if data is not NULL,
 *  it copies the content over, otherwise it does
 *  not initialize it. returns a pointer to the new
 *  data on success, and NULL on error.
 *
 * remove(list, pos) removes a given element from
 *  the list.
 */
void *slist_append (slist_t *list, void *data);
void *slist_prepend(slist_t *list, void *data);
void *slist_insert (slist_t *list, size_t pos, void *data);
int   slist_remove (slist_t *list, size_t pos);

/* data setting/accessing functions
 *
 * slist_set(list, pos, data) sets the element at pos
 *  to the given data, if data is not NULL. it returns
 *  a pointer to the data in any case, or NULL if 
 *  there has been an error.
 *
 * slist_get(list, pos) returns a pointer to the data
 *  at pos.
 *
 * slist_pop(list, data) removes the first element of
 *  the list, writing it's data to the data (if it
 *  isn't NULL). it returns a pointer to the data
 *  on success, or NULL on error.
 *
 * TODO: add an unshift method (same as pop, but
 * takes from the end)
 */
void *slist_set(slist_t *list, size_t pos, void *data);
void *slist_get(slist_t *list, size_t pos);
void *slist_pop(slist_t *list, void *data);

/* list mangling functions
 *
 * slist_chop(list, pos) splits the list, leaving elements 
 *  upto pos in the original list and from pos to the
 *  end in a new one.
 *
 * slist_join(dest, src) adds all data from src to dest, 
 *  leaving src as an empty list, and returns dest or
 *  NULL on error.
 */
slist_t *slist_split(slist_t *list, size_t pos);
slist_t *slist_join(slist_t *dest, slist_t *src);

/*  conversion functions
 *  copy creates a new slist with the same data as the
 *   one it is passed. 
 *  the from_* functions convert some other data type
 *   to a slist.
 *  the to_array function returns a pointer to an array
 *   that contains the same data as is in the slist. this
 *   array needs to be freed by the user.
 *
 *  FIXME: conversion functions from/to array
 */
slist_t *slist_copy      (slist_t *list);
slist_t *slist_from_dlist(dlist_t *list);

#ifdef __cplusplus
}
#endif
