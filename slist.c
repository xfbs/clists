#include "slist.h"


slist *slist_alloc()
{
    // allocate memory for a list
    slist *list = malloc(sizeof(slist));
    // zeroize memory
    memset(list, 0, sizeof(slist));

    return list;
}


void slist_free(slist *list, int free_data)
{
    slist_purge(list, free_data);

    // free list itself
    free(list);
}


slist_node *slist_get_node(slist *list, size_t pos)
{
    // if the list is empty, return NULL
    assert(list->size);
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


slist_node *slist_node_alloc()
{
    slist_node *node = malloc(sizeof(slist_node));
    memset(node, 0, sizeof(node));
    return node;
}


slist_node *slist_node_copy(slist_node *old)
{
    // can't copy nonexistant node
    if(!old)
        return 0;

    // allocate new slist_node
    slist_node *new = malloc(sizeof(slist_node));
    // copy memory from old node over
    memcpy(new, old, sizeof(slist_node));
}


slist *slist_copy(slist *list)
{
    // allocate a new slist
    slist *copy = slist_alloc();

    // head node or list
    slist_node *list_node = list->head;
    // copy head node of list
    slist_node *copy_node = slist_node_copy(list_node);

    // set head node
    copy->head = copy_node;

    // loop through nodes
    while(list_node && list_node->next) {
        // copy nodes
        copy_node->next = slist_node_copy(list_node->next);

        copy_node = copy_node->next;
        list_node = list_node->next;
    }

    // set copy's tail node
    copy->tail = copy_node;
    // set copy's size
    copy->size = list->size;

    return copy;
}


void slist_purge(slist *list, int free_data)
{
    // if list is NULL, don't do anything
    if(!list)
        return;

    // current node
    slist_node *cur = list->head;
    // pointer to next node
    slist_node *next;

    // loop though list's nodes
    while (cur)
    {
        // free data if asked to
        if(free_data)
            free(cur->data);

        // store a pointer to the next node
        next = cur->next;
        // free current node
        free(cur);
        // go to pointer to next node
        cur = next;
    }

    // zeroise list
    memset(list, 0, sizeof(slist));
}



void slist_append(slist *list, void *data)
{
    // get last node
    slist_node *node = list->tail;

    // append node
    if (node)
    {
        node->next = slist_node_alloc();
        node = node->next;
    } else {
        node = slist_node_alloc();
        list->head = node;
    }

    // set this node as new tail
    list->tail = node;

    // update list size
    list->size++;

    // update data
    node->data = data;
}


void slist_push(slist *list, void *data)
{
    // allocate node
    slist_node *node = slist_node_alloc();

    // set data
    node->data = data;

    if (list->size) {
        // make node point to current first node
        node->next = list->head;
    } else {
        list->head = node;
        list->tail = node;
    }

    // make node first node
    list->head = node;

    // update size
    list->size++;
}


void slist_insert(slist *list, void *data, size_t pos)
{
    // handle special cases
    if (pos == 0) {
        slist_push(list, data);
    } else if(pos >= list->size) {
        slist_append(list, data);
    } else {
        // get previous node
        slist_node *prev = slist_get_node(list, pos-1);
        // get next node
        slist_node *next = prev->next;
        
        assert(prev && next);

        slist_node *node = slist_node_alloc();
        prev->next = node; // make prev node point to it
        node->next = next; // make it point to next node
        node->data = data; // set data
        list->size++;      // increment list size
    }
}


void slist_set(slist *list, void *data, size_t pos)
{
    // get pointer to the node that needs to be changed
    slist_node *node = slist_get_node(list, pos);

    // sert data if node exists
    if (node) {
        node->data = data;
    }
}


void *slist_first(slist *list)
{
    if (list->head) {
        return list->head->data;
    } else {
        return 0;
    }
}


void *slist_last(slist *list)
{
    if (list->tail) {
        return list->tail->data;
    } else {
        return 0;
    }
}


void *slist_get(slist *list, size_t pos)
{
    // get the node
    slist_node *node = slist_get_node(list, pos);

    // if node exists, return data, else NULL
    return((node) ? node->data : NULL);
}


void *slist_pop(slist *list)
{
    // get pointer to head of list
    slist_node *head = list->head;

    if (!head)
        return NULL;

    // get pointer to data
    void *data = head->data;

    // remove references to head
    if (head->next) {
        list->head = head->next;
    } else {
        list->head = 0;
        list->tail = 0;
    }

    // decrement list's size
    list->size--;

    // free the node
    free(head);

    return data;
}


void *slist_remove(slist *list, size_t pos, int free_data)
{
    void *data;

    if (pos == 0) {
        // remove first node & save the data pointer
        data = slist_pop(list);
    } else if(pos >= list->size) {
        return 0;
    } else {
        // get previous node
        slist_node *prev = slist_get_node(list, pos-1);

        // check if pos is a valid position
        if (!prev || !prev->next) {
            return 0;
        }

        // get node the be removed
        slist_node *node = prev->next;

        if (node == list->tail) {
            list->tail = prev;
            prev->next = 0;
        } else {
            prev->next = node->next;
        }

        // save the data for later
        data = node->data;

        // free the node
        free(node);

        // decrement the list's size
        list->size--;
    }

    // free the data if asked to
    if(free_data)
        free(data);

    return data;
}


size_t slist_size(slist *list)
{
    return list->size;
}


slist_iter *slist_iter_alloc(slist *list)
{
    // allocate iterator
    slist_iter *iter = malloc(sizeof(slist_iter));
    memset(iter, 0, sizeof(slist_iter));

    // set list
    iter->list = list;
    // set current position
    iter->cur = 0;
    iter->pos = 0;

    return iter;
}


void slist_iter_free(slist_iter *iter)
{
    free(iter);
}


void slist_iter_goto(slist_iter *iter, size_t pos)
{
    // get the node that is requested
    slist_node *node = slist_get_node(iter->list, pos);
    
    // if it doesn't exist, get the last node
    if(!node) {
        pos = iter->list->size-1;
        node = slist_get_node(iter->list, pos);
    }

    iter->pos = pos;
    iter->cur = node;
}

void *slist_iter_next(slist_iter *iter)
{
    if(iter->cur) {
        // go to next node
        iter->cur = iter->cur->next;
        iter->pos = (iter->cur) ? iter->pos+1 : 0;
    } else {
        // go to first node
        iter->cur = iter->list->head;
        iter->pos = 0;
    }

    return iter->cur;
}

void *slist_iter_get(slist_iter *iter)
{
    return((iter->cur) ? iter->cur->data : (void*)0);
}
