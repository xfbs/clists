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
#include <assert.h>

// allocate new node with given size
#define malloc_node(size) malloc(sizeof(dlist_node_t) + (size))

// swap two variables
#define swap(x,y) do {   \
    typeof(x) _x = x;      \
    typeof(y) _y = y;      \
    x = _y;                \
    y = _x;                \
    } while(0)

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

        // make our node the new last node
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
    node->next = NULL;
    node->prev = NULL;

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
        return 0;
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

    // make sure it exists and we have some
    // data to set
    if(node == NULL || data == NULL) {
        return NULL;
    }

    // set data
    memcpy(node->data, data, list->size);

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

void *dlist_pop(dlist_t *list, void *data)
{
    // this is the node to be popped
    dlist_node_t *node = list->head;

    // make sure it exists
    if(node == NULL) {
        assert(list->tail == NULL);
        assert(list->length == 0);
        return NULL;
    }

    // check if the list will be empty after
    // popping
    if(node->next) {
        // make the second node the first
        // node
        node->next->prev = NULL;
        list->head = node->next;
    } else {
        assert(list->length == 1);

        // if we popped the last node, we
        // reset the list
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

int dlist_swap(dlist_t *list, size_t pos_a, size_t pos_b) {
    // you can't swap an element with itself
    if(pos_a == pos_b) {
        return -1;
    }

    // make sure that pos_a is smaller than pos_b
    if(pos_a > pos_b) {
        swap(pos_a, pos_b);
    }

    dlist_node_t *node_a = NULL;
    dlist_node_t *node_b = NULL;
    dlist_node_t *node;

    // determine if it makes more sense to scan the
    // list forward or backwards to get both
    // nodes
    if(pos_a < ((list->length - pos_b)-1)) {
        // scan forwards
        node = list->head;

        for(size_t i = 0; 
            node != NULL && (node_a == NULL || node_b == NULL); 
            i++, node = node->next) 
        {
            if(i == pos_a) node_a = node;
            if(i == pos_b) node_b = node;
        }
    } else {
        // scan backwards
        node = list->tail;

        for(size_t i = list->length-1;
            node != NULL && (node_a == NULL || node_b == NULL);
            i++, node = node->prev)
        {
            if(i == pos_a) node_a = node;
            if(i == pos_b) node_b = node;
        }
    }

    // if we couldn't find either one of the
    // nodes, there must be something wrong
    if(node_a == NULL || node_b == NULL) {
        return -1;
    }

    // node_a could be the first node and
    // node_b could be the last node, so
    // we have to treat those cases differently
    if(node_a->prev == NULL) {
        assert(pos_a == 0);
        assert(node_a == list->head);
        list->head = node_b;
        node_b->prev->next = node_a;
    } else {
        swap(node_a->prev->next, node_b->prev->next);
    }

    if(node_b->next == NULL) {
        assert(pos_b == (list->length-1));
        assert(node_b == list->tail);
        list->tail = node_a;
        node_a->next->prev = node_b;
    } else {
        swap(node_a->next->prev, node_b->next->prev);
    }

    swap(node_a->next, node_b->next);
    swap(node_a->prev, node_b->prev);

    return 0;
}


dlist_t *dlist_split(dlist_t *list, size_t pos)
{
    // check if pos points at anything
    // useful
    if(pos >= list->length) {
        return NULL;
    }

    // allocate new dlist
    dlist_t *new = dlist_new(list->size);
    assert(new != NULL);

    // check if we should transfer the
    // whole list
    if(pos == 0) {
        memcpy(new, list, sizeof(dlist_t));
        memset(list,   0, sizeof(dlist_t));

        // data size stays the same
        list->size = new->size;
    } else {
        // get the node just before pos
        dlist_node_t *node = dlist_node_get(list, pos-1);
        assert(node != NULL);

        // set head and tail of new list
        new->tail = list->tail;
        new->head = node->next;

        // cut list and nodes
        list->tail = node;
        node->next->prev = NULL;
        node->next = NULL;

        // update new length of both
        // lists
        new->length = list->length - pos;
        list->length = pos;
    }

    return new;
}

dlist_t *dlist_join(dlist_t *dest, dlist_t *src)
{
    // if the data sizes used are not the same,
    // return NULL to indicate error
    if(src->size != dest->size) {
        return NULL;
    }

    // if there is nothing to be copied, don't
    // do anything
    if(src->length == 0) {
        return dest;
    }

    // if dest is empty, we can get away with
    // simply copying data */
    if(dest->size == 0) {
        memcpy(dest, src, sizeof(dlist_t));
    } else {
        // otherwise, it seems like we have to
        // do some actual work. eww. so let's
        // copy some nodes!
        dest->tail->next = src->head;
        src->head->prev  = dest->tail;
        dest->tail       = src->tail;
        dest->length    += src->length;
    }

    // reset src, but keep data size
    memset(src, 0, sizeof(dlist_t));
    src->size = dest->size;

    return dest;
}

int dlist_reverse(dlist_t *list)
{
    for(dlist_node_t *node = list->head; node != NULL; node = node->prev) {
        // for every node, swap node->next and
        // node->prev
        swap(node->next, node->prev);
    }
    
    // also swap list head and tail
    swap(list->head, list->tail);

    return 0;
}

/* create a copy of a list */
dlist_t *dlist_copy(const dlist_t *list)
{
    // allocate new list
    dlist_t *copy = dlist_new(list->size);

    // make sure malloc worked
    if(copy == NULL) {
        return NULL;
    }

    /* node is the one from the original list
     * and copy is the one we create as copy */
    for(dlist_node_t *node = list->head; node != NULL; node = node->next) {
        // add data as we go
        void *result = dlist_append(copy, node->data);

        // make sure appending worked
        if(result == NULL) {
            dlist_free(copy);
            return NULL;
        }
    }

    return copy;
}

int dlist_verify(const dlist_t *list) {
    if(list == NULL) {
        return -1;
    }

    dlist_node_t **nodes_seen = malloc(sizeof(dlist_node_t*) * list->length);
    size_t cur_index = 0;

    for(dlist_node_t *node = list->head; node != NULL; node = node->next) {
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

    if(cur_index != list->length) {
        return -6;
    }

    for(dlist_node_t *node = list->tail; node != NULL; node = node->next) {
        if(nodes_seen[cur_index-1] != node) {
            return -8;
        }

        cur_index--;
    }

    free(nodes_seen);
    
    // FIXME: check backwards!

    return 0;
}

// internal function used to extract a node at a
// given position or NULL if it doesn't exists. this
// function is smart about accessing the list, working
// backwards if pos is closer to tail of list.
static dlist_node_t *dlist_node_get(dlist_t *list, size_t pos)
{
    // can't return a node of an empty list
    if(list->length == 0) {
        return NULL;
    }

    // can't return a node at an invalid pos
    if(pos >= list->length) {
        return NULL;
    }

    // easy access nodes
    if((pos-1) == list->length) {
        return list->tail;
    }

    if(pos == 0) {
        return list->head;
    }

    // if we get here, we have the guarantee that pos
    // is within the list and neither the head nor the
    // tail of the list
    dlist_node_t *node;
    if(pos < (list->length/2)) {
        // pos is located closer to the head than the
        // tail, so work from there
        node = list->head;

        // traverse the list forwards while decrementing
        // pos - pos describes the distance between the
        // current node and the one we need
        while (node && pos) {
            node = node->next;
            pos--;
        }
    } else {
        // pos is located closer to the tail of the list
        // so work from there
        node = list->tail;

        // since pos should describe the distance between
        // the current node and the node we need, change
        // it to work backwards
        pos = (list->length - pos) - 1;

        // get the node
        while (node && pos) {
            node = node->prev;
            pos--;
        }
    }

    // if pos is not 0, it means that at some point while
    // traversing the list, we encountered a NULL. not good.
    // return NULL because there's not much we can do
    if(pos != 0) {
        return NULL;
    } else {
        return node;
    }
}
