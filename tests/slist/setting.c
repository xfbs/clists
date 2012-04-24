#include "cu/cu.h"
#include "clists/slist.h"

static int ret;
static slist_t *list;
static slist_node_t *node;

TEST(settingEmpty)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_set(list, 0, (void*)0x1234);
    assertNotEquals(ret, 0);
    assertEquals(list->size, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);

    ret = slist_set(list, 0, (void*)0x1234);
    assertNotEquals(ret, 0);
    assertEquals(list->size, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(settingInvalid)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_append(list, (void*)0x1234);
    assertEquals(ret, 0);
    node = list->head;

    ret = slist_set(list, 2, (void*)0x1234);
    assertNotEquals(ret, 0);
    assertEquals(list->size, 1);
    assertEquals(list->head, node);
    assertEquals(list->tail, node);
    assertEquals(node->data, (void*)0x1234);

    ret = slist_set(list, 1, (void*)0x1234);
    assertNotEquals(ret, 0);
    assertEquals(list->size, 1);
    assertEquals(list->head, node);
    assertEquals(list->tail, node);
    assertEquals(node->data, (void*)0x1234);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(settingAll)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_append(list, (void*)0x1234);
    assertEquals(ret, 0);

    ret = slist_append(list, (void*)0x2341);
    assertEquals(ret, 0);

    ret = slist_set(list, 0, (void*)0x3412);
    assertNotEquals(list->head, NULL);
    assertEquals(list->head->data, (void*)0x3412);

    ret = slist_set(list, 1, (void*)0x4123);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->tail->data, (void*)0x4123);

    ret = slist_free(list);
    assertEquals(ret, 0);
}
