/*  File: sl_list.c
 *  Source for sl_list, a C implementation of a single linked list.
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

#include "sl_list.h"

sl_node *list_get_node(sl_list *list, size_t pos)
{
    if((pos-1) == list->size)
        return list->tail;

    sl_node *node = list->head;

    while(node && pos)
    {
        pos--;
        node = node->next;
    }

    return node;
}

sl_list *sl_list_new()
{
    sl_list *list = (sl_list*)malloc(sizeof(sl_list));
    memset(list, 0, sizeof(list));
}

void *list_get(sl_list *list, size_t pos)
{
    sl_node *node = list_get_node(list, pos);

    if(node)
        return node->data;
    else
        return 0;
}

void *list_last(sl_list *list)
{
    if(list->tail)
        return list->tail->data;
    else
        return 0;
}

void *list_first(sl_list *list)
{
    if(list->head)
        return list->head->data;
    else
        return 0;
}

void *list_pop(sl_list *list)
{
    sl_node *node = list->head;

    if(!node)
        return 0;

    if(node->next)
    {
        list->head = node->next;
    } else {
        list->head = 0;
        list->tail = 0;
    }

    list->size--;

    void *data = node->data;

    free(node);

    return data;
}

void list_set(sl_list *list, size_t pos, void *data)
{
    sl_node *node = list_get_node(list, pos);

    if(node)
        node->data = data;
}

void list_append(sl_list *list, void *data)
{
    sl_node *node = (sl_node*)malloc(sizeof(sl_node));

    memset(node, 0, sizeof(node));

    node->data = data;

    if(list->tail)
    {
        list->tail->next = node;
        list->tail = node;
        list->size++;
    } else {
        list->head = node;
        list->tail = node;
        list->size++;
    }
}

void list_debug(sl_list *list)
{
    printf("list %p head %p tail %p\n", list, list->head, list->tail);
    sl_node *node = list->head;

    while(node)
    {
        printf("node %p data %p next %p\n", node, node->data, node->next);
        node = node->next;
    }
}

void list_reset(sl_list *list, int free_data)
{
    sl_node *node = list->head;
    sl_node *old = 0;

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

size_t list_size(sl_list *list)
{
    // get the list's first node
    sl_node *node = list->head;
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
