/*  File: sl_list.c
 *  Source for llist, a C implementation of a single linked list
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

#include "sl_list.h"

void list_reset(sl_list *list, bool free_data)
{
    sl_list_node *node = list->head;
    sl_list_node *old = 0;

    while(node)
    {
        if(free_data)
            free(node->data);
        old = node;
        node = node->next;
        free(old);
    }

    list->head = 0;
}

void list_delete(sl_list *list, bool free_data)
{
    list_reset(list, free_data);
    free(list);
}

sl_list *sl_list_new()
{
    // allocate space for a sl_list
    sl_list *list = (sl_list*)malloc(sizeof(sl_list));
    // use memset to zero it out
    memset(list, 0, sizeof(sl_list));

    return list;
}

sl_list_node *list_get_node(sl_list *list, size_t pos)
{
    sl_list_node *node = list->head;

    // loop until we are at the node at pos
    while(node && pos)
    {
        pos--;
        node = node->next;
    }

    return node;
}

void list_debug(sl_list *list)
{
    printf("list %p head %p\n", list, list->head);
    sl_list_node *node = list->head;

    while(node)
    {
        printf("node %p data %p next %p\n", node, node->data, node->next);
        node = node->next;
    }
}

size_t list_size(sl_list *list)
{
    // get the list's first node
    sl_list_node *node = list->head;
    // counter variable
    size_t size = 0;

    // loop thru all nodes
    while(node)
    {
        size++;
        node = node->next;
    }

    return size;
}

void list_set(sl_list *list, size_t pos, void *data)
{
    // get the node that we want to update
    sl_list_node *node = list_get_node(list, pos);

    if(node)
        node->data = data;
}

void *list_get(sl_list *list, size_t pos)
{
    // get the node at pos
    sl_list_node *node = list_get_node(list, pos);
    // return data or zero
    if(node)
        return node->data;
    else
        return 0;
}

void *list_last(sl_list *list)
{
    // get list's first ndoe
    sl_list_node *node = list->head;
    // make sure this node exists (not NULL)
    if(!node)
        return 0;
    
    // loop thru to the last node
    while(node->next)
    {
        node = node->next;
    }

    // return last node's data
    return node->data;
}

void *list_first(sl_list *list)
{
    // if the first node exists, return it's data, else NULL
    if(list->head)
        return list->head->data;
    else
        return 0;
}

void list_append(sl_list *list, void *data)
{
    // allocate new node
    sl_list_node *new = (sl_list_node*)malloc(sizeof(sl_list_node));
    // zeroize it
    memset(new, 0, sizeof(sl_list_node));
    // fill data
    new->data = data;

    // check if list is empty
    if(!list->head)
    {
        // if it is, make this the first element
        list->head = new;
        return;
    }

    // get the first node
    sl_list_node *node = list->head;

    // loop until the last node
    while(node->next)
    {
        node = node->next;
    }

    // once we got the last node, append the new node
    node->next = new;
}

void *list_pop(sl_list *list)
{
    // get the first ndoe of the list
    sl_list_node *node = list->head;
    // space to store the node's data
    void *data;

    // make sure the list isn't empty
    if(!node)
        return 0;

    // if the list only had one node, that needs to be handles differently
    if(!node->next)
    {
        // save the node's data
        data = node->data;
        // make the list forget about the node
        list->head = 0;
        // free the node
        free(node);
        // return the data
        return data;
    }
    
    // go to the node before the last node
    while(node->next->next)
    {
        node = node->next;
    }

    // save the data
    data = node->next->data;
    // free the node
    free(node->next);
    // unregiester it
    node->next = 0;
    // return the data
    return data;
}




