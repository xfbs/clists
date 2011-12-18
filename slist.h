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
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debug.h"


/* slist_node struct
 * a single linked list node: contains a pointer
 * to the next list element as well as a pointer
 * to the data of that list element.
 */
struct slist_node
{
    struct slist_node *next;
    void *data;
};


/* slist_node struct
 * data type of a singly linked list: contains 
 * pointer to the head of the list for pushing 
 * items to the list, to the end of the list for
 * efficient appending and a variable to keep 
 * track of the size of the list to avoid having
 * to traverse all elements to get the size.
 */
struct slist
{
    struct slist_node *head;
    struct slist_node *tail;
    struct slist_node *pos;
    size_t size;
};


/* slist_iter struct
 * data type of an iterator for the singly linked
 * list. contains pointers to a list as well as 
 * to the current position in that list and one
 * var to denote the current position.
 */
struct slist_iter
{
    struct slist *list;
    struct slist_node *cur;
    size_t pos;
};

typedef struct slist_node slist_node;
typedef struct slist_iter slist_iter;
typedef struct slist slist;


/* slist_alloc()
 * allocates a new singly linked list with malloc
 * and zeroizes the allocated memory (!)
 */
slist *slist_alloc();


/* slist_free(list, free_data)
 * frees a list, it's nodes and optionally the 
 * node's data
 */
void slist_free(slist* list, bool free_data);


/* slist_node_alloc()
 * allocates and zeroizes a slist_node
 */
slist_node *slist_node_alloc();


/* slist_get_node(list, pos)
 * returns pointer to node at position pos of the
 * list. if there is no node at pos, returns NULL
 */
slist_node *slist_get_node(slist *list, size_t pos);


/* slist_node_copy(node)
 * allocates a new node that is identical to the
 * one passed as argument
 */
slist_node *slist_node_copy(slist_node *old);


/* slist_copy(other)
 * allocates a new singly linked list and copies 
 * all elements from other into it.
 */
slist *slist_copy(slist *old);


/* slist_purge(list, free_data)
 * removes all nodes from list, making it
 * empty, optionally frees all data
 */
void slist_purge(slist *list, bool free_data);


/* slist_merge(dest, source)
 * destructively adds all nodes of other to list.
 * this will make other an empty list. use 
 * slist_copy to prevent other from being emptied
 */
void slist_merge(slist *dest, slist *source);


/* slist_append(list, data)
 * add data to the back of the linked list
 */
void slist_append(slist *list, void *data);


/* slist_push(list, data)
 * add data to the head of the linked list
 */
void slist_push(slist *list, void *data);


/* slist_insert(list, data, pos)
 * adds data to the list at the specified
 * position of the list or at the end if 
 * pos is out of range
 */
void slist_insert(slist *list, void *data, size_t pos);


/* slist_set(list, data, pos)
 * sets the data of the node at pos to data,
 * or don't do anything if pos doesn't exist
 */
void slist_set(slist *list, void *data, size_t pos);


/* slist_first(list)
 * returns data of first node or NULL if it
 * does not exist
 */
void *slist_first(slist *list);


/* slist_last(list)
 * returns data of last ndoe in list or NULL
 * if it does not exist
 */
void *slist_last(slist *list);


/* slist_get(list, pos)
 * returns data of node at pos in list
 */
void *slist_get(slist *list, size_t pos);


/* slist_pop(list)
 * removes and returns the topmose node of
 * the list
 */
void *slist_pop(slist *list);


/* slist_remove(list, pos, free_data)
 * removes node at pos from list, freeing
 * the data if asked so, and returning the
 * pointer
 */
void *slist_remove(slist *list, size_t pos, bool free_data);


/* slist_size(list)
 * returns the size of the list
 */
size_t slist_size(slist *list);


/* slist_iter_alloc(list)
 * returns an iterator for the list
 */
slist_iter *slist_iter_alloc(slist *list);


/* slist_iter_free(iter)
 * frees an iterator
 */
void slist_iter_free(slist_iter *iter);


/* slist_iter_goto(iter, pos)
 * go to position pos in the iterator iter
 */
void slist_iter_goto(slist_iter *iter, size_t pos);


/* slist_iter_next(iter)
 * goes to the next node of the list and
 * returns a pointer to the node or NULL
 * if at end of list
 */
void *slist_iter_next(slist_iter *iter);


/* slist_iter_get(iter)
 * get the current node
 */
void *slist_iter_get(slist_iter *iter);

#endif
