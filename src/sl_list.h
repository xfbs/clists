/*  File: sl_list.h
 *  Header for llist, a C implementation of a single linked list
 *  
 *  Copyright (C) 2011, Patrick M. Elsen
 *
 *  This file is part of CMatrixCrypt (http://github.com/xfbs/CMatrixCrypt)
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

#ifndef SL_LIST_H
#define SL_LIST_H

#define bool short
#define true 1
#define false 0

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/* SL_LIST DATA STRUCTURES
 * Data structures used by the single linked list
 * implementation. 
 */

// single lined list node
struct sl_list_node
{
    // data pointer
    void *data;
    // next list node
    struct sl_list_node *next;
};

// single linked list 'object'
struct sl_list
{
    // pointer to first list element
    struct sl_list_node *head;
};

typedef struct sl_list sl_list;
typedef struct sl_list_node sl_list_node;


/* SL_LIST FUNCTIONS
 * These are functions used to manipulate sl_lists
 */

// create a sl_list 'object'
sl_list *sl_list_new();

// get the node of the list at pos
sl_list_node *list_get_node(sl_list *list, size_t pos);

// reset list nodes
void list_reset(sl_list *list, bool free_data);

// free list and all nodes (but no data pointers)
void list_delete(sl_list *list, bool free_data);

// append data to the end of the list
void list_append(sl_list *list, void *data);

// print diagnostics
void list_debug(sl_list *list);

// set an element to data
void list_set(sl_list *list, size_t pos, void *data);

// get the list's size
size_t list_size(sl_list *list);

// get the data stored at pos (or NULL)
void *list_get(sl_list *list, size_t pos);

// get the list's last element
void *list_last(sl_list *list);

// get the first element (or NULL)
void *list_first(sl_list *list);

// delete last list node and return data
void *list_pop(sl_list *list);

#endif
