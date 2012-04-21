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

    slist_free(list);
}

TEST(prependFull)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_prepend(list, (void*)0x1234);
    assertEquals(ret, 0);

    ret = slist_prepend(list, (void*)0x4321);
    assertEquals(ret, 0);

    assertNotEquals(list->head, list->tail);
    assertEquals(list->size, 2);
    assertEquals(list->head->next, list->tail);
    assertEquals(list->head->data, (void*)0x4321);
    assertEquals(list->tail->data, (void*)0x1234);

    slist_free(list);
}

