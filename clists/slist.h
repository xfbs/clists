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

/*! List node.
 *
 *  Stores some (variable length) data as well as a pointer
 *  to the next node in the list.
 *
 *  When `next` is non-NULL, it means that there are more
 *  elements, if it is NULL, it means that we've hit the
 *  end of the list.
 *
 *  FIXME: zero length array is kinda iffy. can we do this better?
 */
struct slist_node
{
    //! pointer to next node in list
    struct slist_node *next;

    //! variable length data
    char data[0];
};

/*! The main slist struct. 
 *
 *  It stores a pointer to the first
 *  and the last nodes in the list, as well as the size of
 *  the list (since obtaining that is computationally expensive
 *  linear to the size of the list, as all nodes need to be
 *  traversed)
 *
 *  The list has some redundant data such as the length and
 *  a pointer to the last node for efficiency reasons.
 *
 *  The list is not circular.
 */
struct slist
{
    //! head of the list (first node)
    struct slist_node *head;

    //! tail of the list (last node, for efficiency)
    struct slist_node *tail;

    //! length of the list (how many nodes, for for efficency)
    size_t length;

    //! size of data in each node (same for all nodes)
    size_t size;
};

/* CREATION/DESTRUCTION FUNCTIONS */

/*! Creates a new slist_t object on the heap with 
 *  elements of the given size.
 *  
 *  @param size the size of the elements that this
 *      list contains
 *  @return a pointer to the allocated list
 *
 *  ### Error Handling
 *
 *  Returns NULL on error.
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
 */
slist_t *slist_new(size_t size);

/*! Initializes a given slist object for use with
 *  objects of the given size.
 *
 *  Assumes that the list is either uninitialized
 *  or empty. If not, it will leak memory!
 *
 *  @param list the list to be initialized
 *  @param size the size of the elements that the
 *      list should hold
 *  @return a pointer to the initialized list
 *
 *  ### Error Handling
 *
 *  Returns NULL on error.
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
 */
slist_t *slist_init(slist_t *list, size_t size);

/*! Takes an existing (already initialized) list,
 *  removes all its elements and frees it.
 *
 *  Make sure that the list has been initialized,
 *  otherwise this function will cause undefined
 *  behavior!
 *
 *  @param list the list to be purged
 *  @return the purged list
 *
 *  ### Error Handling
 *
 *  Returns NULL in case of error.
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
 */
slist_t *slist_purge(slist_t *list);

/*! Takes an existing list that has been allocated 
 *  on the heap (for example withwith slist_new()),
 *  free()s all of the data and then the list itself.
 *
 *  Make sure to call this on lists that are
 *  that have been allocated on the heap (not on the
 *  stack) as this function will call `free()` on
 *  them!
 *
 *  @param list the list to free
 *  @return 0 on success
 *
 *  ### Error Handling
 *
 *  In case of an error, it will return a negative
 *  value.
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
int     slist_free (slist_t *list);

/*! Appends some data to the end of a list.
 *
 *  This function returns a pointer to the
 *  newly created element. Please note that
 *  this pointer is only valid until the next
 *  mutating library call.
 *
 *  @param list the list to append data to
 *  @param data the data to append, or NULL
 *  @return a pointer to the newly created element
 *
 *  ### Error Handling
 *
 *  In case of an error, this function returns
 *  NULL instead of a pointer to the newly created
 *  element.
 *
 *  ### Example
 *
 *  ```c
 *  slist_t *list = slist_new(sizeof(int));
 *
 *  // append using data pointer
 *  int d = 5;
 *  if(NULL == slist_append(list, &d)) {
 *      // error!
 *  }
 *
 *  // append manually
 *  void *ptr = slist_append(list, NULL);
 *  if(ptr != NULL) {
 *      int *p = ptr;
 *      *p = 5;
 *  } else {
 *      // error!
 *  }
 *  ```
 */
void *slist_append (slist_t *list, void *data);

/*! Prepends some data to the beginning of
 *  a list.
 *
 *  This function returns a pointer to the
 *  newly created element on success. Please
 *  note that this pointer is only valid until
 *  the next mutating library call!
 *
 *  @param list the list to prepend to
 *  @param the data to prepend, or NULL
 *  @return a pointer to the newly created
 *      element
 *
 *  ### Error Handling
 *
 *  Returns NULL on error.
 *
 *  ### Example
 *
 *  ```c
 *  slist_t *list = slist_new(sizeof(int));
 *
 *  // prepend using data pointer
 *  int d = 5;
 *  if(NULL == slist_prepend(list, &d)) {
 *      // error!
 *  }
 *
 *  // prepend manually
 *  void *ptr = slist_prepend(list, NULL);
 *  if(ptr != NULL) {
 *      int *p = ptr;
 *      *p = 5;
 *  } else {
 *      // error!
 *  }
 *  ```
 */
void *slist_prepend(slist_t *list, void *data);

/*! Inserts an element at the given position.
 *  
 *  The function inserts a new element at `pos`. If
 *  a non-NULL pointer `data` is passed, then
 *  whatever it is pointing at is copied into the
 *  element, otherwise the element is not initialized
 *  and it should be assumed to contain random garbage.
 *
 *  This function returns a pointer to the newly
 *  inserted element. Please note that this pointer
 *  is only valid until the next mutating library
 *  call.
 *
 *  @param list the list to insert data to
 *  @param pos the position to insert that data in
 *  @param data the data to insert, or `NULL`
 *  @return a pointer to the inserted element
 *
 *  ### Error Handling
 *
 *  Returns NULL on error.
 *
 *  ### Example
 *
 *  ```c
 *  slist_t *list = slist_new(sizeof(int));
 *
 *  // insert at beginning
 *  int d = 5;
 *  if(NULL == slist_insert(list, 0, &d)) {
 *      // error!
 *  }
 *
 *  // insert at end
 *  if(NULL == slist_insert(list, 1, &d)) {
 *      // error!
 *  }
 *
 *  // insert manually in middle
 *  void *ptr = slist_insert(list, 1, NULL);
 *  if(ptr != NULL) {
 *      int *p = ptr;
 *      *p = 5;
 *  } else {
 *      // error!
 *  }
 *  ```
 */
void *slist_insert (slist_t *list, size_t pos, void *data);

/*! Removes a given element from the list.
 *  
 *  This function attempts to remove the element
 *  at pos. 
 *
 *  @param[in] list the list to remove the element
 *      from
 *  @param[in] pos the position of the item to remove
 *  @return 0 on success
 *
 *  ### Error Handling
 *
 *  If the element does not exist, it returns a
 *  negative integer.
 *
 *  ### Example
 *
 *  ```c
 *  slist_t *list = slist_new(sizeof(int));
 *
 *  int i = 5;
 *  slist_append(list, &i);
 *  slist_append(list, &i);
 *  slist_append(list, &i);
 *
 *  // element does not exist
 *  assert(slist_remove(list, 6) < 0);
 *
 *  assert(slist_remove(list, 2) == 0);
 *  assert(slist_remove(list, 0) == 0);
 *  ```
 */
int   slist_remove (slist_t *list, size_t pos);

/*! Sets the data of the element at the given index.
 *
 *  If the element exists, it returns a pointer to it
 *  that can be used to set the data, otherwise it
 *  returns `NULL`.
 *
 *  If you pass a non-NULL pointer `data`, it's contents
 *  are copied into the element, otherwise it is ignored.
 *
 *  @param[in, out] list the list to work on
 *  @param[in] pos the position of the element to set
 *  @param[in] data optionally, a non-`NULL` pointer to
 *      some data that is copied into the element
 *  @return a pointer to the element, or NULL on error
 *
 *  ```c
 *  slist_t *list = slist_new(sizeof(int));
 *
 *  // fill up the list
 *  int i = 5;
 *  slist_append(list, &i);
 *  slist_append(list, &i);
 *  slist_append(list, &i);
 *
 *  // set second element to 6
 *  i = 6;
 *  assert(slist_set(list, 1, &i) != NULL);
 *  ```
 */
void *slist_set(slist_t *list, size_t pos, void *data);

/*! Gets a pointer to the data at pos.
 *
 *  This function will return a pointer to the element
 *  at `pos`, or `NULL` on error.
 *
 *  @param list the list to work on
 *  @param pos the position of the element to
 *      retrieve
 *  @return a pointer to the element, or NULL on error
 *
 *  ### Example
 *
 *  ```c
 *  slist_t *list = slist_new(sizeof(int));
 *
 *  // add an element
 *  int five = 5;
 *  assert(slist_append(list, &five) != NULL);
 *
 *  // get the element
 *  int *elem = slist_get(list, 0);
 *  assert(elem != NULL);
 *  assert(*elem == five);
 *
 *  // accessing nonexisting element produces NULL
 *  assert(slist_get(list, 1) == NULL);
 *  ```
 */
void *slist_get(slist_t *list, size_t pos);

/*! Removes the first element of the list.
 *
 *  If a non-NULL `data` pointer is provided, 
 *  the data of the popped element will be 
 *  stored there. In that case, a pointer to
 *  it is returned on success, or NULL on
 *  error.
 *
 *  @param list the list to work on
 *  @param data optionally, a non-NULL pointer
 *      to store the data of the popped element in
 *  @return if data was non-NULL, returns data on
 *      success and NULL on failure
 *
 *  ### Example
 *
 *  ```c
 *  slist_t *list = slist_new(sizeof(int));
 *  assert(list != NULL);
 *
 *  // fill up list a bit
 *  int five = 5;
 *  assert(slist_append(list, &five) != NULL);
 *  assert(slist_append(list, &five) != NULL);
 *  assert(slist_length(list) == 2);
 *
 *  // pop the first element
 *  assert(slist_pop(list, NULL);
 *  assert(slist_length(list) == 2);
 *
 *  // pop the second element, saving the data
 *  int data;
 *  assert(slist_pop(list, &data) != NULL);
 *  assert(slist_length(list) == 0);
 *  assert(data == five);
 *  ```
 */
void *slist_pop(slist_t *list, void *data);

/*! Splits the list into two lists, so that the
 *  element at pos is the first element of the
 *  second (split-off) list. 
 *
 *  The list that is passed gets truncated to 
 *  only contain all elements up to pos, and it
 *  returns a pointer to the newly created list,
 *  or NULL on failure.
 *
 *  @param list the list to split
 *  @param pos the position of the first element of the
 *      resulting split list.
 *  @return a new list containing all elements starting
 *      at pos from the passed list
 *
 *  ### Example
 *
 *  ```c
 *  slist_t *list = slist_new(sizeof(int));
 *  assert(list != NULL);
 *
 *  int two = 2;
 *  assert(slist_append(list, &two) != NULL);
 *  assert(slist_append(list, &two) != NULL);
 *  assert(slist_append(list, &two) != NULL);
 *  assert(slist_append(list, &two) != NULL);
 *  assert(slist_length(list) == 4);
 *
 *  slist_t *half = slist_split(list, 2);
 *  assert(slist_length(list) == 2);
 *  assert(slist_length(half) == 2);
 *  ```
 */
slist_t *slist_split(slist_t *list, size_t pos);

/*! Joins two lists together to one big one.
 *
 *  This function copies all elements from `src`
 *  into `dest`, leaving `src` as an empty list.
 *
 *  @param dest the list to add all elements from
 *      src to
 *  @param src the list from which the elements
 *      are taken
 *  @return dest on success, or NULL on error
 *
 *  ### Example
 *
 *  ```c
 *  slist_t *one = slist_new(sizeof(int));
 *  assert(one != NULL);
 *  slist_t *two = slist_new(sizeof(int));
 *  assert(two != NULL);
 *
 *  int number = 2;
 *  
 *  assert(slist_append(one, &number) != NULL);
 *  assert(slist_append(one, &number) != NULL);
 *  assert(slist_length(one) == 2);
 *
 *  assert(slist_append(two, &number) != NULL);
 *  assert(slist_append(two, &number) != NULL);
 *  assert(slist_length(two) == 2);
 *  
 *  assert(slist_join(one, two) != NULL);
 *  assert(slist_length(one) == 4);
 *  assert(slist_length(two) == 0);
 *  ```
 */
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
/*! Creates a copy of a list
 *
 *  This function creates a new list, and fills
 *  it up by copying all the elements of the
 *  list passed as parameter.
 *
 *  @param list the list to copy
 *  @return a copy of the list passed as parameter,
 *      or NULL on error
 *
 *  ### Error Handling
 *
 *  Returns NULL on error.
 *
 *  ### Example
 *
 *  ```c
 *  slist_t *list = slist_new(sizeof(int));
 *  assert(list != NULL);
 *
 *  int number = 8;
 *  assert(slist_append(list, &number) != NULL);
 *  assert(slist_append(list, &number) != NULL);
 *  assert(slist_append(list, &number) != NULL);
 *  assert(slist_length(list) == 3);
 *
 *  slist_t *copy = slist_copy(list);
 *  assert(slist_length(copy) == 3);
 *  ```
 */
slist_t *slist_copy(const slist_t *list);

#ifdef __cplusplus
}
#endif
