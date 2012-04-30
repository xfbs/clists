#include "cu/cu.h"
#include "clists/dlist.h"

static int ret;
static void *data;
static dlist_t *list;

TEST(poppingEmpty)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    data = dlist_pop(list);
    assertEquals(data, NULL);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(poppingSingle)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_append(list, (void*)0x1234);
    assertEquals(ret, 0);

    data = dlist_pop(list);
    assertEquals(data, (void*)0x1234);
    assertEquals(list->size, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(poppingFull)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_append(list, (void*)0x1234);
    assertEquals(ret, 0);
    ret = dlist_append(list, (void*)0x2341);
    assertEquals(ret, 0);
    ret = dlist_append(list, (void*)0x3412);
    assertEquals(ret, 0);
    ret = dlist_append(list, (void*)0x4123);
    assertEquals(ret, 0);

    data = dlist_pop(list);
    assertEquals(data, (void*)0x1234);
    assertEquals(list->size, 3);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertNotEquals(list->head->next, NULL);
    assertNotEquals(list->tail->prev, NULL);
    assertEquals(list->head->next, list->tail->prev);
    assertEquals(list->head->next->next, list->tail);
    assertEquals(list->tail->prev->prev, list->head);

    data = dlist_pop(list);
    assertEquals(data, (void*)0x2341);
    assertEquals(list->size, 2);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->head->next, list->tail);
    assertEquals(list->tail->prev, list->head);

    data = dlist_pop(list);
    assertEquals(data, (void*)0x3412);
    assertEquals(list->size, 1);
    assertEquals(list->head, list->tail);

    data = dlist_pop(list);
    assertEquals(data, (void*)0x4123);
    assertEquals(list->size, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}
