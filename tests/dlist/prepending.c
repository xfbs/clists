#include "cu/cu.h"
#include "clists/dlist.h"

static int ret;
static dlist_t *list;
static dlist_node_t *node;

TEST(prependEmpty)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_prepend(list, (void*)0x1234);
    assertEquals(ret, 0);

    assertEquals(list->size, 1);
    assertEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertEquals(list->head->data, (void*)0x1234);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(prependFull)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_prepend(list, (void*)0x1234);
    assertEquals(ret, 0);

    ret = dlist_prepend(list, (void*)0x2341);
    assertEquals(ret, 0);

    assertEquals(list->size, 2);
    assertNotEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->head->next, list->tail);
    assertEquals(list->tail->prev, list->head);
    assertEquals(list->head->data, (void*)0x2341);
    assertEquals(list->tail->data, (void*)0x1234);

    ret = dlist_prepend(list, (void*)0x3412);
    assertEquals(ret, 0);

    assertEquals(list->size, 3);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertNotEquals(list->head->next, NULL);
    assertEquals(list->head->next, list->tail->prev);
    assertEquals(list->head->next->next, list->tail);
    assertEquals(list->tail->prev->prev, list->head);
    assertEquals(list->head->data, (void*)0x3412);
    assertEquals(list->tail->data, (void*)0x1234);
    assertEquals(list->head->next->data, (void*)0x2341);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}
