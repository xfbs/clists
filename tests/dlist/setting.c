#include "cu/cu.h"
#include "clists/dlist.h"

static int ret;
static dlist_t *list;
static dlist_node_t *node;

TEST(settingEmpty)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_set(list, 0, (void*)0x1234);
    assertNotEquals(ret, 0);
    assertEquals(list->size, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);

    ret = dlist_set(list, 1, (void*)0x1234);
    assertNotEquals(ret, 0);
    assertEquals(list->size, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(settingInvalid)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_append(list, (void*)0x1234);
    assertEquals(ret, 0);
    node = list->head;

    ret = dlist_set(list, 2, (void*)0x2341);
    assertNotEquals(ret, 0);
    assertEquals(list->size, 1);
    assertEquals(list->head, node);
    assertEquals(list->tail, node);
    assertEquals(node->data, (void*)0x1234);

    ret = dlist_set(list, 1, (void*)0x1234);
    assertNotEquals(ret, 0);
    assertEquals(list->size, 1);
    assertEquals(list->head, node);
    assertEquals(list->tail, node);
    assertEquals(node->data, (void*)0x1234);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(settingAll)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_append(list, (void*)0x1234);
    assertEquals(ret, 0);

    ret = dlist_append(list, (void*)0x2341);
    assertEquals(ret, 0);

    ret = dlist_append(list, (void*)0x3412);
    assertEquals(ret, 0);

    ret = dlist_set(list, 0, (void*)0x3412);
    assertNotEquals(list->head, NULL);
    assertEquals(list->head->data, (void*)0x3412);

    ret = dlist_set(list, 1, (void*)0x4123);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->head->next, (void*)0x4123);

    assertEquals(list->tail->data, (void*)0x3412);
    ret = dlist_set(list, 2, (void*)0x4123);
    assertEquals(ret, 0);
    assertEquals(list->tail->data, (void*)0x4123);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}
