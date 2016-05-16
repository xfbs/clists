#include "helpers.h"

TEST(new_works_with_all_sizes)
{
    USING(dlist_new(sizeof(int))) {
        assertEquals(dlist_size(list), sizeof(int));
        assertEquals(dlist_length(list), 0);
    }

    USING(dlist_new(sizeof(float))) {
        assertEquals(dlist_size(list), sizeof(float));
        assertEquals(dlist_length(list), 0);
    }

    USING(dlist_new(56)) {
        assertEquals(dlist_size(list), 56);
        assertEquals(dlist_length(list), 0);
    }
}

TEST(new_sets_all_pointers_to_null)
{
    USING(dlist_new(sizeof(int))) {
        assertEquals(list->head, NULL);
        assertEquals(list->tail, NULL);
    }

    USING(dlist_new(sizeof(float))) {
        assertEquals(list->head, NULL);
        assertEquals(list->tail, NULL);
    }

    USING(dlist_new(sizeof(int) * 4)) {
        assertEquals(list->head, NULL);
        assertEquals(list->tail, NULL);
    }
}
