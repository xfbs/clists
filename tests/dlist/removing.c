#include "cu/cu.h"
#include "clists/dlist.h"

static int ret;
static dlist_t *list;

TEST(removeEmpty)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_remove(list, 0);
    assertNotEquals(ret, 0);

    ret = dlist_remove(list, 1);
    assertNotEquals(ret, 0);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(removeInvalid)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_append(list, (void*)0x1234);
    assertEquals(ret, 0);

    ret = dlist_remove(list, 2);
    assertNotEquals(ret, 0);
    assertEquals(list->size, 1);
    assertEquals(list->head, list->tail);

    ret = dlist_remove(list, 1);
    assertNotEquals(ret, 0);
    assertEquals(list->size, 1);
    assertEquals(list->head, list->tail);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(removeSingle)
{
    list = dlist_new();
    assertNotEquals(list, NULL);
    
    ret = dlist_append(list, (void*)0x1234);
    assertEquals(ret, 0);

    ret = dlist_remove(list, 0);
    assertEquals(ret, 0);
    assertEquals(list->size, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(removeAll)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_append(list, (void*)0x1234);
    assertEquals(ret, 0);
    ret = dlist_append(list, (void*)0x2341);
    assertEquals(ret, 0);
    ret = dlist_append(list, (void*)0x3412);
    assertEquals(ret, 0);
    ret = dlist_append(list, (void*)0x4123);
    assertEquals(ret, 0);

    /* delete first */
    ret = dlist_remove(list, 0);
    assertEquals(ret, 0);
    assertEquals(list->size, 3);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertNotEquals(list->head->next, NULL);
    assertNotEquals(list->tail->prev, NULL);
    assertEquals(list->head->next, list->tail->prev);
    assertEquals(list->head->next->next, list->tail);
    assertEquals(list->tail->prev->prev, list->head);

    /* delete middle */
    ret = dlist_remove(list, 1);
    assertEquals(ret, 0);
    assertEquals(list->size, 2);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->head->next, list->tail);
    assertEquals(list->tail->prev, list->head);

    /* delete from back */
    ret = dlist_remove(list, 1);
    assertEquals(ret, 0);
    assertEquals(list->size, 1);
    assertEquals(list->head, list->tail);

    /* delete last */
    ret = dlist_remove(list, 0);
    assertEquals(ret, 0);
    assertEquals(list->size, 0);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}
