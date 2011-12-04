#include "slist.h"

slist *slist_alloc()
{
    // allocate memory for a list
    slist *list = malloc(sizeof(slist));
    // zeroize memory
    memset(list, 0, sizeof(list));

    return list;
}

slist *slist_copy(slist *old)
{
    // TODO
}

slist_node *slist_get_node(slist *list, size_t pos)
{
    // if the list is empty, return NULL
    if (!list->size)
        return NULL;

    // if pos is zero, return list's head
    if (!pos)
        return list->head;

    // if pos is the last list element, return the list's tail
    if (pos == (list->size-1))
        return list->tail;

    // if pos is larger than the amount of elements in list, return NULL
    if (pos >= list->size)
        return NULL;

    // loop until we hit the requested element
    slist_node *node = list->head;
    while (node && pos)
    {
        pos--;
        node = node->next;
    }

    return node;
}
