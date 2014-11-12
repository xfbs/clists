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

int dlist_remove(dlist_t *list, size_t pos)
{
    /* can't remove anything from an empty list */
    if(list->size == 0)
        return -1;

    /* can't remove if pos is not valid */
    if(pos >= list->size)
        return -1;

    /* removing at position 0 is basically popping but
     * discarding the data */
    if(pos == 0) {
        dlist_pop(list);
    } else {
        /* extract the node we want to remove */
        dlist_node_t *node = dlist_node_get(list, pos);

        /* make sure the node exists */
        if(node == NULL)
            return -1;

        /* since we have a guarantee that pos!=0, we
         * only have two cases left: pos could be in the
         * middle of the list or it could be at the
         * end. distinguish between the two: */
        if(node == list->tail) {
            /* this is the last node. make the node before
             * it the last node */
            list->tail = node->prev;
        } else {
            /* node is not the last node in the list. make
             * the backpointer of the node after it point
             * to the node before it */
            node->next->prev = node->prev;
        }

        /* connect the node before it with what comes after
         * the node or if node is last, indicate the previous
         * node that it's the last */
        node->prev->next = node->next;

        /* update list size to reflect removed node */
        list->size--;
        free(node);
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

dlist_t *dlist_from_slist(slist_t *list)
{
    /* allocate new dlist */
    dlist_t *new = dlist_new();

    /* make sure allocation worked */
    if(new == NULL)
        return NULL;

    /* iterate through the slist, adding elements
     * to our very own dlist as we go */
    slist_node_t *node = list->head;
    while(node) {
        int ret = dlist_append(new, node->data);

        /* make sure appending worked */
        if(ret < 0) {
            dlist_free(new);
            return NULL;
        }

        /* proceed to next node */
        node = node->next;
    }

    return new;
}

dlist_t *dlist_from_array(void **array, size_t size)
{
    /* create new dlist */
    dlist_t *list = dlist_new();

    /* make sure allocation worked */
    if(list == NULL)
        return NULL;

    /* loop through the array, adding stuff to the list
     * as we go */
    int i;
    for(i = 0; i < size; ++i) {
        int ret = dlist_append(list, array[i]);

        /* make sure appending worked */
        if(ret < 0) {
            dlist_free(list);
            return NULL;
        }
    }

    return list;
}

void **dlist_to_array(dlist_t *list)
{
    /* creating an empty array doesn't make sense so
     * simply return NULL if list is empty */
    if(list->size == 0)
        return NULL;

    /* allocate memory for array */
    void **array = malloc(list->size);

    /* make sure memory allocation worked */
    if(array == NULL)
        return NULL;

    /* extract first node for walking through it */
    dlist_node_t *node = list->head;

    /* walk through the dlist, noting the index
     * because we don't want a buffer overflow (even
     * if the list is corrupt) */
    size_t i = 0;
    while((node != NULL) && (i < list->size)) {
        /* copy data to array */
        array[i] = node->data;

        /* proceed to next node */
        node = node->next;

        /* go to next index */
        ++i;
    }

    return array;
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
