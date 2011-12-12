#include "dlist.h"


dlist *dlist_alloc()
{
    // allocate new list
    dlist *list = malloc(sizeof(dlist));

    // zeroize list
    memset(list, 0, sizeof(dlist));

    return list;
}


dlist *dlist_copy(dlist *list)
{
    // TODO!!!
}


dlist_node *dlist_node_alloc()
{
    // allocate memory for node
    dlist_node *node = malloc(sizeof(dlist_node));

    // zeroize node
    memset(node, 0, sizeof(dlist_node));

    return node;
}


dlist_node *dlist_node_copy(dlist_node *node)
{
    // allocate memory for the copy
    dlist_node *copy = malloc(sizeof(dlist_node));

    // copy contents over
    memcpy(copy, node, sizeof(dlist_node));

    return copy;
}


dlist_node *dlist_node_get(dlist *list, size_t pos)
{
    // return NULL if the list is empty
    if (!list->size)
        return NULL;

    // return null if pos doesn't exist in list
    if (pos >= list->size)
        return NULL;

    // deliberately uninitialized
    dlist_node *node;

    // check where the node is
    if (pos < (list->size/2)) {
        // pos is before the middle if the list,
        // thus we loop from the beginning
        node = list->head;

        while (node && pos) {
            // decrement pos
            pos--;

            // go to next node
            node = node->next;
        }
    } else {
        // pos is after the middle of the list,
        // thus we loop from the end of the list

        node = list->tail;
        pos = (list->size-pos)-1;

        while (node && pos) {
            // decrement pos
            pos--;

            // go to previous node
            node = node->prev;
        }
    }

    return node;
}


void dlist_free(dlist *list, int free_data)
{
    // get pointer to head of list
    dlist_node *node = list->head;

    while(node)
    {
        // save data pointer for freeing later
        void *data = node->data;

        // free node
        free(node);

        // free data if asked to
        if(free_data)
            free(data);

        // traverse to next node
        node = node->next;
    }

    // free dlist
    free(list);
}


void dlist_append(dlist *list, void *data)
{
    // the ndoe that needs to be appended
    dlist_node *node = dlist_node_alloc();

    // set data
    node->data = data;

    // check if list is empty
    if (list->size) {
        // append after current tail of list
        // set the previous node (current tail)
        node->prev = list->tail;

        // set current tail's next ndoe (this one)
        list->tail->next = node;

        // set node as new tail
        list->tail = node;
    } else {
        // set node as first item of list
        list->head = node;

        // set node as last item of list
        list->tail = node;
    }

    // increae size by one
    list->size++;
}


void dlist_push(dlist *list, void *data)
{
    // node that needs to be pushed
    dlist_node *node = dlist_node_alloc();

    // set data
    node->data = data;

    // check if list is empty
    if (list->size) {
        // set node's next to the current head of the list
        node->next = list->head;

        // set current head's prev to this node
        list->head->prev = node;

        // set this node as head
        list->head = node;
    } else {
        // set this node as the only list member
        list->head = node;
        list->tail = node;
    }

    // increase list size by one
    list->size++;
}



