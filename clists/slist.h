/*! @file slist.h
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
 *
 *  ### Design Specifications
 *  - implementation of single linked lists in C
 *  - simple
 *  - efficient
 *  - intuitive
 *  - flexible
 *
 *  @todo test the code extensively
 */

#pragma once

#include <stdlib.h>
#include <string.h>

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
 *  ### Invariants
 *
 *  If `next` is NULL, this is the last node of the list.
 *  If `next` is non-NULL, this is not the last node of
 *  the list, and the value of `next` is a pointer to
 *  the next node in the list. All nodes in the list 
 *  are of the same size (so all elements hold the same
 *  amount of data, as measured by the length of `data`.
 *
 *  Since the list is not circular, `next` may never
 *  point to an element that has already been in the
 *  list earlier or to this node.
 *
 *  @todo zero length array is kinda iffy. can we do this better?
 */
struct slist_node
{
    //! pointer to next node in list
    struct slist_node *next;

    //! variable length data
    char data[0];
};

typedef struct slist_node slist_node_t;

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
 *  ### Invariants
 *
 *  If the list is not empty, `head` points to the first node
 *  in the list, otherwise it is NULL.
 *
 *  Similarly, `tail` points to the last node in the list if
 *  it is not empty, and otherwise NULL.
 *
 *  `head` and `tail` may only point to the same node if the 
 *  list has a `length` of 1.
 *
 *  `length` is always the length of the list, as measured by
 *  how many nodes are between `head` and `tail` (including
 *  `head` and `tail` themselves).
 *
 *  `size` is the size of each elements, which stays the same
 *  during the whole lifetime of the list.
 *
 *  The list may not be  circular.
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

typedef struct slist slist_t;

/*! Function to compare two elements. 
 *
 *  Used by slist_compare() to compare two lists
 *  by their elements.
 *  
 *  @param a the first element
 *  @param b the second element
 *  @return
 *      - 0 if they are equal
 *      - -1 if a > b
 *      - 1 if a < b
 */
typedef int slist_compare_elements(void *a, void *b);

/* BASIC DATA ACCESS */

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
 *  slist_t *list = slist_new(sizeof(int));
 *  assert(list != NULL);
 *
 *  // add some elements
 *  assert(slist_append(list, NULL) != NULL);
 *  assert(slist_append(list, NULL) != NULL);
 *
 *  // there are now two elements in the list
 *  assert(slist_length(list) == 2);
 *
 *  // and each of them are sizeof(int) big
 *  assert(slist_size(list) == sizeof(int));
 *  ```
 */
size_t slist_size(const slist_t *list);

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
 *  slist_t *list = slist_new(sizeof(int));
 *  assert(list != NULL);
 *
 *  // list is empty
 *  assert(slist_length(list) == 0);
 *
 *  // fill 'er up
 *  assert(slist_append(list, NULL) != NULL);
 *  assert(slist_append(list, NULL) != NULL);
 *  assert(slist_append(list, NULL) != NULL);
 *
 *  // it isn't empty no more
 *  assert(slist_length(list) == 3);
 *  ```
 */
size_t slist_length(const slist_t *list);

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
 *  slist_t *list = slist_new(sizeof(int));
 *  assert(list != NULL);
 *
 *  // passing NULL
 *  assert(slist_first(NULL) == NULL);
 *
 *  // passing empty list
 *  assert(slist_first(list) == NULL);
 *
 *  assert(slist_append(list, NULL) != NULL);
 *  assert(slist_first(list) != NULL);
 *  ```
 */
void *slist_first(const slist_t *list);

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
 *  slist_t *list = slist_new(sizeof(int));
 *  assert(list != NULL);
 *
 *  // passing NULL
 *  assert(slist_last(NULL) == NULL);
 *
 *  // passing empty list
 *  assert(slist_last(list) == NULL);
 *
 *  assert(slist_append(list, NULL) != NULL);
 *  assert(slist_last(list) != NULL);
 *  ```
 */
void *slist_last(const slist_t *list);

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
void *slist_append (slist_t *list, const void *data);

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
void *slist_prepend(slist_t *list, const void *data);

/*! Inserts an element at the given position.
 *  
 *  The function inserts a new element at `pos`. If
 *  a non-NULL pointer `data` is passed, then
 *  whatever it is pointing at is copied into the
 *  element, otherwise the element is not initialized
 *  and it should be assumed to contain random garbage.
 *
 *
 *  Used by slist_compare() to compare two lists
 *  by their elements.
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
void *slist_insert (slist_t *list, size_t pos, const void *data);

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
 *  Copies the contents of the pointer `data` into
 *  the given element, and returns a pointer to the
 *  element in the list on success. If `data` is
 *  NULL, returns NULL.
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
void *slist_set(slist_t *list, size_t pos, const void *data);

/*! Gets a pointer to the data at pos.
 *
 *  This function will return a pointer to the element
 *  at `pos`, or `NULL` on error.
 *
 *  @warning if data is not NULL, it must point to 
 *  memory that is at least as large as the size of
 *  the elements in the list!
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
void *slist_get(const slist_t *list, size_t pos, void *data);

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
 *  slist_t *list = slist_new(sizeof(int));
 *  assert(list != NULL);
 *
 *  int num = 5;
 *  assert(slist_append(list, &num) != NULL);
 *  num = 10;
 *  assert(slist_append(list, &num) != NULL);
 *
 *  // this does nothing
 *  assert(slist_swap(list, 0, 0) == 0);
 *  assert(slist_get(list, 0, &num) != NULL);
 *  assert(num == 5);
 *
 *  // swap elements
 *  assert(slist_swap(list, 0, 1) == 0);
 *  assert(slist_get(list, 0, &num) != NULL);
 *  assert(num == 10);
 *  assert(slist_get(list, 1, &num) != NULL);
 *  assert(num == 5);
 *
 *  // this doesn't work
 *  assert(slist_swap(list, 1, 2) < 0);
 *  ```
 */
int slist_swap(slist_t *list, size_t a, size_t b);

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
 *  @warning The element sizes of both lists
 *  must be identical!
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

/*! Compares two lists, optionally using a 
 *  supplied comparison function.
 *
 *  If no comparison function is given, the
 *  elements are compared byte-by-byte using
 *  memcmp(). 
 *
 *  @param a the first list to compare
 *  @param b the second list to compare
 *  @param func the comparison function to use,
 *      or NULL
 *
 *  ### Example
 *
 *  ```c
 *  slist_t *list_a = slist_new(sizeof(int));
 *  slist_t *list_b = slist_new(sizeof(int));
 *
 *  assert(0 == slist_compare(list_a, list_b, NULL));
 *  ```
 */
int slist_compare(slist_t *a, slist_t *b, slist_compare_elements *cmp);

/*! Verifies that a list is correct.
 *
 *  This method verifies that a list is correct and
 *  does not have any cycles.
 *
 *  It exists only for internal testing purposes.
 */
int slist_verify(const slist_t *list);

#ifdef __cplusplus
}
#endif
