#include "helpers.h"

TEST(new_works_with_all_sizes)
{
    USING(slist_new(sizeof(int))) {
        assertEquals(slist_size(list), sizeof(int));
        assertEquals(slist_length(list), 0);
    }

    USING(slist_new(sizeof(float))) {
        assertEquals(slist_size(list), sizeof(float));
        assertEquals(slist_length(list), 0);
    }

    USING(slist_new(56)) {
        assertEquals(slist_size(list), 56);
        assertEquals(slist_length(list), 0);
    }
}

TEST(new_sets_all_pointers_to_null)
{
    USING(slist_new(sizeof(int))) {
        assertEquals(list->head, NULL);
        assertEquals(list->tail, NULL);
    }

    USING(slist_new(sizeof(float))) {
        assertEquals(list->head, NULL);
        assertEquals(list->tail, NULL);
    }
}
