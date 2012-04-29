#include "cu/cu.h"
#include "clists/slist.h"

static int ret;
static slist_t *list;
static slist_node_t *node;

TEST(purgingEmpty)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_purge(list);
    assertEquals(ret, 0);
    assertEquals(list->size, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);
    free(list);
}

TEST(purgingSingle)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    node = malloc(sizeof(slist_node_t));
    assertNotEquals(node, NULL);

    memset(node, 0, sizeof(slist_node_t));
    list->head = node;
    list->tail = node;
    list->size = 1;

    ret = slist_purge(list);
    assertEquals(ret, 0);
    assertEquals(list->size, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);
    free(list);
}

TEST(purgingFull)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    node = malloc(sizeof(slist_node_t));
    assertNotEquals(node, NULL);

    memset(node, 0, sizeof(slist_node_t));
    list->head = node;

    node->next = malloc(sizeof(slist_node_t));
    assertNotEquals(node->next, NULL);

    memset(node, 0, sizeof(slist_node_t));
    list->tail = node;
    list->size = 2;

    ret = slist_purge(list);
    assertEquals(ret, 0);
    assertEquals(list->size, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);
    free(list);
}

