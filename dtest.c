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


void *data1 = (void*)0xDEADBEEF1;
void *data2 = (void*)0xCAFEBABE2;
void *data3 = (void*)0x123ABCDE3;
void *data4 = (void*)0xDECAFBAD4;
void *data5 = (void*)0xCBABCDEF5;


void dlist_debug(dlist *list)
{
    // make sure list isn't NULL
    assert(list);

    // print list header
    printf("dlist %p, head %p, tail %p, size %u\n", list, list->head, list->tail, (unsigned int)list->size);

    // node before current one
    dlist_node *befo = 0;
    // current node
    dlist_node *node = list->head;
    // amount of nodes traversed
    unsigned int traversed = 0;

    // while node isn't NULL
    while (node) {
        // print node info
        printf(" node %p, prev %p, next %p, data %p, pos %u\n", node, node->prev, node->next, node->data, traversed++);

        // when this is the last node, check if is equals list->head
        if (!node->next)
            assert(node == list->tail);

        // check if the ndoe before is set as node->prev
        assert(befo == node->prev);

        // traverse to next node
        befo = node;
        node = node->next;
    }

    printf("\n");

    // check if we traversed the right amount of nodes
    assert(traversed == list->size);
}


dlist *dtest_new()
{
    // allocate new list
    dlist *list = dlist_alloc();

    // fill list with data
    dlist_append(list, data1);
    dlist_append(list, data2);
    dlist_append(list, data3);
    dlist_append(list, data4);
    dlist_append(list, data5);

    return list;
}


int main(void)
{
    dlist *list;
    dlist *copy;

    printf("-> dtest_new()\n");
    list = dtest_new();
    dlist_debug(list);
    dlist_free(list, false);


    printf("-> dlist_copy(empty)\n");
    list = dlist_alloc();
    dlist_debug(list);
    copy = dlist_copy(list);
    dlist_debug(copy);
    assert(copy->size == 0);
    assert(copy->head == NULL);
    assert(copy->tail == NULL);
    dlist_free(list, false);
    dlist_free(copy, false);


    printf("-> dlist_copy(full)\n");
    list = dtest_new();
    copy = dlist_copy(list);
    dlist_debug(copy);
    assert(list->size == copy->size);
    assert(list->head->data == copy->head->data);
    assert(list->tail->data == copy->tail->data);
    dlist_free(list, false);
    dlist_free(copy, false);


    printf("-> dlist_compare(empty, empty)\n");
    list = dlist_alloc();
    copy = dlist_alloc();
    assert(dlist_compare(list, copy));
    dlist_free(list, false);
    dlist_free(copy, false);


    printf("-> dlist_compare(full, full)\n");
    list = dtest_new();
    copy = dtest_new();
    assert(dlist_compare(list, copy));
    dlist_free(list, false);
    dlist_free(copy, false);


    printf("-> dlist_compare(full, full) when full != full\n");
    list = dtest_new();
    copy = dtest_new();
    copy->tail->data = data3;
    assert(dlist_compare(list, copy) == false);
    dlist_free(list, false);
    dlist_free(copy, false);


    printf("-> dlist_compare(full, empty)\n");
    list = dtest_new();
    copy = dlist_alloc();
    assert(dlist_compare(list, copy) == false);
    dlist_free(list, false);
    dlist_free(copy, false);


    printf("-> dlist_first(empty)\n");
    list = dlist_alloc();
    assert(dlist_first(list) == NULL);
    dlist_free(list, false);


    printf("-> dlist_first(full)\n");
    list = dtest_new();
    assert(dlist_first(list) == data1);
    dlist_free(list, false);


    printf("-> dlist_last(empty)\n");
    list = dlist_alloc();
    assert(dlist_last(list) == NULL);
    dlist_free(list, false);


    printf("-> dlist_last(full)\n");
    list = dtest_new();
    assert(dlist_last(list) == data5);
    dlist_free(list, false);


    printf("-> dlist_append(empty, data1)\n");
    list = dlist_alloc();
    dlist_append(list, data1);
    dlist_debug(list);
    assert(list->size == 1);
    assert(list->head == list->tail);
    assert(list->head->data == data1);
    dlist_free(list, false);


    printf("-> dlist_append(full, data1)\n");
    list = dtest_new();
    dlist_append(list, data1);
    dlist_debug(list);
    assert(list->size == 6);
    assert(list->head->data == data1);
    dlist_free(list, false);


    printf("-> dlist_insert(empty, data1, 0)\n");
    list = dlist_alloc();
    dlist_insert(list, data1, 0);
    dlist_debug(list);
    assert(list->size == 1);
    assert(list->head == list->tail);
    assert(list->head->data == data1);
    dlist_free(list, false);


    printf("-> dlist_insert(empty, data1, 1)\n");
    list = dlist_alloc();
    dlist_insert(list, data1, 1);
    dlist_debug(list);
    assert(list->size == 1);
    assert(list->head == list->tail);
    assert(list->head->data == data1);
    dlist_free(list, false);


    printf("-> dlist_insert(full, data5, 0)\n");
    list = dtest_new();
    dlist_insert(list, data5, 0);
    dlist_debug(list);
    assert(list->size == 6);
    assert(list->head->data == data5);
    dlist_free(list, false);


    printf("-> dlist_insert(full, data5, 2)\n");
    list = dtest_new();
    dlist_insert(list, data5, 2);
    dlist_debug(list);
    assert(list->size == 6);
    assert(list->head->next->next->data == data5);
    dlist_free(list, false);


    printf("-> dlist_insert(full, data1, 6)\n");
    list = dtest_new();
    dlist_insert(list, data1, 6);
    dlist_debug(list);
    assert(list->size == 6);
    assert(list->tail->data == data1);
    dlist_free(list, false);


    printf("-> dlist_set(empty, data1, 0)\n");
    list = dlist_alloc();
    dlist_set(list, data1, 0);
    dlist_debug(list);
    assert(list->size == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    dlist_free(list, false);


    printf("-> dlist_set(full, data1, 2)\n");
    list = dtest_new();
    dlist_set(list, data1, 2);
    dlist_debug(list);
    assert(list->size == 5);
    assert(list->head->next->next->data == data1);
    dlist_free(list, false);


    printf("-> dlist_merge(full, full)\n");
    list = dtest_new();
    copy = dtest_new();
    dlist_merge(list, copy);
    dlist_debug(list);
    assert(list->size == 10);
    assert(list->head->data == data1);
    assert(list->tail->data == data5);
    dlist_free(list, false);
    dlist_free(copy, false);


    printf("-> dlist_merge(empty, empty)\n");
    list = dlist_alloc();
    copy = dlist_alloc();
    dlist_merge(list, copy);
    dlist_debug(list);
    assert(list->size == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    dlist_free(list, false);
    dlist_free(copy, false);


    printf("-> dlist_merge(empty, full)\n");
    list = dlist_alloc();
    copy = dtest_new();
    dlist_merge(list, copy);
    dlist_debug(list);
    assert(list->size == 5);
    assert(list->head->data == data1);
    assert(list->tail->data == data5);
    dlist_free(list, false);
    dlist_free(copy, false);


    printf("-> dlist_merge(full, empty)\n");
    list = dtest_new();
    copy = dlist_alloc();
    dlist_merge(list, copy);
    dlist_debug(list);
    assert(list->size == 5);
    assert(list->head->data == data1);
    assert(list->tail->data == data5);
    dlist_free(list, false);
    dlist_free(copy, false);


    printf("-> dlist_get(empty, n)\n");
    list = dlist_alloc();
    assert(dlist_get(list, 0) == NULL);
    assert(dlist_get(list, 1) == NULL);
    assert(dlist_get(list, 2) == NULL);
    dlist_free(list, false);


    printf("-> dlist_get(full, valid_pos)\n");
    list = dtest_new();
    assert(dlist_get(list, 0) == data1);
    assert(dlist_get(list, 1) == data2);
    assert(dlist_get(list, 2) == data3);
    assert(dlist_get(list, 3) == data4);
    assert(dlist_get(list, 4) == data5);
    dlist_free(list, false);


    printf("-> dlist_get(full, invalid_pos)\n");
    list = dtest_new();
    assert(dlist_get(list, 5) == NULL);
    assert(dlist_get(list, 6) == NULL);
    dlist_free(list, false);


    printf("-> dlist_pop(empty)\n");
    list = dlist_alloc();
    assert(dlist_pop(list) == NULL);
    assert(list->size == 0);
    dlist_free(list, false);


    printf("-> dlist_pop(full)\n");
    list = dtest_new();
    assert(dlist_pop(list) == data1);
    dlist_debug(list);
    assert(list->size == 4);
    assert(dlist_pop(list) == data2);
    dlist_debug(list);
    assert(list->size == 3);
    dlist_free(list, false);


    printf("-> dlist_pop(full) where full->size == 1\n");
    list = dlist_alloc();
    dlist_append(list, data1);
    assert(list->size == 1);
    assert(dlist_pop(list) == data1);
    dlist_debug(list);
    assert(list->size == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    dlist_free(list, false);


    printf("-> dlist_push(empty, data)\n");
    list = dlist_alloc();
    dlist_push(list, data1);
    dlist_debug(list);
    assert(list->size == 1);
    assert(list->head == list->tail);
    assert(list->head->data == data1);
    dlist_free(list, false);


    printf("-> dlist_push(full, data)\n");
    list = dtest_new();
    dlist_push(list, data5);
    dlist_debug(list);
    assert(list->size == 6);
    assert(list->head->data == data5);
    dlist_free(list, false);


    printf("-> dlist_size(empty)\n");
    list = dlist_alloc();
    assert(dlist_size(list) == 0);
    dlist_free(list, false);


    printf("-> dlist_size(full)\n");
    list = dtest_new();
    assert(dlist_size(list) == 5);
    dlist_free(list, false);


    printf("-> dlist_remove(empty, invalid_pos, false)\n");
    list = dlist_alloc();
    assert(dlist_remove(list, 0, false) == NULL);
    assert(dlist_remove(list, 1, false) == NULL);
    dlist_debug(list);
    dlist_free(list, false);


    printf("-> dlist_remove(full, valid_pos, false)\n");
    list = dtest_new();
    assert(dlist_remove(list, 4, false) == data5);
    dlist_debug(list);
    assert(list->size == 4);
    assert(dlist_last(list) == data4);
    assert(dlist_remove(list, 2, false) == data3);
    dlist_debug(list);
    assert(list->size == 3);
    assert(dlist_get(list, 2) == data4);
    assert(dlist_remove(list, 0, false) == data1);
    dlist_debug(list);
    assert(list->size == 2);
    assert(dlist_first(list) == data2);
    dlist_free(list, false);


    printf("-> dlist_remove(full, invalid_pos, false)\n");
    list = dtest_new();
    copy = dtest_new();
    assert(dlist_remove(list, 5, false) == NULL);
    assert(dlist_remove(list, 6, false) == NULL);
    assert(dlist_compare(list, copy));
    dlist_free(list, false);
    dlist_free(copy, false);


    printf("-> ALL TESTS PASSED (B:%d)\n", log_alloc_balance(0));
}
