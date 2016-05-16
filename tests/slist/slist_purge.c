#include "helpers.h"

TEST(purge_does_nothing_on_empty_list)
{
    USING(slist_new(sizeof(int))) {
        assertEquals(slist_purge(list), list);
        assertEquals(slist_length(list), 0);
        assertEquals(slist_size(list), sizeof(int));
    }
}

TEST(purge_removes_all_elements_of_list) {
    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, NULL), NULL);
        assertEquals(slist_length(list), 1);
        assertEquals(slist_purge(list), list);
        assertEquals(slist_length(list), 0);
        assertEquals(slist_size(list), sizeof(int));
    }

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, NULL), NULL);
        assertNotEquals(slist_append(list, NULL), NULL);
        assertEquals(slist_length(list), 2);
        assertEquals(slist_purge(list), list);
        assertEquals(slist_length(list), 0);
        assertEquals(slist_size(list), sizeof(int));
    }

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, NULL), NULL);
        assertNotEquals(slist_append(list, NULL), NULL);
        assertNotEquals(slist_append(list, NULL), NULL);
        assertEquals(slist_length(list), 3);
        assertEquals(slist_purge(list), list);
        assertEquals(slist_length(list), 0);
        assertEquals(slist_size(list), sizeof(int));
    }
}
