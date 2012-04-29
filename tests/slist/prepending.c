#include "cu/cu.h"
#include "clists/slist.h"

static int ret;
static slist_t *list;
static slist_node_t *node;

TEST(prependEmpty)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_prepend(list, (void*)0x1234);
    assertEquals(ret, 0);

    assertEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertEquals(list->size, 1);

    node = list->head;
    assertEquals(node->data, (void*)0x1234);
    assertEquals(node->next, NULL);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(prependFull)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_prepend(list, (void*)0x1234);
    assertEquals(ret, 0);

    ret = slist_prepend(list, (void*)0x2341);
    assertEquals(ret, 0);

    assertNotEquals(list->head, list->tail);
    assertEquals(list->size, 2);
    assertEquals(list->head->next, list->tail);
    assertEquals(list->head->data, (void*)0x2341);
    assertEquals(list->tail->data, (void*)0x1234);

    ret = slist_prepend(list, (void*)0x3412);
    assertEquals(ret, 0);

    assertEquals(list->size, 3);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertNotEquals(list->head->next, NULL);
    assertNotEquals(list->head->next, NULL);
    assertEquals(list->head->next->next, list->tail);
    assertEquals(list->head->data, (void*)0x3412);
    assertEquals(list->tail->data, (void*)0x1234);
    assertEquals(list->head->next->data, (void*)0x2341);

    ret = slist_free(list);
    assertEquals(ret, 0);
}
