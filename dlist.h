#ifndef _DLIST_H
#define _DLIST_H
#include <string.h>
#include <stdlib.h>
#include "debug.h"


/* dlist_node struct
 * represents a node of the doubly linked list,
 * has pointers to the previous and next nodes
 */
struct dlist_node
{
    struct dlist_node *prev;
    struct dlist_node *next;
    void *data;
};


/* dlist struct
 * data type of doubly linked list, contains
 * pointer to first node as well as cached 
 * variables for the size of the list and the
 * last node
 */
struct dlist
{
    struct dlist_node *head;
    struct dlist_node *tail;
    size_t size;
};


typedef struct dlist dlist;
typedef struct dlist_node dlist_node;


/* dlist_alloc()
 * convenience function to allocate a new
 * dlist 'object' with malloc and zeroizes
 * it. 
 */
dlist *dlist_alloc();


/* dlist_copy(list)
 * copies a list and all data pointers
 */
dlist *dlist_copy(dlist *list);


/* dlist_node_alloc()
 * convenience function to allocate new 
 * node with malloc and zeroize it
 */
dlist_node *dlist_node_alloc();


/* dlist_copy_node(node)
 * allocates new node, copies the content
 * of node into it and returns it
 */
dlist_node *dlist_node_copy(dlist_node *node);


/* dlist_node_get(list, pos)
 * get the node at position pos of the list or
 * return NULL if it doesn't exist
 */
dlist_node *dlist_node_get(dlist *list, size_t pos);


/* dlist_free(list, free_data)
 * frees list's nodes, the list itself and
 * optionally the data the ndoes point to
 */
void dlist_free(dlist *list, int free_node);


/* dlist_append(list, data)
 * append data to the end of the list
 */
void dlist_append(dlist *list, void *data);


/* dlist_push(list, data)
 * add data as node to the top of the list
 */
void dlist_push(dlist *list, void *data);

#endif
