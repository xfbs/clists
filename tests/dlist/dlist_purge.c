#include "helpers.h"

TEST(purge_does_nothing_on_empty_list)
{
    USING(dlist_new(sizeof(int))) {
        assertEquals(dlist_purge(list), list);
        assertEquals(dlist_length(list), 0);
        assertEquals(dlist_size(list), sizeof(int));
    }
}

TEST(purge_removes_all_elements_of_list) {
    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, NULL), NULL);
        assertEquals(dlist_length(list), 1);
        assertEquals(dlist_purge(list), list);
        assertEquals(dlist_length(list), 0);
        assertEquals(dlist_size(list), sizeof(int));
    }

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, NULL), NULL);
        assertNotEquals(dlist_append(list, NULL), NULL);
        assertEquals(dlist_length(list), 2);
        assertEquals(dlist_purge(list), list);
        assertEquals(dlist_length(list), 0);
        assertEquals(dlist_size(list), sizeof(int));
    }

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, NULL), NULL);
        assertNotEquals(dlist_append(list, NULL), NULL);
        assertNotEquals(dlist_append(list, NULL), NULL);
        assertEquals(dlist_length(list), 3);
        assertEquals(dlist_purge(list), list);
        assertEquals(dlist_length(list), 0);
        assertEquals(dlist_size(list), sizeof(int));
    }
}
