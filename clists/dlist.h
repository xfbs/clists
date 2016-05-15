/*! @file dlist.h
 *  @author Patrick Elsen
 *  @date 9 Sep 2012
 *  @copyright 2011
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
 *
 *  ### Design Specifications
 *  - implementation of double linked lists in C
 *  - simple
 *  - efficient
 *  - intuitive
 *  - flexible
 *
 *  @todo think about making dlist a circular linked list?
 *  @todo test the code extensively
 */

#ifndef _DLIST_H
#define _DLIST_H

#include <stdlib.h>
#include <string.h>

/*  macro foreach loop implementations for dlist
 *
 *  these macros can be used as foreach loops, with one going from
 *  beginning to end and one for traversing the list backwards (which
 *  is efficient because it's a doubly linked list, each node has a
 *  pointer to the previous node as well)
 *  assuming that list is of type dlist_t*, use them like this:
 *
 *      void *item;
 *      dlist_foreach(list, item) {
 *          printf("%p", item);
 *      }
 *
 *  for backwards traversal:
 *
 *      dlist_forach_backwards(list, item) {
 *          printf("%p", item);
 *      }
 */
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

/*! List node.
 *
 *  Stores some (variable length) data as well as pointers
 *  to the next and previous nodes in the list.
 *
 *  We know that a node is the last node if `next` is NULL,
 *  and we know that a node is the first node is `prev` is
 *  NULL.
 *
 *  @todo zero length array is kinda iffy, can we do this
 *      better?
 */
struct dlist_node
{
    //! pointer to previous node in the list
    struct dlist_node *prev;

    //! pointer to next node in the list
    struct dlist_node *next;

    //! variable length data
    char data[0];
};

typedef struct dlist_node dlist_node_t;

/*! The main dlist struct. 
 *
 *  This is what gets passed around to library
 *  functions and kept by the user. It stores some
 *  vital data like a pointer to the first node
 *  `head` and the `size` of the elements, 
 *  as well as some convenience data like the 
 *  `length` of the list of the last node `tail`
 *  so we don't have to compute them all the time.
 */
struct dlist
{
    //! the first node in the list
    struct dlist_node *head;

    //! the last node in the list
    struct dlist_node *tail;

    //! the length (amount of elements)
    //! of the list
    size_t length;

    //! the size of the elements of the
    //! list
    size_t size;
};

typedef struct dlist dlist_t;

/*! Returns the size of the elements that the list
 *  holds in bytes.
 *
 *  @param list the list in question
 *  @return the size of the elements in the list
 *  @todo implement this as macro for speed
 *
 *  ### Error Handling
 *
 *  If passed NULL, it will return 0.
 *
 *  ### Example
 *
 *  ```c
 *  // create new list with size = sizeof(int)
 *  dlist_t *list = dlist_new(sizeof(int));
 *  assert(list != NULL);
 *
 *  // add some elements
 *  assert(dlist_append(list, NULL) != NULL);
 *  assert(dlist_append(list, NULL) != NULL);
 *
 *  // there are now two elements in the list
 *  assert(dlist_length(list) == 2);
 *
 *  // and each of them are sizeof(int) big
 *  assert(dlist_size(list) == sizeof(int));
 *  ```
 */
size_t dlist_size(const dlist_t *list);

/*! Returns the length of the list (how many elements
 *  are in it).
 *
 *  @param list the list in question
 *  @return how many elements the list holds
 *  @todo implement this as macro for speed
 *
 *  ### Error Handling
 *
 *  If passed NULL, returns 0.
 *
 *  ### Example
 *
 *  ```c
 d  dlist_t *list = dlist_new(sizeof(int));
 *  assert(list != NULL);
 *
 *  // list is empty
 *  assert(dlist_length(list) == 0);
 *
 *  // fill 'er up
 *  assert(dlist_append(list, NULL) != NULL);
 *  assert(dlist_append(list, NULL) != NULL);
 *  assert(dlist_append(list, NULL) != NULL);
 *
 *  // it isn't empty no more
 *  assert(dlist_length(list) == 3);
 *  ```
 */
size_t dlist_length(const dlist_t *list);

/*! Returns a pointer to the first element in
 *  the list.
 *
 *  @param list the list in question
 *  @return a pointer to the first element in the
 *      list
 *  @todo implement this as macro for speed
 *
 *  ### Error Handling
 *
 *  If `list` is NULL or it is empty, returns
 *  NULL.
 *
 *  ### Example
 *
 *  ```c
 *  dlist_t *list = dlist_new(sizeof(int));
 *  assert(list != NULL);
 *
 *  // passing NULL
 *  assert(dlist_first(NULL) == NULL);
 *
 *  // passing empty list
 *  assert(dlist_first(list) == NULL);
 *
 *  assert(dlist_append(list, NULL) != NULL);
 *  assert(dlist_first(list) != NULL);
 *  ```
 */
void *dlist_first(const dlist_t *list);

/*! Returns a pointer to the last element in
 *  the list.
 *
 *  @param list the list in question
 *  @return a pointer to the first element in the
 *      list
 *  @todo implement this as macro for speed
 *
 *  ### Error Handling
 *
 *  If `list` is NULL or it is empty, returns
 *  NULL.
 *
 *  ### Example
 *
 *  ```c
 *  dlist_t *list = dlist_new(sizeof(int));
 *  assert(list != NULL);
 *
 *  // passing NULL
 *  assert(dlist_last(NULL) == NULL);
 *
 *  // passing empty list
 *  assert(dlist_last(list) == NULL);
 *
 *  assert(dlist_append(list, NULL) != NULL);
 *  assert(dlist_last(list) != NULL);
 *  ```
 */
void *dlist_last(const dlist_t *list);

/* CREATION / DESTRUCTION */

/* CREATION/DESTRUCTION FUNCTIONS */

/*! Creates a new dlist_t object on the heap with 
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
 *  dlist_t *list = dlist_new(sizeof(int));
 *
 *  if(list == NULL) {
 *      // error!
 *  }
 *  ```
 */
dlist_t *dlist_new(size_t size);

/*! Initializes a given dlist object for use with
 *  objects of the given size.
 *
 *  @warning Assumes that the list is either 
 *      uninitialized or empty. If not, it will 
 *      leak memory!
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
 *  dlist_t list;
 *  
 *  if(NULL == dlist_init(&list, sizeof(int))) {
 *      // error!
 *  }
 *  ```
 *
 */
dlist_t *dlist_init(dlist_t *list, size_t size);

/*! Takes an existing (already initialized) list,
 *  removes all its elements and frees it.
 *
 *  @warning Make sure that the list has been initialized,
 *      otherwise this function will cause undefined
 *      behavior!
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
 *  dlist_t list;
 *  dlist_init(&list, sizeof(int));
 *  
 *  int i = 5;
 *  dlist_append(list, &i);
 *
 *  if(NULL == dlist_purge(list)) {
 *      // error!
 *  }
 *  ```
 */
dlist_t *dlist_purge(dlist_t *list);

/*! Takes an existing list that has been allocated 
 *  on the heap (for example withwith dlist_new()),
 *  free()s all of the data and then the list itself.
 *
 *  @warning Make sure to call this on lists
 *      that have been allocated on the heap (not on the
 *      stack) as this function will call `free()` on
 *      them!
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
 *  dlist_t *list = dlist_new(sizeof(int));
 *  
 *  int i = 5;
 *  dlist_append(list, &5);
 *
 *  if(0 != dlist_free(list)) {
 *      // error!
 *  }
 *  ```
 */
int     dlist_free (dlist_t *list);

/*! Appends some data to the end of a list.
 *
 *  @warning This function returns a pointer to the
 *      newly created element. Please note that
 *      this pointer is only valid until the next
 *      mutating library call.
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
 *  dlist_t *list = dlist_new(sizeof(int));
 *
 *  // append using data pointer
 *  int d = 5;
 *  if(NULL == dlist_append(list, &d)) {
 *      // error!
 *  }
 *
 *  // append manually
 *  void *ptr = dlist_append(list, NULL);
 *  if(ptr != NULL) {
 *      int *p = ptr;
 *      *p = 5;
 *  } else {
 *      // error!
 *  }
 *  ```
 */
void *dlist_append (dlist_t *list, void *data);

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
 *  dlist_t *list = dlist_new(sizeof(int));
 *
 *  // prepend using data pointer
 *  int d = 5;
 *  if(NULL == dlist_prepend(list, &d)) {
 *      // error!
 *  }
 *
 *  // prepend manually
 *  void *ptr = dlist_prepend(list, NULL);
 *  if(ptr != NULL) {
 *      int *p = ptr;
 *      *p = 5;
 *  } else {
 *      // error!
 *  }
 *  ```
 */
void *dlist_prepend(dlist_t *list, void *data);

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
 *  dlist_t *list = dlist_new(sizeof(int));
 *
 *  // insert at beginning
 *  int d = 5;
 *  if(NULL == dlist_insert(list, 0, &d)) {
 *      // error!
 *  }
 *
 *  // insert at end
 *  if(NULL == dlist_insert(list, 1, &d)) {
 *      // error!
 *  }
 *
 *  // insert manually in middle
 *  void *ptr = dlist_insert(list, 1, NULL);
 *  if(ptr != NULL) {
 *      int *p = ptr;
 *      *p = 5;
 *  } else {
 *      // error!
 *  }
 *  ```
 */
void *dlist_insert (dlist_t *list, size_t pos, void *data);

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
 *  dlist_t *list = dlist_new(sizeof(int));
 *
 *  int i = 5;
 *  dlist_append(list, &i);
 *  dlist_append(list, &i);
 *  dlist_append(list, &i);
 *
 *  // element does not exist
 *  assert(dlist_remove(list, 6) < 0);
 *
 *  assert(dlist_remove(list, 2) == 0);
 *  assert(dlist_remove(list, 0) == 0);
 *  ```
 */
int   dlist_remove (dlist_t *list, size_t pos);

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
 *  dlist_t *list = dlist_new(sizeof(int));
 *
 *  // fill up the list
 *  int i = 5;
 *  dlist_append(list, &i);
 *  dlist_append(list, &i);
 *  dlist_append(list, &i);
 *
 *  // set second element to 6
 *  i = 6;
 *  assert(dlist_set(list, 1, &i) != NULL);
 *  ```
 */
void *dlist_set(dlist_t *list, size_t pos, void *data);

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
 *  @todo incorporate data pointer
 *
 *  ### Example
 *
 *  ```c
 *  dlist_t *list = dlist_new(sizeof(int));
 *
 *  // add an element
 *  int five = 5;
 *  assert(dlist_append(list, &five) != NULL);
 *
 *  // get the element
 *  int *elem = dlist_get(list, 0);
 *  assert(elem != NULL);
 *  assert(*elem == five);
 *
 *  // accessing nonexisting element produces NULL
 *  assert(dlist_get(list, 1) == NULL);
 *  ```
 */
void *dlist_get(dlist_t *list, size_t pos, void *data);

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
 *  dlist_t *list = dlist_new(sizeof(int));
 *  assert(list != NULL);
 *
 *  // fill up list a bit
 *  int five = 5;
 *  assert(dlist_append(list, &five) != NULL);
 *  assert(dlist_append(list, &five) != NULL);
 *  assert(dlist_length(list) == 2);
 *
 *  // pop the first element
 *  assert(dlist_pop(list, NULL);
 *  assert(dlist_length(list) == 2);
 *
 *  // pop the second element, saving the data
 *  int data;
 *  assert(dlist_pop(list, &data) != NULL);
 *  assert(dlist_length(list) == 0);
 *  assert(data == five);
 *  ```
 */
void *dlist_pop(dlist_t *list, void *data);

/*! Swaps two elements in the list by position.
 *
 *  Given two valid positions in the list, this
 *  function swaps the two elements.
 *
 *  @param list the list to operate on
 *  @param a the index of the first element
 *  @param b the index of the second element
 *  @return 
 *    - 0 on success
 *    - negative on error
 *
 *  ### Example
 *
 *  ```c
 *  dlist_t *list = dlist_new(sizeof(int));
 *  assert(list != NULL);
 *
 *  int num = 5;
 *  assert(dlist_append(list, &num) != NULL);
 *  num = 10;
 *  assert(dlist_append(list, &num) != NULL);
 *
 *  // this does nothing
 *  assert(dlist_swap(list, 0, 0) == 0);
 *  assert(dlist_get(list, 0, &num) != NULL);
 *  assert(num == 5);
 *
 *  // swap elements
 *  assert(dlist_swap(list, 0, 1) == 0);
 *  assert(dlist_get(list, 0, &num) != NULL);
 *  assert(num == 10);
 *  assert(dlist_get(list, 1, &num) != NULL);
 *  assert(num == 5);
 *
 *  // this doesn't work
 *  assert(dlist_swap(list, 1, 2) < 0);
 */
int dlist_swap(dlist_t *list, size_t a, size_t b);

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
 *  dlist_t *list = dlist_new(sizeof(int));
 *  assert(list != NULL);
 *
 *  int two = 2;
 *  assert(dlist_append(list, &two) != NULL);
 *  assert(dlist_append(list, &two) != NULL);
 *  assert(dlist_append(list, &two) != NULL);
 *  assert(dlist_append(list, &two) != NULL);
 *  assert(dlist_length(list) == 4);
 *
 *  dlist_t *half = dlist_split(list, 2);
 *  assert(dlist_length(list) == 2);
 *  assert(dlist_length(half) == 2);
 *  ```
 */
dlist_t *dlist_split(dlist_t *list, size_t pos);

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
 *  dlist_t *one = dlist_new(sizeof(int));
 *  assert(one != NULL);
 *  dlist_t *two = dlist_new(sizeof(int));
 *  assert(two != NULL);
 *
 *  int number = 2;
 *  
 *  assert(dlist_append(one, &number) != NULL);
 *  assert(dlist_append(one, &number) != NULL);
 *  assert(dlist_length(one) == 2);
 *
 *  assert(dlist_append(two, &number) != NULL);
 *  assert(dlist_append(two, &number) != NULL);
 *  assert(dlist_length(two) == 2);
 *  
 *  assert(dlist_join(one, two) != NULL);
 *  assert(dlist_length(one) == 4);
 *  assert(dlist_length(two) == 0);
 *  ```
 */
dlist_t *dlist_join(dlist_t *dest, dlist_t *src);

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
 *  dlist_t *list = dlist_new(sizeof(int));
 *  assert(list != NULL);
 *
 *  int number = 8;
 *  assert(dlist_append(list, &number) != NULL);
 *  assert(dlist_append(list, &number) != NULL);
 *  assert(dlist_append(list, &number) != NULL);
 *  assert(dlist_length(list) == 3);
 *
 *  dlist_t *copy = dlist_copy(list);
 *  assert(dlist_length(copy) == 3);
 *  ```
 */
dlist_t *dlist_copy(const dlist_t *list);

/*! Reverses a dlist.
 *
 *  @param list the list to reverse
 *  @return 0 on success
 *  @todo document this more
 */
int      dlist_reverse(dlist_t *list);

#ifdef __cplusplus
}
#endif
#endif
