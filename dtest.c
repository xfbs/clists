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

    printf("-> allocating new dlist\n");
    dlist *list = dlist_alloc();
    dlist_debug(list);

    printf("-> copying empty list\n");
    dlist *copy = dlist_copy(list);
    assert(dlist_size(copy) == dlist_size(list) == 0);
    dlist_debug(copy);

    printf("-> freeing empty copy\n");
    dlist_free(list, 0);

    printf("-> appending data to list\n");
    dlist_append(list, data1);
    dlist_debug(list);

    printf("-> copying list\n");
    copy = dlist_copy(list);
    dlist_debug(copy);

    printf("-> joining lists\n");
    dlist_merge(list, copy);
    dlist_debug(list);

    printf("-> adding to list\n");
    dlist_append(copy, data2);
    dlist_push(copy, data1);
    assert(dlist_get(copy, 0) == data1);
    assert(dlist_get(copy, 1) == data2);
    dlist_debug(copy);

    printf("-> popping from list\n");
    assert(dlist_pop(copy) == data1);
    dlist_debug(copy);

    printf("-> freeing lists\n");
    dlist_free(list, 0);
    dlist_free(copy, 0);
}
