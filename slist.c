/*  File: slist.c
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

#include "clists/slist.h"
static slist_node_t *slist_node_get(slist_t *list, size_t pos);

slist_t *slist_new(void)
{
    slist_t *list = malloc(sizeof(slist_t));
    if(list == NULL)
        return NULL;

    memset(list, 0, sizeof(slist_t));
    return list;
}

int slist_init(slist_t *list)
{
    if(list == NULL)
        return -1;

    memset(list, 0, sizeof(slist_t));
    return 0;
}

int slist_purge(slist_t *list)
{
    slist_node_t *cur = list->head;
    slist_node_t *next;

    while (cur != NULL) {
        /* store ptr to next node */
        next = cur->next;

        /* free current node */
        free(cur);

        /* advance to next node */
        cur = next;
    }

    memset(list, 0, sizeof(slist_t));
    return 0;
}

int slist_free(slist_t *list)
{
    if(list == NULL)
        return -1;

    /* free nodes */
    int ret = slist_purge(list);
    free(list);

    return ret;
}

int slist_append(slist_t *list, void *data)
{
    slist_node_t *node = list->tail;

    if (node != NULL) {
        /* append to existing node */
        node->next = malloc(sizeof(slist_node_t));
        node = node->next;
    } else {
        /* make it the first node */
        node = malloc(sizeof(slist_node_t));
        list->head = node;
    }

    if(node == NULL)
        return -1;

    memset(node, 0, sizeof(slist_node_t));
    list->tail = node;
    list->size++;
    node->data = data;

    return 0;
}

int slist_prepend(slist_t *list, void *data)
{
    slist_node_t *node = malloc(sizeof(slist_node_t));
    if(node == NULL)
        return -1;

    memset(node, 0, sizeof(slist_node_t));

    node->data = data;

    if (list->head != NULL) {
        node->next = list->head;
    } else {
        list->tail = node;
    }

    list->head = node;
    list->size++;

    return 0;
}

int slist_insert(slist_t *list, size_t pos, void *data)
{
    if (pos == 0) {
        slist_prepend(list, data);
    } else if (pos == list->size) {
        slist_append(list, data);
    } else if (pos > list->size) {
        return -1;
    } else {
        slist_node_t *prev = slist_node_get(list, pos-1);
        slist_node_t *next = prev->next;
        
        slist_node_t *node = malloc(sizeof(slist_node_t));
        if(node == NULL)
            return -1;

        memset(node, 0, sizeof(slist_node_t));

        /* connect nodes */
        prev->next = node;
        node->next = next;

        node->data = data;
        list->size++;
    }

    return 0;
}

int slist_remove(slist_t *list, size_t pos)
{
    if(list->size == 0) {
        return -1;
    } else if(pos == 0) {
        slist_pop(list);
    } else if(pos >= list->size) {
        return -1;
    } else {
        slist_node_t *prev = slist_node_get(list, pos-1);

        if ((prev == NULL) || (prev->next == NULL)) {
            return -1;
        }

        slist_node_t *node = prev->next;

        /* connect the previous and the next node */
        if (node == list->tail) {
            list->tail = prev;
            prev->next = NULL;
        } else {
            prev->next = node->next;
        }
        
        free(node);
        list->size--;
    }

    return 0;
}

int slist_set(slist_t *list, size_t pos, void *data)
{
    slist_node_t *node = slist_node_get(list, pos);

    if (node != NULL) {
        node->data = data;
        return 0;
    } else {
        return -1;
    }
}

void *slist_get(slist_t *list, size_t pos)
{
    slist_node_t *node = slist_node_get(list, pos);
    return((node) ? node->data : NULL);
}

void *slist_pop(slist_t *list)
{
    slist_node_t *head = list->head;

    if (head == NULL)
        return NULL;

    void *data = head->data;

    if (head->next) {
        list->head = head->next;
    } else {
        list->head = NULL;
        list->tail = NULL;
    }

    list->size--;
    free(head);

    return data;
}

#ifndef slist_size
size_t slist_size(slist_t *list)
{
    return list->size;
}
#endif

#ifndef slist_first
void *slist_first(slist_t *list)
{
    slist_node_t *node = list->head;
    return((node) ? node->data : NULL);
}
#endif

#ifndef slist_last
void *slist_last(slist_t *list)
{
    slist_node_t *node = list->tail;
    return((node) ? node->data : NULL);
}
#endif

int slist_equal(slist_t *lista, slist_t *listb)
{
    if((lista != listb) && ((lista == NULL) || (listb == NULL)))
        return 0;

    // check if they have the same size
    if (slist_size(lista) != slist_size(listb))
        return 0;
    
    // the nodes to loop through
    slist_node_t *lista_node = lista->head;
    slist_node_t *listb_node = listb->head;

    // loop through them
    while (lista_node && listb_node) {
        // return false if their data isn't the same
        if (lista_node->data != listb_node->data)
            return 0;

        // iterate to the next nodes
        lista_node = lista_node->next;
        listb_node = listb_node->next;
    }

    return 1;
}

/*
slist *slist_copy(slist *list)
{
    // allocate a new slist
    slist *copy = slist_alloc();

    // head node or list
    slist_node *list_node = list->head;

    // copy head node of list
    slist_node *copy_node = slist_node_copy(list_node);

    // set head node
    copy->head = copy_node;

    // loop through nodes
    while (list_node && list_node->next) {
        // copy nodes
        copy_node->next = slist_node_copy(list_node->next);

        // go to next nodes
        copy_node = copy_node->next;
        list_node = list_node->next;
    }

    // set copy's tail node
    copy->tail = copy_node;

    // set copy's size
    copy->size = list->size;

    return copy;
}
*/

static slist_node_t *slist_node_get(slist_t *list, size_t pos)
{
    if (list->size == 0)
        return NULL;

    if (pos == 0)
        return list->head;
    else if (pos == (list->size-1))
        return list->tail;
    else if (pos >= list->size)
        return NULL;

    slist_node_t *node = list->head;
    while ((node != NULL) && (pos != 0)) {
        pos--;
        node = node->next;
    }

    if(pos != 0)
        return NULL;

    return node;
}

