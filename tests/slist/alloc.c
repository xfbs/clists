#include "cu/cu.h"
#include "clists/slist.h"

TEST(allocation)
{
    slist_t *list = slist_new();
    assertNotEquals(list, NULL);
    assertEquals(list->size, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);
    free(list);
}

TEST(initialization)
{
    slist_t list;
    assertEquals(slist_init(&list), 0);
    assertEquals(list.size, 0);
    assertEquals(list.head, NULL);
    assertEquals(list.tail, NULL);
}

TEST(manualAllocation)
{
    slist_t *list = malloc(sizeof(slist_t));
    assertNotEquals(list, NULL);
    assertEquals(slist_init(list), 0);
    assertEquals(list->size, 0);
    assertEquals(list->head, NULL);
    assertEquals(list->tail, NULL);
}
