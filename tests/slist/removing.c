#include "cu/cu.h"
#include "clists/slist.h"

static int ret;
static slist_t *list;
static slist_node_t *node;

TEST(removeEmpty)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_remove(list, 0);
    assertNotEquals(ret, 0);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(removeBeginning)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    node = malloc(sizeof(slist_node_t));
    assertNotEquals(node, NULL);
    memset(node, 0, sizeof(slist_node_t));
    list->head = node;

    node = malloc(sizeof(slist_node_t));
    assertNotEquals(node, NULL);
    memset(node, 0, sizeof(slist_node_t));
    list->tail = node;

    list->head->next = list->tail;
    list->size = 2;

    ret = slist_remove(list, 0);
    assertEquals(ret, 0);
    assertEquals(list->size, 1);
    assertEquals(list->head, list->tail);
    assertEquals(list->head, node);
    
    ret = slist_remove(list, 0);
    assertEquals(ret, 0);
    assertEquals(list->size, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);

    ret = slist_free(list);
    assertEquals(ret, 0);
}
