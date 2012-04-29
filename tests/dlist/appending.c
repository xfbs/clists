#include "cu/cu.h"
#include "clists/dlist.h"

static int ret;
static dlist_t *list;
static dlist_node_t *node;

TEST(appendEmpty)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_append(list, (void*)0x1234);
    assertEquals(ret, 0);
    assertEquals(list->size, 1);
    assertEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertEquals(list->head->data, (void*)0x1234);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(appendFull)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_append(list, (void*)0x1234);
    assertEquals(ret, 0);
    assertEquals(list->size, 1);
    assertEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertEquals(list->head->data, (void*)0x1234);

    ret = dlist_append(list, (void*)0x2341);
    assertEquals(ret, 0);
    assertEquals(list->size, 2);
    assertNotEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->head->data, (void*)0x1234);
    assertEquals(list->tail->data, (void*)0x2341);

    ret = dlist_append(list, (void*)0x3412);
    assertEquals(ret, 0);
    assertEquals(list->size, 3);
    assertNotEquals(list->head, NULL);
    assertEquals(list->tail->data, (void*)0x3412);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}
