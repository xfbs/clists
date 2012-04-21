#include "cu/cu.h"
#include "clists/dlist.h"

static int ret;
static dlist_t *list;

TEST(allocNew)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);
    assertEquals(list->size, 0);
    
    free(list);
}

TEST(heapInit)
{
    list = malloc(sizeof(dlist_t));
    assertNotEquals(list, NULL);

    ret = dlist_init(list);
    assertEquals(ret, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);
    assertEquals(list->size, 0);

    free(list);
}

TEST(stackInit)
{
    dlist_t list;
    ret = dlist_init(&list);
    assertEquals(ret, 0);
    assertEquals(list.head, NULL);
    assertEquals(list.tail, NULL);
    assertEquals(list.size, 0);
}
