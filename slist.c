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
    /* allocate memory for new list */
    slist_t *list = malloc(sizeof(slist_t));

    /* check if memory allocation worked */
    if(list == NULL)
        return NULL;

    /* initialize memory */
    memset(list, 0, sizeof(slist_t));
    return list;
}

int slist_init(slist_t *list)
{
    /* error checking */
    if(list == NULL)
        return -1;

    /* initialize memory */
    memset(list, 0, sizeof(slist_t));
    return 0;
}

/*  for every node in the list, free the node
 *  and reset the list
 */
int slist_purge(slist_t *list)
{
    /* start with the first node, pointed to
     * by list->head
     */
    slist_node_t *cur = list->head;
    slist_node_t *next;

    while (cur != NULL) {
        /* store ptr to next node (because we
         * are freeing this node now and thus
         * can't access it later) */
        next = cur->next;

        /* free current node */
        free(cur);

        /* advance to next node */
        cur = next;
    }

    /* initialize list to make it empty */
    memset(list, 0, sizeof(slist_t));
    return 0;
}

int slist_free(slist_t *list)
{
    /* error checking */
    if(list == NULL)
        return -1;

    /* free nodes */
    int ret = slist_purge(list);

    free(list);

    /* return whatever purge gave back
     * to propagate eventual errors */
    return ret;
}

int slist_append(slist_t *list, void *data)
{
    /* we want to add stuff past the last node */
    slist_node_t *node = list->tail;

    /* there are two possibilities here: either
     * the list is empty and there is no last node,
     * or it's full and we can simply append after
     * the last one */
    if (node != NULL) {
        /* append to existing node */
        node->next = malloc(sizeof(slist_node_t));
        node = node->next;
    } else {
        /* make it the first node */
        node = malloc(sizeof(slist_node_t));
        list->head = node;
    }

    /* check for memory allocation errors */
    if(node == NULL)
        return -1;

    /* initialize node */
    memset(node, 0, sizeof(slist_node_t));

    /* update slist properties */
    list->tail = node;
    list->size++;

    /* set the node's data */
    node->data = data;

    return 0;
}

int slist_prepend(slist_t *list, void *data)
{
    /* allocate memory for new node */
    slist_node_t *node = malloc(sizeof(slist_node_t));

    /* memory allocation error checking */
    if(node == NULL)
        return -1;

    /* initialize new node */
    memset(node, 0, sizeof(slist_node_t));

    /* set it's data */
    node->data = data;

    /* is the list empty? */
    if (list->head != NULL) {
        /* if not, attach existing nodes to
         * the new node */
        node->next = list->head;
    } else {
        /* list is empty, so this node is the
         * only node and as such, it is both
         * the head and the tail of the list
         */
        list->tail = node;
    }

    /* make node new head of list */
    list->head = node;

    /* update list size */
    list->size++;

    return 0;
}

int slist_insert(slist_t *list, size_t pos, void *data)
{
    if (pos == 0) {
        /* insertion at position 0 is the same as prepending,
         * so use that method */
        slist_prepend(list, data);
    } else if (pos == list->size) {
        /* inserting at list->size is the same as appending,
         * so use that method */
        slist_append(list, data);
    } else if (pos > list->size) {
        /* inserting at a non-valid position is not possible */
        return -1;
    } else {
        /* get the node located before pos (this is guaranteed
         * not to be the head or the tail, because of the if
         * conditions above) and a pointer to the node after
         * it (which is supposed to not be NULL) */
        slist_node_t *prev = slist_node_get(list, pos-1);
        slist_node_t *next = prev->next;
        
        /* allocate memeory for new node */
        slist_node_t *node = malloc(sizeof(slist_node_t));
        if(node == NULL)
            return -1;

        /* initialize memory */
        memset(node, 0, sizeof(slist_node_t));

        /* connect nodes */
        prev->next = node;
        node->next = next;

        /* set data and update list */
        node->data = data;
        list->size++;
    }

    return 0;
}

int slist_remove(slist_t *list, size_t pos)
{
    if(list->size == 0) {
        /* can't remove anything from an empty list */
        return -1;
    } else if(pos == 0) {
        /* removing the first element can be done efficiently
         * by using the pop function */
        slist_pop(list);
    } else if(pos >= list->size) {
        /* can't remove something which is not in the list */
        return -1;
    } else {
        /* get a pointer to the node before pos - this is
         * guaranteed to exist, because we know that the list
         * is not empty, pos!=0 and pos is valid in the list
         */
        slist_node_t *prev = slist_node_get(list, pos-1);

        /* error checking - prev must exist, and prev->next,
         * which is supposed to point to the node we want to
         * remove, should also exist */
        if ((prev == NULL) || (prev->next == NULL)) {
            return -1;
        }

        /* pointer to the node we want to remove */
        slist_node_t *node = prev->next;

        if (node == list->tail) {
            /* if the node to be removed is the last node,
             * we have to update the list so that prev is now
             * the tail */
            list->tail = prev;
            prev->next = NULL;
        } else {
            /* connect the previous node the to the next node,
             * thereby skipping the current node */
            prev->next = node->next;
        }
        
        free(node);
        list->size--;
    }

    return 0;
}

int slist_set(slist_t *list, size_t pos, void *data)
{
    /* get node */
    slist_node_t *node = slist_node_get(list, pos);

    /* set data or return error if node doesn't exist */
    if (node != NULL) {
        node->data = data;
        return 0;
    } else {
        return -1;
    }
}

void *slist_get(slist_t *list, size_t pos)
{
    /* get node */
    slist_node_t *node = slist_node_get(list, pos);

    /* return data or NULL if node doesn't exist
     * since NULL can be valid data, it is smart to
     * make sure the pos you are requesting actually
     * exists */
    return((node) ? node->data : NULL);
}

void *slist_pop(slist_t *list)
{
    /* get pointer to head, this is the node that is
     * to be removed and it's data returned */
    slist_node_t *head = list->head;

    /* error checking - again, NULL can be valid data,
     * so might be smart to check size before doing
     * a pop */
    if (head == NULL)
        return NULL;

    /* save the data, because we're going to free the
     * memory of the node later */
    void *data = head->data;

    if (head->next) {
        /* if list will not be empty after the pop,
         * simply update it to make head point to the
         * next node */
        list->head = head->next;
    } else {
        /* if this was the last node, reset list */
        list->head = NULL;
        list->tail = NULL;
    }

    list->size--;
    free(head);

    return data;
}

slist_t *slist_chop(slist_t *list, size_t pos)
{
    /* check if pos actually points to anything useful */
    if(pos >= list->size)
        return NULL;

    /* allocate new slist */
    slist_t *new = slist_new();

    /* check if we should transfer the whole list */
    if(pos == 0) {
        memcpy(new, list, sizeof(slist_t));
        memset(list,   0, sizeof(slist_t));
        return new;
    }

    /* get the node just before pos */
    slist_node_t *node = slist_node_get(list, pos-1);

    /* make sure it actually exists */
    if(node == NULL) {
        free(new);
        return NULL;
    }

    /* chop the list! */
    new->tail = list->tail;
    new->head = node->next;
    new->size = list->size - pos;
    list->tail = node;
    list->size = pos;

    return new;
}

slist_t *slist_join(slist_t *dest, slist_t *src)
{
    /* if any of the parameters are NULL, return NULL to
     * indicate an error */
    if(dest == NULL || src == NULL)
        return NULL;

    /* if there is nothing to copy, just return dest */
    if(src->size == 0)
        return dest;

    /* if dest is an empty list, we can get away by simply
     * memcpy-ing src to dest and then clearing src out */
    if(dest->size == 0) {
        memcpy(dest, src, sizeof(slist_t));
        memset(src,    0, sizeof(slist_t));
    } else {
        /* otherwise, do it the hard way. */
        dest->tail->next = src->head;
        dest->tail       = src->tail;
        dest->size      += src->size;
    }

    return dest;
}

slist_t *slist_copy(slist_t *list)
{
    /* allocate a new slist */
    slist_t *copy = slist_new();

    /* memory error checking */
    if(copy == NULL)
        return NULL;

    /* loop thought the original slist */
    slist_node_t *node;
    for(node = list->head; node != NULL; node=node->next) {
        /* add data as we go */
        int ret = slist_append(copy, node->data);

        /* if ret=-1, something went wrong with memory
         * allocation while appending. technically, we'd
         * have to clean up, but as this can really only
         * happen if something if wrong with the system,
         * we just return NULL because nothing good can 
         * come out of a system with a failed malloc call
         */
        if(ret < 0)
            return NULL;
    }

    return copy;
}

slist_t *slist_from_array(void **array, size_t len)
{
    /* create new slist */
    slist_t *list = slist_new();

    /* memory allocarion error checking */
    if(list == NULL)
        return NULL;

    /* loop through data, adding it to slist as we go */
    size_t i;
    for(i = 0; i < len; ++i) {
        int ret = slist_append(list, array[i]);

        /* memory error checking */
        if(ret < 0)
            return NULL;
    }

    return list;
}

slist_t *slist_from_dlist(dlist_t *dlist)
{
    /* allocate new slist */
    slist_t *list = slist_new();

    /* memory allocation error checking */
    if(list == NULL)
        return NULL;

    /* loop through the dlist, appending data to
     * the slist as we go */
    dlist_node_t *node;
    for(node = dlist->head; node != NULL; node = node->next) {
        int ret = slist_append(list, node->data);

        /* check the return value for errors */
        if(ret < 0)
            return NULL;
    }

    return list;
}


void **slist_to_array(slist_t *list)
{
    /* creating an empty array doesn't make sense so
     * simply return NULL if list is empty */
    if(list->size == 0)
        return NULL;

    /* allocate an array with the size of the list */
    void **array = malloc(list->size * sizeof(void*));
    
    /* memory error checking */
    if(array == NULL)
        return NULL;

    /* loop through the list, adding data to the array
     * as we go and making sure that we are in no case
     * adding anything past the end of the array */
    slist_node_t *node = list->head;
    size_t i = 0;
    while((node != NULL) && (i < list->size)) {
        /* write data */
        array[i] = node->data;

        /* proceed to next node and update i */
        node = node->next;
        ++i;
    }

    /* if all went well, i should now point to the
     * last element written, which is list->size-1
     */
    if(i != (list->size-1)) {
        /* something went wrong. free the array and
         * set it to NULL to indicate this to the
         * caller */
        free(array);
        array = NULL;
    }

    return array;
}

/* this is an internal function used to extract the node at
 * pos of a given list, or NULL if it doesn't exist */
static slist_node_t *slist_node_get(slist_t *list, size_t pos)
{
    /* obviously, an empty list does not have any nodes
     * that could be extracted, so return NULL
     */
    if (list->size == 0)
        return NULL;

    /* shortcuts */
    if (pos == 0)
        /* head is the first element, at pos=0 */
        return list->head;
    else if (pos == (list->size-1))
        /* tail is the last element, at pos=size-1 */
        return list->tail;
    else if (pos >= list->size)
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
