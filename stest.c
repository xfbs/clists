#include "slist.h"

void slist_debug(slist *list)
{
    // make sure list exists
    assert(list);

    // print debug info about list
    printf("list @%p, head %p, tail %p, size %u\n", list, list->head, list->tail, (unsigned int)list->size);

    slist_node *node = list->head;
    size_t pos = -1;

    while (node) {
        pos++;

        // print debug info about node
        printf(" node @%p, data %p, next %p, pos %u\n", node, node->data, node->next, (unsigned int)pos);

        // if this is the last node, check if it's list->tail
        if(!node->next)
            assert(node == list->tail);

        // go to next node
        node = node->next;
    }

    // check if list size is right
    assert(list->size == (++pos));

    printf("\n");
}

int main(void)
{
    // couldn't get it to work as an array... this'll do
    void *data1 = (void*)0xCAFEBABE1;
    void *data2 = (void*)0xDECAFBAD2;
    void *data3 = (void*)0xDEADBEEF3;
    void *data4 = (void*)0xBAADF00D4;
    void *data5 = (void*)0xC0DEBABE5;
    void *data6 = (void*)0xBADCAB1E6;

    printf("-> allocate list\n");
    slist *list = slist_alloc();
    slist_debug(list);

    printf("-> push (add to top)\n");
    slist_push(list, data2);
    slist_debug(list);

    printf("-> append (add to back)\n");
    slist_append(list, data4);
    slist_debug(list);

    printf("-> insert (at position 0)\n");
    slist_insert(list, data1, 0);
    slist_debug(list);

    printf("-> insert (at position 2)\n");
    slist_insert(list, data3, 2);
    slist_debug(list);

    printf("-> check size (should be 4)\n");
    assert(slist_size(list) == 4);

    printf("-> test if first node it correct\n");
    assert(slist_first(list) == data1);

    printf("-> test if last node is correct\n");
    assert(slist_last(list) == data4);

    printf("-> copy list\n");
    slist *copy = slist_copy(list);
    slist_debug(copy);

    printf("-> free lists\n");
    slist_free(list, 0);
    slist_free(copy, 0);

    printf("-> copy empty list\n");
    list = slist_alloc();
    copy = slist_copy(list);
    slist_debug(copy);

    printf("-> insert some data\n");
    slist_insert(copy, data5, 1);
    slist_debug(copy);

    printf("-> remove nonexistant node\n");
    assert(!slist_remove(copy, 2, 0));
    assert(slist_size(copy));
    slist_debug(copy);

    printf("-> inserting another node\n");
    slist_insert(copy, data1, 0);
    slist_debug(copy);

    printf("-> remove existing node\n");
    assert(slist_remove(copy, 0, 0));
    assert(slist_size(copy)==1);
    slist_debug(copy);

    printf("-> popping nonexistant node\n");
    assert(!slist_pop(list));
    
    printf("-> popping existant node\n");
    assert(slist_pop(copy));
    slist_debug(copy);

    printf("-> filling list with data\n");
    slist_append(list, data1);
    slist_append(list, data2);
    slist_append(list, data3);
    slist_append(list, data4);
    slist_append(list, data5);
    slist_append(list, data6);
    assert(slist_size(list) == 6);
    slist_debug(list);
    
    printf("-> checking data\n");
    assert(slist_get(list, 0) == data1);
    assert(slist_get(list, 1) == data2);
    assert(slist_get(list, 2) == data3);
    assert(slist_get(list, 3) == data4);
    assert(slist_get(list, 4) == data5);
    assert(slist_get(list, 5) == data6);
    assert(slist_first(list) == data1);
    assert(slist_last(list)  == data6);

    printf("-> setting nonexistant nodes\n");
    slist_set(list, data1, 6);
    slist_set(list, data1, 7);
    slist_set(list, data1, -1);
    slist_debug(list);

    printf("-> setting valid nodes\n");
    slist_set(list, data6, 0);
    slist_set(list, data5, 1);
    slist_set(list, data4, 2);
    slist_set(list, data1, 5);
    assert(slist_get(list, 0) == data6);
    assert(slist_get(list, 2) == data4);
    assert(slist_get(list, 3) == data4);
    assert(slist_get(list, 5) == data1);
    slist_debug(list);
    
    printf("-> making iterator\n");
    slist_iter *iter = slist_iter_alloc(list);
    assert(iter);
    printf("-> testing iterator\n");
    assert(slist_iter_next(iter));
    assert(slist_iter_get(iter) == data6);
    assert(slist_iter_next(iter));
    assert(slist_iter_get(iter) == data5);
    assert(slist_iter_next(iter));
    assert(slist_iter_get(iter) == data4);

    printf("-> testing iterator goto\n");
    slist_iter_goto(iter, 4);
    assert(slist_iter_get(iter) == data5);
    assert(slist_iter_next(iter));
    assert(slist_iter_get(iter) == data1);
    assert(!slist_iter_next(iter));
    assert(iter->pos == 0);
    assert(iter->cur == 0);
    printf("-> freeing iterator\n");
    free(iter);

    printf("-> purging list\n");
    slist_purge(list, 0);
    slist_debug(list);
    assert(slist_size(list) == 0);
    assert(slist_first(list) == 0);
    assert(slist_last(list) == 0);

    printf("-> freeing lists\n");
    slist_free(list, 0);
    slist_free(copy, 0);

    printf("-> DONE\n");

    return 0;
}
