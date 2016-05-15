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
#include <assert.h>

// allocate new node with given size
#define malloc_node(size) malloc(sizeof(slist_node_t) + (size))

// get the node at pos, or NULL
static slist_node_t *slist_node_get(const slist_t *list, size_t pos);

size_t slist_size(const slist_t *list) {
    if(list != NULL) {
        return list->size;
    }

    return 0;
}

size_t slist_length(const slist_t *list) {
    if(list != NULL) {
        return list->length;
    }

    return 0;
}

void *slist_first(const slist_t *list) {
    if(list != NULL && list->head != NULL) {
        return list->head->data;
    }

    return NULL;
}

void *slist_last(const slist_t *list) {
    if(list != NULL && list->tail != NULL) {
        return list->tail->data;
    }

    return NULL;
}

slist_t *slist_new(size_t size)
{
    // allocate memory for new list
    slist_t *list = malloc(sizeof(slist_t));

    // check if memory allocation worked
    if(list == NULL) {
        return NULL;
    }

    // initialize memory
    memset(list, 0, sizeof(slist_t));

    // set size
    list->size = size;

    return list;
}

slist_t *slist_init(slist_t *list, size_t size)
{
    // make sure list exists
    if(list == NULL) {
        return NULL;
    }

    // initialize memory
    memset(list, 0, sizeof(slist_t));

    // set size
    list->size = size;

    return list;
}

slist_t *slist_purge(slist_t *list)
{
    // start with the first node, pointed to
    // by list->head
    slist_node_t *cur = list->head;
    slist_node_t *next;

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

int slist_free(slist_t *list)
{
    // can't free a NULL pointer
    if(list == NULL)
        return -1;

    // free nodes
    slist_purge(list);

    // free list itself
    free(list);

    return 0;
}

void *slist_append(slist_t *list, void *data)
{
    // we want to add stuff past the last node
    slist_node_t *node = list->tail;

    // the list could be empty, so we have to
    // check for that
    if (node != NULL) {
        // append to existing node
        node->next = malloc_node(list->size);
        node = node->next;
    } else {
        // list is empty, so this is both the
        // first and the last node.
        node = malloc_node(list->size);
        list->head = node;
    }

    // make sure malloc worked
    if(node == NULL) {
        return NULL;
    }

    // initialize node
    node->next = NULL;

    // update slist properties
    list->tail = node;
    list->length++;

    // set the node's data
    if(data != NULL) {
        memcpy(node->data, data, list->size);
    }

    return node->data;
}

void *slist_prepend(slist_t *list, void *data)
{
    // allocate memory for new node
    slist_node_t *node = malloc_node(list->size);

    // make sure malloc worked
    if(node == NULL) {
        return NULL;
    }

    // set node data (if some data was supplied)
    if(data != NULL) {
        memcpy(node->data, data, list->size);
    }

    // initialize node: set next to
    // current head of the list
    node->next = list->head;

    // if the list was empty, the node needs to
    // also become the tail of the list, since
    // it's now the only node
    if (list->head == NULL) {
        list->tail = node;
    }

    // make node new head of list
    list->head = node;

    // update list size
    list->length++;

    return node->data;
}

void *slist_insert(slist_t *list, size_t pos, void *data)
{
    // there are some special cases where we can call
    // some optimized functions
    if (pos == 0) {
        // insertion at position 0 is the same as prepending
        return slist_prepend(list, data);
    } else if (pos == list->length) {
        // inserting at list->length is the same as appending
        return slist_append(list, data);
    } else if (pos > list->length) {
        // inserting at a non-valid position is not possible
        return NULL;
    } else {
        // by this point we know what pos is neither zero, nor
        // at the end of the list, nor past the end. so
        // we can safely get the node just before where we
        // want to insert:
        slist_node_t *prev = slist_node_get(list, pos-1);
        slist_node_t *next = prev->next;

        assert(prev != NULL);
        assert(next != NULL);
        
        // allocate memeory for new node
        slist_node_t *node = malloc_node(list->size);

        // make sure allocation worked
        if(node == NULL) {
            return NULL;
        }

        // connect nodes
        prev->next = node;
        node->next = next;

        // set data and update list
        if(data != NULL) {
            memcpy(node->data, data, list->size);
        }

        // update list
        list->length++;

        return node->data;
    }
}

int slist_remove(slist_t *list, size_t pos)
{
    if(list->length == 0) {
        // can't remove anything from an empty list
        return -1;
    } else if(pos == 0) {
        // removing the first element can be done efficiently
        // by using the pop function
        slist_pop(list, NULL);
    } else if(pos >= list->length) {
        // can't remove something which is not in the list
        return -2;
    } else {
        // by this point, we know that pos is valid in
        // the list, because the list contains elements,
        // pos is not zero and it's not past the end of
        // the list, so we can safely get a pointer to
        // the node just before the one we want to delete.
        slist_node_t *prev = slist_node_get(list, pos-1);
        assert(prev != NULL);

        // now we can also get a pointer to the node we
        // want to remove
        slist_node_t *node = prev->next;
        assert(node != NULL);

        // if the node is the last node in the list, we
        // have to change list->tail, so we check for that
        if (node->next == NULL) {
            assert(node == list->tail);

            // set tail to previous node
            list->tail = prev;
        } else {
            assert(node != list->tail);
        }
        
        // connect the previous node to the node
        // after the one we just deleted.
        prev->next = node->next;
        
        // get rid of the node
        free(node);

        // update the list
        list->length--;
    }

    return 0;
}

void *slist_set(slist_t *list, size_t pos, void *data)
{
    // get node
    slist_node_t *node = slist_node_get(list, pos);

    // make sure node exists
    if(node == NULL) {
        return NULL;
    }

    // copy data over if pointer is non-NULL
    if (data != NULL) {
        memcpy(node->data, data, list->size);
    }

    return node->data;
}

void *slist_get(const slist_t *list, size_t pos, void *data)
{
    // get node
    slist_node_t *node = slist_node_get(list, pos);

    // make sure node exists
    if(node == NULL) {
        return NULL;
    }

    // copy data over if pointer is non-NULL
    if(data != NULL) {
        memcpy(data, node->data, list->size);
    }

    return node->data;
}

void *slist_pop(slist_t *list, void *data)
{
    // this is the node to be popped
    slist_node_t *node = list->head;

    // make sure list isn't empty
    if (node == NULL) {
        assert(list->tail == NULL);
        assert(list->length == 0);
        return NULL;
    }

    // check if the list will be empty after
    // popping
    if (node->next) {
        // set the list's head to the node after
        // our node
        list->head = node->next;
    } else {
        assert(list->length == 1);

        // if we popped the last node, we reset the
        // list
        list->head = NULL;
        list->tail = NULL;
    }

    // update list info
    list->length--;

    // copy data if requested
    if(data != NULL) {
        memcpy(data, node->data, list->size);
    }

    free(node);

    return data;
}

int slist_swap(slist_t *list, size_t a, size_t b) {
    // FIXME
    return -1;
}

slist_t *slist_split(slist_t *list, size_t pos)
{
    // check if pos actually points to anything useful
    if(pos >= list->length) {
        return NULL;
    }

    // allocate new slist
    slist_t *new = slist_new(list->size);
    assert(new != NULL);

    // check if we should transfer the whole list
    if(pos == 0) {
        memcpy(new, list, sizeof(slist_t));
        memset(list,   0, sizeof(slist_t));

        // data size stays the same
        list->size = new->size;
    } else {
        // get the node just before pos
        slist_node_t *node = slist_node_get(list, pos-1);
        assert(node != NULL);

        // everything from node->next to
        // list->tail is now part of new
        new->tail = list->tail;
        new->head = node->next;

        // node is now the last node of
        // the list
        list->tail = node;
        node->next = NULL;

        // we also have to update
        // the lengths of both lists
        new->length = list->length - pos;
        list->length = pos;
    }

    return new;
}

slist_t *slist_join(slist_t *dest, slist_t *src)
{
    // if the data sizes used are not the same, return
    // NULL to indicate an error
    if(src->size != dest->size) {
        return NULL;
    }

    // if there is nothing to copy, just return dest
    if(src->length == 0) {
        return dest;
    }

    // if dest is an empty list, we can get away by simply
    // memcpy-ing src to dest and then clearing src out
    if(dest->length == 0) {
        memcpy(dest, src, sizeof(slist_t));
    } else {
        // otherwise, do it the hard way
        dest->tail->next = src->head;
        dest->tail       = src->tail;
        dest->length    += src->length;
    }

    // reset src, but keep data size
    memset(src, 0, sizeof(slist_t));
    src->size = dest->size;

    return dest;
}

slist_t *slist_copy(const slist_t *list)
{
    // allocate a new slist
    slist_t *copy = slist_new(list->size);

    // memory error checking
    if(copy == NULL) {
        return NULL;
    }

    // loop thought the original slist
    slist_node_t *node;
    for(node = list->head; node != NULL; node=node->next) {
        // add data as we go
        void *result = slist_append(copy, node->data);

        // make sure appending worked
        if(result == NULL) {
            slist_free(copy);
            return NULL;
        }
    }

    return copy;
}

int slist_verify(slist_t *list) {
    if(list == NULL) {
        return -1;
    }

    slist_node_t **nodes_seen = malloc(sizeof(slist_node_t*) * list->length);
    size_t cur_index = 0;

    for(slist_node_t *node = list->head; node != NULL; node = node->next) {
        if((cur_index+1) == list->length) {
            if(node != list->tail) {
                return -4;
            }

            if(node->next != NULL) {
                return -5;
            }
        }

        for(size_t i = 0; i < cur_index; i++) {
            if(nodes_seen[i] == node) {
                return -2;
            }
        }

        nodes_seen[cur_index] = node;
        cur_index++;
    }

    return 0;
}

/*
slist_t *slist_from_array(void **array, size_t len, size_t size)
{
    slist_t *list = slist_new(size);

    if(list == NULL)
        return NULL;
    
    size_t i;
    for(i = 0; i < len; ++i) {
        slist_t *ret = slist_append(list, array[i]);

        if(ret == NULL)
            return NULL;
    }

    return list;
}
*/

/*
slist_t *slist_from_dlist(dlist_t *dlist)
{
    slist_t *list = slist_new(dlist->size);

    if(list == NULL)
        return NULL;

    dlist_node_t *node;
    for(node = dlist->head; node != NULL; node = node->next) {
        int ret = slist_append(list, node->data);

        if(ret < 0)
            return NULL;
    }

    return list;
}
*/

/*
void **slist_to_array(slist_t *list)
{
    if(list->size == 0)
        return NULL;

    void **array = malloc(list->size * sizeof(void*));
    
    if(array == NULL)
        return NULL;

    slist_node_t *node = list->head;
    size_t i = 0;
    while((node != NULL) && (i < list->size)) {
        array[i] = node->data;

        node = node->next;
        ++i;
    }

    if(i != (list->size-1)) {
        free(array);
        array = NULL;
    }

    return array;
}
*/

/* this is an internal function used to extract the node at
 * pos of a given list, or NULL if it doesn't exist */
static slist_node_t *slist_node_get(const slist_t *list, size_t pos)
{
    /* obviously, an empty list does not have any nodes
     * that could be extracted, so return NULL
     */
    if (list->length == 0)
        return NULL;

    /* shortcuts */
    if (pos == 0)
        /* head is the first element, at pos=0 */
        return list->head;
    else if (pos == (list->length-1))
        /* tail is the last element, at pos=size-1 */
        return list->tail;
    else if (pos >= list->length)
        /* anything greater or equal than size is beyond
         * the lendth of the list, thus there is no node
         * that could be extracted */
        return NULL;

    /* if none of the shortcuts worked, extract the node
     * by traversing the list */
    slist_node_t *node = list->head;
    while ((node != NULL) && (pos != 0)) {
        /* pos is now the 'distance' between the current
         * node and the one we want. decrease pos as we
         * get closer to it, and once pos=0, we have what
         * we were looking for. if we encounter NULL on
         * the way, there is an error in the list! */
        pos--;
        node = node->next;
    }

    /* error in the list! bad! */
    if(pos != 0)
        return NULL;

    return node;
}
