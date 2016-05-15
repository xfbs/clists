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

// allocate new node with given size
#define malloc_node(size) malloc(sizeof(dlist_node_t) + (size))

// get the node at pos, or NULL
static dlist_node_t *dlist_node_get(dlist_t *list, size_t pos);

size_t dlist_size(const dlist_t *list) {
    if(list != NULL) {
        return list->size;
    }

    return 0;
}

size_t dlist_length(const dlist_t *list) {
    if(list != NULL) {
        return list->length;
    }

    return 0;
}

void *dlist_first(const dlist_t *list) {
    if(list != NULL && list->head != NULL) {
        return list->head->data;
    }

    return NULL;
}

void *dlist_last(const dlist_t *list) {
    if(list != NULL && list->tail != NULL) {
        return list->tail->data;
    }

    return NULL;
}

dlist_t *dlist_new(size_t size)
{
    // allocate memory for new list
    dlist_t *list = malloc(sizeof(dlist_t));

    // check if memory allocation worked
    if(list == NULL) {
        return NULL;
    }

    // initialize memory
    memset(list, 0, sizeof(dlist_t));

    // set size
    list->size = size;

    return list;
}

dlist_t *dlist_init(dlist_t *list, size_t size)
{
    // make sure list exists
    if(list == NULL) {
        return NULL;
    }

    // initialize memory
    memset(list, 0, sizeof(dlist_t));

    // set size
    list->size = size;

    return list;
}

dlist_t *dlist_purge(dlist_t *list)
{
    // start with the first node, pointed to
    // by list->head
    dlist_node_t *cur = list->head;
    dlist_node_t *next;

    while (cur != NULL) {
        // remember which node was supposed to
        // come next so we can safely free cur
        next = cur->next;

        // free current node
        free(cur);

        // advance to next node
        cur = next;
    }

    // reset everything but list->size
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;

    return list;
}

int dlist_free(dlist_t *list)
{
    // can't free a NULL pointer
    if(list == NULL)
        return -1;

    // free nodes
    dlist_purge(list);

    // free list itself
    free(list);

    return 0;
}

void *dlist_append(dlist_t *list, void *data)
{
    // allocate new node
    dlist_node_t *node = malloc_node(list->size);

    // make sure the malloc call worked 
    if(node == NULL) {
        return NULL;
    }

    // initialize node
    node->next = NULL;
    node->prev = NULL;

    // set node data, if necessary
    if(data != NULL) {
        memcpy(node->data, data, list->size);
    }

    // the list could be empty, in which
    // case we have to set both head and tail
    // to the node, so we check for that
    if(list->tail != NULL) {
        // link the new node with the previous
        // last node of the list
        node->prev = list->tail;
        list->tail->next = node;

        // make out node the new last node
        list->tail = node;
    } else {
        assert(list->length == 0);

        // make this node the one and only
        list->head = node;
        list->tail = node;
    }

    // increase length to reflect added node
    list->length++;

    return node->data;
}

void *dlist_prepend(dlist_t *list, void *data)
{
    // allocate new node
    dlist_node_t *node = malloc_node(list->size);

    // make sure allocation worked
    if(node == NULL) {
        return NULL;
    }

    // initialize node
    node->head = NULL;
    node->tail = NULL;

    // set node data, if necessary
    if(data != NULL) {
        memcpy(node->data, data, list->size);
    }

    // we have to check if the list was empty
    if(list->head != NULL) {
        // connect node with previous head of list
        node->next = list->head;
        list->head->prev = node;

        // set this node as the new head
        list->head = node;
    } else {
        // make this node the one and only
        list->head = node;
        list->tail = node;
    }

    // increase length to reflect added node
    list->length++;

    return node->data;
}

void *dlist_insert(dlist_t *list, size_t pos, void *data)
{
    // there are some optimizations we can do on
    // edge cases
    if(pos == 0) {
        // inserting at pos 0 is the same as prepending
        return dlist_prepend(list, data);
    } else if(pos == list->length) {
        // inserting to the end of the list is the same
        // as appending
        return dlist_append(list, data);
    } else if(pos > list->length) {
        // can't add data past the end of the list
        return NULL;
    } else {
        // we now know that pos does not point to the
        // first, last or pase the end of the list
        dlist_node_t *new = malloc_node(list->size);

        if(new == NULL) {
            return NULL;
        }

        // set node data, if neccessary
        if(data != NULL) {
            memcpy(new->data, data, list->size);
        }

        // get a pointer to the node before
        // where we want to insert
        dlist_node_t *node = dlist_node_get(list, pos-1);

        if(node == NULL) {
            free(new);
            return NULL;
        }

        // insert new node in between
        // node and node->next
        assert(node->next != NULL);
        assert(node->next->prev != NULL);
        node->next->prev = new;
        new->next = node->next;
        new->prev = node;
        node->next = new;

        // increase list length
        list->length++;
        
        return new->data;;
    }
}

int dlist_remove(dlist_t *list, size_t pos)
{
    // can't remove anything from an empty list
    if(list->head == NULL) {
        assert(list->length == 0);
        return -1;
    }

    // can't remove if pos is not valid
    if(pos >= list->length) {
        return -1;
    }

    // removing at position 0 is basically popping but
    // discarding the data
    if(pos == 0) {
        dlist_pop(list, NULL);
    }
    
    // extract the node we want to remove
    dlist_node_t *node = dlist_node_get(list, pos);

    // make sure the node exists
    if(node == NULL) {
        return -1;
    }

    // the node could now be in the middle 
    // or at the end of the list
    if(node == list->tail) {
        assert(node->next == NULL);

        // this is the last node. make the node before
        // it the last node
        list->tail = node->prev;
    } else {
        assert(node->next != NULL);

        // it is not the last node in the list,
        // so there is a node after it which
        // needs to be connected to the one
        // before it.
        node->next->prev = node->prev;
    }

    // node->next can be NULL, in this case it updates
    // the previous node to be the last one, or otherwise
    // connect the previous node to the next one
    node->prev->next = node->next;

    // update list size to reflect removed node
    list->length--;

    free(node);
    return 0;
}

void *dlist_set(dlist_t *list, size_t pos, void *data)
{
    // get the node at pos
    dlist_node_t *node = dlist_node_get(list, pos);

    // make sure it exists
    if(node == NULL) {
        return NULL;
    }

    // if given, set data
    if(data != NULL) {
        memcpy(node->data, data, list->size);
    }

    return node->data;
}

void *dlist_get(dlist_t *list, size_t pos, void *data)
{
    // get the node at pos
    dlist_node_t *node = dlist_node_get(list, pos);

    // make sure it exists
    if(node == NULL) {
        return NULL;
    }

    // if given, get data
    if(data != NULL) {
        memcpy(data, node->data, list->size);
    }

    return node->data;
}

void *dlist_pop(dlist_t *list)
{
    void *data;
    dlist_node_t *node;

    switch(list->size) {
        case 0:
            /* can't pop anything from an empty list */
            return NULL;
            break;
        case 1:
            /* if list has size 1, we have to set it to
             * be empty after extracting the data */
            node = list->head;
            data = node->data;
            memset(list, 0, sizeof(dlist_t));
            break;
        default:
            /* extract head node */
            node = list->head;

            /* delete back reference to this node */
            if(node->next)
                node->next->prev = NULL;

            /* make list->head point to node after
             * head node */
            list->head = node->next;

            /* update size to account for extracted
             * node */
            list->size--;

            data = node->data;
            break;
    }

    free(node);
    return data;
}

dlist_t *dlist_chop(dlist_t *list, size_t pos)
{
    /* you can't chop a list up if it doesn't have any
     * data in it */
    if(list->size == 0)
        return NULL;

    /* chopping anything past the end of the list
     * is not possible */
    if(list->size <= pos)
        return NULL;

    /* allocate new dlist */
    dlist_t *chopped = dlist_new();

    /* make sure allocation was successful */
    if(list == NULL)
        return NULL;

    /* the pos that is supplied is supposed to be
     * the first element of the chopped list */
    if(pos == 0) {
        /* transfer list to new chopped list */
        memcpy(chopped, list, sizeof(dlist_t));

        /* reset original list */
        memset(list, 0, sizeof(dlist_t));
    } else {
        /* find the node just before where the
         * chopping is supposed to take place */
        dlist_node_t *node = dlist_node_get(list, pos-1);

        /* make sure node exists and there are
         * nodes after it that can be transferred */
        if((node == NULL) || (node->next == NULL)) {
            free(chopped);
            return NULL;
        }

        /* transfer all nodes past node to chopped */
        chopped->head = node->next;
        chopped->tail = list->tail;
        list->tail = node;

        /* disconnect nodes */
        node->next = NULL;
        chopped->head->prev = NULL;
    }

    return chopped;
}

dlist_t *dlist_join(dlist_t *dest, dlist_t *src)
{
    /* if there is nothing to be copied, don't
     * do anything */
    if(src->size == 0)
        return dest;

    /* if dest is empty, we can get away with
     * simply copying data */
    if(dest->size == 0) {
        memcpy(dest, src, sizeof(dlist_t));
    } else {
        /* otherwise, it seems like we have to
         * do some actual work. eww. so let's
         * copy some nodes! */
        dest->tail->next = src->head;
        src->head->prev = dest->tail;
        dest->tail = src->tail;
    }

    /* initialize src (because we just extracted
     * all it's nodes) */
    memset(src, 0, sizeof(dlist_t));

    return dest;
}

int dlist_reverse(dlist_t *list)
{
    /* this is a fun one: reverse the order of
     * all nodes of the list. when I say 'fun',
     * I really mean 'easy'. but do make sure the
     * list actually exists! */
    if(list == NULL)
        return -1;

    /* for every node, swap node->next and
     * node->prev */
    dlist_node_t *node = list->head;
    dlist_node_t *tmp;
    while(node) {
        tmp = node->next;
        node->next = node->prev;
        node->prev = tmp;

        /* since we just swapped next and prev,
         * going forward in the list is done by
         * going to node->prev */
        node = node->prev;
    }

    /* finally, swap list->head and list->tail */
    tmp = list->head;
    list->head = list->tail;
    list->tail = list->head;

    return 0;
}

/* create a copy of a list */
dlist_t *dlist_copy(dlist_t *list)
{
    /* create new list */
    dlist_t *clist = dlist_new();

    /* node is the one from the original list
     * and copy is the one we create as copy */
    dlist_node_t *node = list->head;
    dlist_node_t *cnode;

    if(node != NULL) {
        /* allocate new copy node */
        cnode = malloc(sizeof(dlist_node_t));

        /* make sure allocation worked */
        if(cnode == NULL)
            return NULL;

        /* initialize node */
        memset(cnode, 0, sizeof(dlist_node_t));

        /* copy data */
        cnode->data = node->data;

        /* set this node as head of list */
        clist->head = cnode;
        
        /* once the head node exists, we can iterate
         * through the other nodes and add the sequentially */
        while((node = node->next) != NULL) {
            /* copy the current node */
            cnode->next = malloc(sizeof(dlist_node_t));

            /* make sure memory allocation worked */
            if(cnode->next == NULL)
                return NULL;

            /* initialize memory */
            memset(cnode->next, 0, sizeof(dlist_node_t));

            /* set node data and prev pointer */
            cnode->next->data = node->data;
            cnode->next->prev = cnode;

            /* move to next node */
            cnode = cnode->next;
        }
    }
    
    /* set tail of list */
    clist->tail = cnode;

    /* copy list size */
    clist->size = list->size;
    return clist;
}

/* internal function used to extract a node at a
 * given position or NULL if it doesn't exists. this
 * function is smart about accessing the list, working
 * backwards if pos is closer to tail of list.
 */
static dlist_node_t *dlist_node_get(dlist_t *list, size_t pos)
{
    /* can't return a node of an empty list */
    if(list->size == 0)
        return NULL;

    /* can't return a node at an invalid pos */
    if(pos >= list->size)
        return NULL;

    /* easy access nodes */
    if((pos-1) == list->size)
        return list->tail;
    if(pos == 0)
        return list->head;

    /* if we get here, we have the guarantee that pos
     * is within the list and neither the head nor the
     * tail of the list */
    dlist_node_t *node;
    if(pos < (list->size/2)) {
        /* pos is located closer to the head than the
         * tail, so work from there */
        node = list->head;

        /* traverse the list forwards while decrementing
         * pos - pos describes the distance between the
         * current node and the one we need */
        while (node && pos) {
            node = node->next;
            pos--;
        }
    } else {
        /* pos is located closer to the tail of the list
         * so work from there */
        node = list->tail;

        /* since pos should describe the distance between
         * the current node and the node we need, change
         * it to work backwards */
        pos = (list->size - pos) - 1;

        /* get the node */
        while (node && pos) {
            node = node->prev;
            pos--;
        }
    }

    /* if pos is not 0, it means that at some point while
     * traversing the list, we encountered a NULL. not good.
     * return NULL because there's not much we can do */
    if(pos != 0) {
        return NULL;
    } else {
        return node;
    }
}
