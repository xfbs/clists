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
    slist_t *list = slist_new();
    assertNotEquals(list, NULL);
    assertEquals(list->size, 0);
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
        (slist_node_t*)0xDEADBEEF, 
        (slist_node_t*)0xCAFEBABE, 
        (size_t)50
    };
    assertEquals(slist_init(&list), 0);
    assertEquals(list.size, 0);
    assertEquals(list.head, NULL);
    assertEquals(list.tail, NULL);
}

TEST(purgingEmpty)
{
    /* test purging an empty list */
    slist_t *list = slist_new();
    assertNotEquals(list, NULL);

    /* make sure list is empty */
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);
    assertEquals(list->size, 0);

    /* purge list and check return and
     * state of list */
    ret = slist_purge(list);
    assertEquals(ret, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);
    assertEquals(list->size, 0);
}

TEST(purgingSingle)
{
    /* test purging a list with a single
     * node */
    slist_t *list = slist_new();
    assertNotEquals(list, NULL);

    /* add single node */
    ret = slist_append(list, (void*)0xBADC0DE5);
    assertEquals(ret, 0);

    /* make sure list contains single node */
    assertNotEquals(list->head, NULL);
    assertEquals(list->tail, list->head);
    assertEquals(list->size, 1);

    /* purge list and check return and
     * state of list */
    ret = slist_purge(list);
    assertEquals(ret, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);
    assertEquals(list->size, 0);
}

TEST(purgingMultiple)
{
    /* test purging if there are multiple
     * nodes in the list
     */
    slist_t *list = slist_new();
    assertNotEquals(list, NULL);

    /* add nodes */
    ret = slist_append(list, (void*)0xDECAFBAD);
    assertEquals(ret, 0);
    ret = slist_append(list, (void*)0xCAFEBABE);
    assertEquals(ret, 0);
    ret = slist_append(list, (void*)0xC0DEC0DE);
    assertEquals(ret, 0);

    /* make sure nodes are in place */
    assertEquals(list->size, 3);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->head->next, NULL);
    assertNotEquals(list->head->next->next, NULL);
    assertEquals(list->head->next->next->next, NULL);

    /* free list and check return value
     * and list state */
    ret = slist_purge(list);
    assertEquals(ret, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);
    assertEquals(list->size, 0);
}

TEST(freeingEmpty)
{
    /* test freeing by checking return
     * values of the free function
     */
    slist_t *list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(freeingSingle)
{
    /* test freeing if list contains a
     * a single node
     */
    slist_t *list = slist_new();
    assertNotEquals(list, NULL);

    /* add a single node */
    ret = slist_append(list, (void*)0xDECAFBAD);
    assertEquals(ret, 0);

    /* make sure node is in place */
    assertEquals(list->size, 1);
    assertEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(freeingMultiple)
{
    /* test freeing if there are multiple
     * nodes in the list
     */
    slist_t *list = slist_new();
    assertNotEquals(list, NULL);

    /* add nodes */
    ret = slist_append(list, (void*)0xDECAFBAD);
    assertEquals(ret, 0);
    ret = slist_append(list, (void*)0xCAFEBABE);
    assertEquals(ret, 0);
    ret = slist_append(list, (void*)0xC0DEC0DE);
    assertEquals(ret, 0);

    /* make sure nodes are in place */
    assertEquals(list->size, 3);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->head->next, NULL);
    assertNotEquals(list->head->next->next, NULL);
    assertEquals(list->head->next->next->next, NULL);

    /* free list and check return value */
    ret = slist_free(list);
    assertEquals(ret, 0);
}
