#include "cu/cu.h"
#include "clists/slist.h"

static int ret;
static slist_t *list;

TEST(insertEmpty)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_insert(list, 0, (void*)0x1234);
    assertEquals(ret, 0);

    assertEquals(list->head, list->tail);
    assertEquals(list->size, 1);
    assertNotEquals(list->head, NULL);
    assertEquals(list->head->data, (void*)0x1234);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(insertBeginning)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_insert(list, 0, (void*)0x1234);
    assertEquals(ret, 0);

    ret = slist_insert(list, 0, (void*)0x4321);
    assertEquals(ret, 0);

    assertNotEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->size, 2);
    assertEquals(list->head->next, list->tail);
    assertEquals(list->head->data, (void*)0x4321);
    assertEquals(list->tail->data, (void*)0x1234);

    ret = slist_insert(list, 0, (void*)0x2222);
    assertEquals(ret, 0);

    assertEquals(list->size, 3);
    assertNotEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertNotEquals(list->head->next, NULL);
    assertNotEquals(list->head->next, list->tail);
    assertNotEquals(list->head->next, list->head);
    assertEquals(list->head->data, (void*)0x2222);
    assertEquals(list->tail->data, (void*)0x1234);
    assertEquals(list->head->next->data, (void*)0x4321);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(insertBack)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_insert(list, 0, (void*)0x1234);
    assertEquals(ret, 0);

    ret = slist_insert(list, 1, (void*)0x2341);
    assertEquals(ret, 0);

    assertNotEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->size, 2);
    assertEquals(list->head->next, list->tail);
    assertEquals(list->head->data, (void*)0x1234);
    assertEquals(list->tail->data, (void*)0x2341);

    ret = slist_insert(list, 2, (void*)0x3412);
    assertEquals(ret, 0);

    assertEquals(list->size, 3);
    assertNotEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertNotEquals(list->head->next, NULL);
    assertNotEquals(list->head->next, list->tail);
    assertNotEquals(list->head->next, list->head);
    assertEquals(list->head->data, (void*)0x1234);
    assertEquals(list->head->next->data, (void*)0x2341);
    assertEquals(list->tail->data, (void*)0x3412);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(insertMiddle)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_insert(list, 0, (void*)0x1234);
    assertEquals(ret, 0);

    ret = slist_insert(list, 1, (void*)0x4123);
    assertEquals(ret, 0);

    assertEquals(list->size, 2);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->head->data, (void*)0x1234);
    assertEquals(list->tail->data, (void*)0x4123);

    ret = slist_insert(list, 1, (void*)0x2341);
    assertEquals(ret, 0);

    assertEquals(list->size, 3);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertNotEquals(list->head->next, NULL);
    assertEquals(list->head->data, (void*)0x1234);
    assertEquals(list->tail->data, (void*)0x4123);
    assertEquals(list->head->next->data, (void*)0x2341);

    ret = slist_free(list);
    assertEquals(ret, 0);
}
