#include <string.h>
#include <stdlib.h>

/* slist_node struct
 * a single linked list node: contains a pointer
 * to the next list element as well as a pointer
 * to the data of that list element.
 */
struct slist_node
{
    struct slist_node *next;
    void *data;
}

/* slist_node struct
 * data type of a singly linked list: contains 
 * pointer to the head of the list for pushing 
 * items to the list, to the end of the list for
 * efficient appending and a variable to keep 
 * track of the size of the list to avoid having
 * to traverse all elements to get the size.
 */
struct slist
{
    struct slist_node *head;
    struct slist_node *tail;
    size_t size;
}

typedef struct slist_node slist_node;
typedef struct slist slist;


/* slist_alloc()
 * allocates a new singly linked list with malloc
 * and zeroizes the allocated memory (!)
 */
slist *slist_alloc();


/* slist_copy(other)
 * allocates a new singly linked list and copies 
 * all elements from other into it.
 */
slist *slist_copy(slist *old);


/* slist_get_node(list, pos)
 * returns pointer to node at position pos of the
 * list. if there is no node at pos, returns NULL
 */
slist_node *slist_get_node(slist *list, size_t pos);


