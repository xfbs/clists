#include "clists/slist.h"
#include "cu/cu.h"

static int ret;
static slist_t *list;
static slist_node_t *node;

TEST(appendEmpty)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_append(list, NULL);
    assertEquals(ret, 0);

    assertEquals(list->head, list->tail);
    assertEquals(list->size, 1);

    node = list->head;
    assertNotEquals(node, NULL);
    assertEquals(node->data, NULL);
    assertEquals(node->next, NULL);

    slist_free(list);
}

TEST(appendFull)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_append(list, (void*)0x1234);
    assertEquals(ret, 0);

    ret = slist_append(list, (void*)0x4321);
    assertEquals(ret, 0);

    assertNotEquals(node->next, NULL);
    assertNotEquals(list->head, list->tail);
    assertEquals(list->tail, node->next);
    assertEquals(list->head->data, (void*)0x1234);
    assertEquals(list->tail->data, (void*)0x4321);
    assertEquals(list->size, 2);

    slist_free(list);
}
