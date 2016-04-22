/* tests for slist creation and destruction
 * functions
 */

#include "cu/cu.h"
#include "clists/slist.h"
int ret;

TEST(allocation)
{
    /* make sure new() allocates memory and
     * initializes it properly */
    slist_t *list = slist_new(sizeof(void*));
    assertNotEquals(list, NULL);
    assertEquals(list->size, sizeof(void*));
    assertEquals(list->length, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);
    free(list);
}

TEST(initialization)
{
    /* test initialization by filling it up
     * with random garbage and checking if
     * it is cleared
     */
    slist_t list = {
        .head = (slist_node_t*)0xDEADBEEF, 
        .tail = (slist_node_t*)0xCAFEBABE, 
        .length = (size_t)50,
        .size = (size_t)1312
    };
    assertEquals(slist_init(&list, sizeof(void*)), 0);
    assertEquals(list.size, sizeof(void*));
    assertEquals(list.length, 0);
    assertEquals(list.head, NULL);
    assertEquals(list.tail, NULL);
}

TEST(purgingEmpty)
{
    slist_t *list = slist_new(sizeof(void*));
    assertNotEquals(list, NULL);

    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);
    assertEquals(list->size, sizeof(void*));
    assertEquals(list->length, 0);

    ret = slist_purge(list);
    assertEquals(ret, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);
    assertEquals(list->length, 0);
    assertEquals(list->size, sizeof(void*))

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(purgingSingle)
{
    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    int data = 0xBADC0DE5;
    ret = slist_append(list, &data);
    assertEquals(ret, 0);

    assertNotEquals(list->head, NULL);
    assertEquals(list->tail, list->head);
    assertEquals(list->length, 1);
    assertEquals(list->size, sizeof(int));

    ret = slist_purge(list);
    assertEquals(ret, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);
    assertEquals(list->size, sizeof(int));
    assertEquals(list->length, 0);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(purgingMultiple)
{
    // test purging if there are multiple
    // entries (nodes) in the list
    // we can't check if the nodes are
    // free()'d properly, this is something
    // that should be tested with valgrind.

    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    // add nodes
    int data[] = {0xDECAFBAD, 0xCAFEBABE, 0xC0DEC0DE, 0};
    for(int i = 0; data[i] != 0; i++) {
        ret = slist_append(list, &data[i]);
        assertEquals(ret, 0);
    }

    // make sure the nodes are all set properly
    assertEquals(list->size, sizeof(int));
    assertEquals(list->length, 3);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->head->next, NULL);
    assertNotEquals(list->head->next->next, NULL);
    assertEquals(list->head->next->next->next, NULL);

    // try the purge and see if it works
    ret = slist_purge(list);
    assertEquals(ret, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);
    assertEquals(list->size, sizeof(int));
    assertEquals(list->length, 0);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(freeingEmpty)
{
    // test the free function by checking
    // it's return value. we can't check
    // anything else because by the time
    // slist_free() returns, the slist has
    // been free()'d and it's contents
    // may have been overwritten.

    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(freeingSingle)
{
    // test slist_free on a list that
    // contains a single node.

    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    // add single node
    int data = 0xDECAFBAD;
    ret = slist_append(list, &data);
    assertEquals(ret, 0);

    // verify the node exists
    assertEquals(list->length, 1);
    assertEquals(list->size, sizeof(int));
    assertEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);

    // run free and check return value
    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(freeingMultiple)
{
    // test slist_free() if there are
    // multiple items in the list

    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    // add nodes to the list
    int data[] = {0xDECAFBAD, 0xCAFEBABE, 0xC0DEC0DE, 0};
    for(int i = 0; data[i] != 0; i++) {
        ret = slist_append(list, &data[i]);
        assertEquals(ret, 0);
    }

    // make sure the nodes are in place
    assertEquals(list->size, sizeof(int));
    assertEquals(list->length, 3);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->head->next, NULL);
    assertNotEquals(list->head->next->next, NULL);
    assertEquals(list->head->next->next->next, NULL);

    // free the list and check the return value
    ret = slist_free(list);
    assertEquals(ret, 0);
}
