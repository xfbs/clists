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


/* dlist_node struct
 * represents a node of the doubly linked list,
 * has pointers to the previous and next nodes
 */
struct dlist_node
{
    struct dlist_node *prev;
    struct dlist_node *next;
    void *data;
};


/* dlist struct
 * data type of doubly linked list, contains
 * pointer to first node as well as cached 
 * variables for the size of the list and the
 * last node
 */
struct dlist
{
    struct dlist_node *head;
    struct dlist_node *tail;
    size_t size;
};


typedef struct dlist dlist;
typedef struct dlist_node dlist_node;


/* dlist_alloc()
 * convenience function to allocate a new
 * dlist 'object' with malloc and zeroizes
 * it. 
 */
dlist *dlist_alloc();


/* dlist_copy(list)
 * copies a list and all data pointers
 */
dlist *dlist_copy(dlist *list);


/* dlist_node_alloc()
 * convenience function to allocate new 
 * node with malloc and zeroize it
 */
dlist_node *dlist_node_alloc();


/* dlist_copy_node(node)
 * allocates new node, copies the content
 * of node into it and returns it
 */
dlist_node *dlist_node_copy(dlist_node *node);


/* dlist_node_get(list, pos)
 * get the node at position pos of the list or
 * return NULL if it doesn't exist
 */
dlist_node *dlist_node_get(dlist *list, size_t pos);


/* dlist_free(list, free_data)
 * frees list's nodes, the list itself and
 * optionally the data the ndoes point to
 */
void dlist_free(dlist *list, bool free_data);


/* dlist_purge(list, free_data)
 * remove all nodes from list and optionally
 * free their data
 */
void dlist_purge(dlist *list, bool free_data);


/* dlist_merge(destination, source)
 * moves all nodes of source into destination, 
 * leaving source as an empty list and destination
 * as a list with all of source's nodes
 */
void dlist_merge(dlist *dest, dlist *source);


/* dlist_append(list, data)
 * append data to the end of the list
 */
void dlist_append(dlist *list, void *data);


/* dlist_push(list, data)
 * add data as node to the top of the list
 */
void dlist_push(dlist *list, void *data);


/* dlist_insert(list, data, pos)
 * insert data at position pos of list
 */
void dlist_insert(dlist *list, void *data, size_t pos);


/* dlist_set(list, data, pos)
 * set the data of the list's node at pos to data
 */
void dlist_set(dlist *list, void *data, size_t pos);


/* dlist_first(list)
 * return the first node's data or NULL if 
 * list is empty
 */
void *dlist_first(dlist *list);


/* dlist_last(list)
 * return the last node's data or NULL if
 * list is empty
 */
void *dlist_last(dlist *lsit);


/* dlist_get(list, pos)
 * return the data of the node at pos
 */
void *dlist_get(dlist *list, size_t pos);


/* dlist_pop(list)
 * remove and return the topmost node's data
 */
void *dlist_pop(dlist *list);


/* dlist_remove(list, pos, free_data)
 * remove the node at pos, freeing it if asked to
 * and return it's data in case cleanup needs to 
 * be done
 */
void *dlist_remove(dlist *list, size_t pos, bool free_data);


/* dlist_size(list)
 * returns the current size of the list
 */
size_t dlist_size(dlist *list);


/* dlist_compare(lhs, rhs)
 * returns true if both lists have the same
 * size and their nodes have the same data
 */
bool dlist_compare(dlist *lhs, dlist *rhs);

#endif
