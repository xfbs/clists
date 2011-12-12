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
    dlist *list = dlist_alloc();
    dlist_debug(list);
    dlist_append(list, (void*)0xDEADBEEF);
    dlist_debug(list);
    dlist_free(list, 0);
}
