/*  File: dtest.c
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


#include "dlist.h"

void dlist_debug(dlist *list)
{
    assert(list);

    printf("dlist %p, head %p, tail %p, size %u\n", list, list->head, list->tail, (unsigned int)list->size);

    dlist_node *node = list->head;
    unsigned int traversed = 0;

    while (node) {
        printf(" node %p, prev %p, next %p, data %p, pos %u\n", node, node->prev, node->next, node->data, traversed++);

        if (!node->next)
            assert(node == list->tail);

        node = node->next;
    }

    printf("\n");

    assert(traversed == list->size);
}


int main(void)
{
    void *data1 = (void*)0xDEADBEEF1;
    void *data2 = (void*)0xCAFEBABE2;
    void *data3 = (void*)0x123ABCDE3;

    printf("-> dlist_alloc (allocating new list)\n");
    dlist *list = dlist_alloc();
    dlist_debug(list);

    printf("-> dlist_copy (copying empty list)\n");
    dlist *copy = dlist_copy(list);
    assert(dlist_size(copy) == 0);
    assert(dlist_size(copy) == dlist_size(list));
    dlist_debug(copy);

    printf("-> dlist_compare (comparing empty lists)\n");
    assert(dlist_compare(list, copy));

    printf("-> dlist_first (first data of empty list)\n");
    assert(dlist_first(list) == NULL);

    printf("-> dlist_append (appending data1 to list)\n");
    dlist_append(list, data1);
    dlist_debug(list);

    printf("-> dlist_compare (comparing different lists)\n");
    assert(dlist_compare(list, copy) == false);

    printf("-> dlist_insert (inserting into copy at pos 1)\n");
    dlist_insert(copy, data2, 1);
    dlist_debug(copy);
    
    printf("-> dlist_compare (comparing inequal lists)\n");
    assert(dlist_compare(list, copy) == false);

    printf("-> dlist_free (freeing copied list)\n");
    dlist_free(copy, 0);

    printf("-> dlist_copy (copying full list)\n");
    copy = dlist_copy(list);
    dlist_debug(copy);

    printf("-> dlist_set (setting nonexistant position)\n");
    dlist_set(copy, data2, 3);
    dlist_debug(copy);

    printf("-> dlist_set (setting existing position)\n");
    dlist_set(copy, data2, 0);
    dlist_debug(copy);

    printf("-> dlist_merge (joining lists)\n");
    dlist_merge(list, copy);
    dlist_debug(list);

    printf("-> dlist_first (checking first element)\n");
    assert(dlist_first(list) == data1);

    printf("-> dlist_last (checking last element)\n");
    assert(dlist_last(list) == data2);

    printf("-> dlist_get (check if data is correct)\n");
    assert(dlist_get(list, 0) == data1);
    assert(dlist_get(list, 1) == data2);

    printf("-> dlist_pop (check if data is correct)\n");
    assert(dlist_pop(list) == data1);
    assert(dlist_size(list) == 1);
    assert(dlist_pop(list) == data2);
    assert(dlist_size(list) == 0);
    assert(dlist_pop(list) == NULL);
    assert(dlist_size(list) == 0);
    dlist_debug(list);

    printf("-> dlist_push (prepend data to list)\n");
    dlist_push(list, data2);
    dlist_push(list, data1);
    assert(dlist_get(list, 0) == data1);
    assert(dlist_get(list, 1) == data2);
    dlist_debug(list);

    printf("-> dlist_size (checking size of list)\n");
    assert(dlist_size(list) == 2);

    printf("-> dlist_insert (adding to list)\n");
    dlist_insert(copy, data2, 1);
    dlist_insert(copy, data1, 0);
    dlist_insert(copy, data3, 1);
    assert(dlist_get(copy, 0) == data1);
    assert(dlist_get(copy, 1) == data3);
    assert(dlist_get(copy, 2) == data2);
    dlist_debug(copy);

    printf("-> dlist_remove (removing from list)\n");
    assert(dlist_remove(copy, 1, false) == data3);

    printf("-> popping from list\n");
    assert(dlist_pop(copy) == data1);
    dlist_debug(copy);

    printf("-> freeing lists\n");
    dlist_free(list, 0);
    dlist_free(copy, 0);
}
