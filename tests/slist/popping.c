#include "cu/cu.h"
#include "clists/slist.h"

static int ret;
static void *data;
static slist_t *list;

TEST(poppingEmpty)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    data = slist_pop(list);
    assertEquals(data, NULL);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(poppingSingle)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_append(list, (void*)0x1234);
    assertEquals(ret, 0);

    data = slist_pop(list);
    assertEquals(data, (void*)0x1234);
    assertEquals(list->size, 0);

    data = slist_pop(list);
    assertEquals(data, NULL);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(poppingFull)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_append(list, (void*)0x1234);
    assertEquals(ret, 0);

    ret = slist_append(list, (void*)0x2341);
    assertEquals(ret, 0);

    ret = slist_append(list, (void*)0x3412);
    assertEquals(ret, 0);

    data = slist_pop(list);
    assertEquals(data, (void*)0x1234);
    assertEquals(list->size, 2);
    assertNotEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->head->next, list->tail);

    data = slist_pop(list);
    assertEquals(data, (void*)0x2341);
    assertEquals(list->size, 1);
    assertEquals(list->head, list->tail);
    assertNotEquals(list->head, NULL);

    data = slist_pop(list);
    assertEquals(data, (void*)0x3412);
    assertEquals(list->size, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);

    ret = slist_free(list);
    assertEquals(ret, 0);
}
