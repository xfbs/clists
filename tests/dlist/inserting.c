#include "cu/cu.h"
#include "clists/dlist.h"

static int ret;
static dlist_t *list;

TEST(insertEmpty)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_insert(list, 0, (void*)0x1234);
    assertEquals(ret, 0);

    assertEquals(list->head, list->tail);
    assertEquals(list->size, 1);
    assertNotEquals(list->head, NULL);
    assertEquals(list->head->data, (void*)0x1234);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(insertBeginning)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_insert(list, 0, (void*)0x1234);
    assertEquals(ret, 0);

    ret = dlist_insert(list, 0, (void*)0x4321);
    assertEquals(ret, 0);

    assertNotEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->size, 2);
    assertEquals(list->head->next, list->tail);
    assertEquals(list->tail->prev, list->head);
    assertEquals(list->head->data, (void*)0x4321);
    assertEquals(list->tail->data, (void*)0x1234);

    ret = dlist_insert(list, 0, (void*)0x2222);
    assertEquals(ret, 0);

    assertEquals(list->size, 3);
    assertNotEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertNotEquals(list->head->next, NULL);
    assertNotEquals(list->tail->prev, NULL);
    assertEquals(list->head->next, list->tail->prev);
    assertEquals(list->head->next->next, list->tail);
    assertEquals(list->tail->prev->prev, list->head);
    assertEquals(list->head->data, (void*)0x2222);
    assertEquals(list->tail->data, (void*)0x1234);
    assertEquals(list->head->next->data, (void*)0x4321);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(insertBack)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_insert(list, 0, (void*)0x1234);
    assertEquals(ret, 0);

    ret = dlist_insert(list, 1, (void*)0x2341);
    assertEquals(ret, 0);

    assertNotEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->size, 2);
    assertEquals(list->head->next, list->tail);
    assertEquals(list->tail->prev, list->head);
    assertEquals(list->head->data, (void*)0x1234);
    assertEquals(list->tail->data, (void*)0x2341);

    ret = dlist_insert(list, 2, (void*)0x3412);
    assertEquals(ret, 0);

    assertEquals(list->size, 3);
    assertNotEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertNotEquals(list->head->next, NULL);
    assertNotEquals(list->tail->prev, NULL);
    assertEquals(list->head->next, list->tail->prev);
    assertEquals(list->head->next->next, list->tail);
    assertEquals(list->tail->prev->prev, list->head);
    assertEquals(list->head->data, (void*)0x1234);
    assertEquals(list->head->next->data, (void*)0x2341);
    assertEquals(list->tail->data, (void*)0x3412);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(insertMiddle)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_insert(list, 0, (void*)0x1234);
    assertEquals(ret, 0);

    ret = dlist_insert(list, 1, (void*)0x4123);
    assertEquals(ret, 0);

    assertEquals(list->size, 2);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->head->data, (void*)0x1234);
    assertEquals(list->tail->data, (void*)0x4123);

    ret = dlist_insert(list, 1, (void*)0x2341);
    assertEquals(ret, 0);

    assertEquals(list->size, 3);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertNotEquals(list->head->next, NULL);
    assertNotEquals(list->tail->prev, NULL);
    assertEquals(list->head->next, list->tail->prev);
    assertEquals(list->head->next->next, list->tail);
    assertEquals(list->tail->prev->prev, list->head);
    assertEquals(list->head->data, (void*)0x1234);
    assertEquals(list->tail->data, (void*)0x4123);
    assertEquals(list->head->next->data, (void*)0x2341);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(insertInvalid)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_insert(list, 2, (void*)0x2341);
    assertNotEquals(ret, 0);
    assertEquals(list->size, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);

    ret = dlist_insert(list, 1, (void*)0x1234);
    assertNotEquals(ret, 0);
    assertEquals(list->size, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(insertAll)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    /* insert first */
    ret = dlist_insert(list, 0, (void*)0x1234);
    assertEquals(ret, 0);
    assertEquals(list->size, 1);
    assertEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertEquals(list->head->data, (void*)0x1234);

    /* insert to beginning */
    ret = dlist_insert(list, 0, (void*)0x2341);
    assertEquals(ret, 0);
    assertEquals(list->size, 2);
    assertNotEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->head->next, list->tail);
    assertEquals(list->tail->prev, list->head);
    assertEquals(list->head->data, (void*)0x2341);

    /* insert to the end */
    ret = dlist_insert(list, 2, (void*)0x3412);
    assertEquals(ret, 0);
    assertEquals(list->size, 3);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->head->next, list->tail->prev);
    assertEquals(list->tail->data, (void*)0x3412);

    /* insert to middle */
    ret = dlist_insert(list, 1, (void*)0x4123);
    assertEquals(ret, 0);
    assertEquals(list->size, 4);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->head->next, NULL);
    assertEquals(list->head->next->data, (void*)0x4123);

    /* insert to impossible location */
    ret = dlist_insert(list, 5, (void*)0x1234);
    assertNotEquals(ret, 0);
    
    /* free list */
    ret = dlist_free(list);
    assertEquals(ret, 0);
}

