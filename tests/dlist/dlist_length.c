#include "helpers.h"

TEST(length_works_with_basic_ops)
{
    USING(dlist_new(sizeof(float))) {
        assertEquals(dlist_length(list), 0);
        dlist_append(list, NULL);
        assertEquals(dlist_length(list), 1);
        dlist_prepend(list, NULL);
        assertEquals(dlist_length(list), 2);
        dlist_prepend(list, NULL);
        assertEquals(dlist_length(list), 3);
        dlist_remove(list, 1);
        assertEquals(dlist_length(list), 2);
        dlist_pop(list, NULL);
        assertEquals(dlist_length(list), 1);
        dlist_purge(list);
        assertEquals(dlist_length(list), 0);
    }
}

TEST(length_works_manually)
{
    dlist_t list;
    dlist_init(&list, sizeof(int));
    
    list.length = 5;
    assertEquals(dlist_length(&list), 5);

    list.length = 9;
    assertEquals(dlist_length(&list), 9);
}
