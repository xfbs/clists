/*  File: dlist.c
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

#include "clists/dlist.h"
static dlist_node_t *dlist_node_get(dlist_t *list, size_t pos);

dlist_t *dlist_new(void)
{
    /* allocate memory for new list */
    dlist_t *list = malloc(sizeof(dlist_t));

    /* check if memory allocation worked */
    if(list == NULL)
        return NULL;

    /* initialize the new list */
    memset(list, 0, sizeof(dlist_t));
    return list;
}

int dlist_init(dlist_t *list)
{
    /* make sure list actually exists */
    if(list == NULL)
        return -1;

    /* initialize list */
    memset(list, 0, sizeof(dlist_t));
    return 0;
}

/* free every node of the list and reset the
 * list */
int dlist_purge(dlist_t *list)
{
    /* start at frist node of the list */
    dlist_node_t *node = list->head;

    /* free every node that is encountered */
    while (node) {
        free(node);
        node = node->next;
    }

    /* initialize list */
    memset(list, 0, sizeof(dlist_t));
    return 0;
}

int dlist_free(dlist_t *list)
{
    /* error checking */
    if(list == NULL)
        return -1;

    /* free all nodes */
    int ret = dlist_purge(list);

    free(list);

    /* return whatever purge gave pack to propagate
     * eventual errors */
    return ret;
}

int dlist_append(dlist_t *list, void *data)
{
    /* allocate new node */
    dlist_node_t *node = malloc(sizeof(dlist_node_t));

    /* make sure the malloc call worked */
    if(node == NULL) {
        return -1;
    }

    /* initialize node */
    memset(node, 0, sizeof(dlist_node_t));

    /* set node data */
    node->data = data;

    /* two cases possible: either list is empty, 
     * and we have to set the node as the first,
     * last and only node, or the list has other
     * nodes and we can simplt append to the end
     */
    if(list->tail != NULL) {
        /* link the new node with the previous
         * last node of the list */
        node->prev = list->tail;
        list->tail->next = node;

        /* make out node the new last node */
        list->tail = node;
    } else {
        /* make this node the one and only */
        list->head = node;
        list->tail = node;
    }

    /* increase size to reflect added node */
    list->size++;
    return 0;
}

int dlist_prepend(dlist_t *list, void *data)
{
    /* allocate new node */
    dlist_node_t *node = malloc(sizeof(dlist_node_t));

    /* make sure allocation worked */
    if(node == NULL) {
        return -1;
    }

    /* initialize node */
    memset(node, 0, sizeof(dlist_node_t));

    /* set node data */
    node->data = data;

    /* just as in dlist_append, we have to check if
     * the list was empty and this will be the first,
     * last and only node or if we can simply prepend
     * to existing nodes */
    if(list->head != NULL) {
        /* connect node with previous head of list */
        node->next = list->head;
        list->head->prev = node;

        /* set this node as the new head */
        list->head = node;
    } else {
        /* make this node the one and only */
        list->head = node;
        list->tail = node;
    }

    /* increment size to reflect added node */
    list->size++;
    return 0;
}

int dlist_insert(dlist_t *list, size_t pos, void *data)
{
    if(pos == 0) {
        /* inserting at pos=0 is the same as prepending */
        return dlist_prepend(list, data);
    } else if(pos == list->size) {
        /* inserting to the end of the list is the same
         * as appending */
        return dlist_append(list, data);
    } else if(pos > list->size) {
        /* can't add data past the end of the list
         * (otherwise, there would be gaps in the data)
         */
        return -2;
    } else {
        /* the previous if statements guarantee, that if we
         * get here, the data is to be inserted in the middle
         * of the list and not as first or last element */

        /* allocate new node */
        dlist_node_t *new = malloc(sizeof(dlist_node_t));

        /* make sure allocation worked */
        if(new == NULL) {
            return -3;
        }

        /* initialize node */
        memset(new, 0, sizeof(dlist_node_t));

        /* set node data */
        new->data = data;

        /* extract the node before where we want to insert
         * ours */
        dlist_node_t *node = dlist_node_get(list, pos-1);

        /* make sure this node exists (guaranteed to exist,
         * but who knows anything for certain right?) */
        if(node != NULL) {
            /* so currently node and node->next are doubly
             * linked, and our goal is to be sneaky and
             * put our node in between */
            node->next->prev = new;
            new->next = node->next;
            new->prev = node;
            node->next = new;
        } else {
            /* technically it should be impossible to get 
             * here if you're using the library functions
             */
            free(new);
            return -4;
        }

        /* increase list size to reflect added node */
        list->size++;
    }

    return 0;
}

int dlist_set(dlist_t *list, size_t pos, void *data)
{
    /* get the node at pos */
    dlist_node_t *node = dlist_node_get(list, pos);

    /* make sure it exists (if not, error!) */
    if(node) {
        /* set the node data */
        node->data = data;
        return 0;
    } else {
        return -1;
    }
}

void *dlist_get(dlist_t *list, size_t pos)
{
    /* get node at pos */
    dlist_node_t *node = dlist_node_get(list, pos);

    /* return node->data if node exists, otherwise
     * NULL (since NULL can be a valid value, be sure
     * to check if pos is valid!)
     */
    return((node) ? node->data : NULL);
}

void *dlist_pop(dlist_t *list)
{
    void *data;
    dlist_node_t *node;

    switch(list->size) {
        case 0:
            return NULL;
            break;
        case 1:
            node = list->head;
            data = node->data;
            memset(list, 0, sizeof(dlist_t));
            break;
        default:
            node = list->head;

            if(node->next)
                node->next->prev = NULL;

            list->head = node->next;
            list->size--;
            data = node->data;
            break;
    }

    free(node);
    return data;
}

int dlist_remove(dlist_t *list, size_t pos)
{
    if(list->size == 0)
        return -1;

    if(pos >= list->size)
        return -1;

    if(pos == 0) {
        dlist_pop(list);
    } else {
        dlist_node_t *node = dlist_node_get(list, pos);

        if(node == NULL)
            return -1;

        if(node == list->tail)
            list->tail = node->prev;

        if(node->next != NULL)
            node->next->prev = node->prev;

        if(node->prev != NULL)
            node->prev->next = node->next;

        free(node);
        list->size--;
    }

    return 0;
}

#ifndef dlist_size
size_t dlist_size(dlist_t *list)
{
    return((list) ? list->size : 0);
}
#endif

#ifndef dlist_first
void *dlist_first(dlist_t *list)
{
    dlist_node_t *node = list->head;
    return((node) ? node->data : NULL);
}
#endif

#ifndef dlist_last
void *dlist_last(dlist_t *list)
{
    dlist_node_t *node = list->tail;
    return((node) ? node->data : NULL);
}
#endif

int dlist_equal(dlist_t *lista, dlist_t *listb)
{
    if(dlist_size(lista) != dlist_size(listb))
        return 0;

    dlist_node_t *lista_node = lista->head;
    dlist_node_t *listb_node = listb->head;

    while (lista_node && listb_node) {
        if(lista_node->data != listb_node->data)
            return 0;

        lista_node = lista_node->next;
        listb_node = listb_node->next;
    }

    return 1;
}

dlist_t *dlist_copy(dlist_t *list)
{
    dlist_t *copy = dlist_new();

    dlist_node_t *o_node = list->head;
    dlist_node_t *c_node;

    if(o_node != NULL) {
        c_node = malloc(sizeof(dlist_node_t));
        if(c_node == NULL) {
            return NULL;
        }

        memset(c_node, 0, sizeof(dlist_node_t));
        c_node->data = o_node->data;
        copy->head = c_node;
        
        while((o_node = o_node->next) != NULL) {
            // copy node
            c_node->next = malloc(sizeof(dlist_node_t));
            if(c_node->next == NULL) {
                return NULL;
            }

            memset(c_node->next, 0, sizeof(dlist_node_t));
            c_node->next->data = o_node->data;
            c_node->next->prev = c_node;
            c_node = c_node->next;
        }
    }
    
    copy->tail = c_node;
    copy->size = list->size;
    return copy;
}

void **dlist_to_array(dlist_t *list)
{
    if(list->size == 0) return NULL;
    void **array = malloc(list->size);
    dlist_node_t *node = list->head;

    int index = 0;
    while(node) {
        array[index] = node->data;
        node = node->next;
        index++;
    }

    return array;
}

static dlist_node_t *dlist_node_get(dlist_t *list, size_t pos)
{
    if(list->size == 0)
        return NULL;

    if(pos >= list->size)
        return NULL;

    if((pos-1) == list->size)
        return list->tail;

    if(pos == 0)
        return list->head;

    dlist_node_t *node;
    if(pos < (list->size/2)) {
        // pos is before the middle if the list,
        // thus we loop from the beginning
        node = list->head;

        while (node && pos) {
            pos--;
            node = node->next;
        }
    } else {
        // pos is after the middle of the list,
        // thus we loop from the end of the list
        node = list->tail;
        pos = (list->size - pos) - 1;

        while (node && pos) {
            pos--;
            node = node->prev;
        }
    }

    if(pos != 0) {
        return NULL;
    } else {
        return node;
    }
}
