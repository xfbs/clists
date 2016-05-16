#include "helpers.h"

TEST(init_works_with_all_sizes)
{
    USING(malloc(sizeof(dlist_t))) {
        assertEquals(dlist_init(list, sizeof(int)), list);
        assertEquals(dlist_size(list), sizeof(int));
        assertEquals(dlist_length(list), 0);
    }

    USING(malloc(sizeof(dlist_t))) {
        assertEquals(dlist_init(list, sizeof(float)), list);
        assertEquals(dlist_size(list), sizeof(float));
        assertEquals(dlist_length(list), 0);
    }

    USING(malloc(sizeof(dlist_t))) {
        assertEquals(dlist_init(list, 56), list);
        assertEquals(dlist_size(list), 56);
        assertEquals(dlist_length(list), 0);
    }
}

TEST(init_sets_all_pointers_to_null)
{
    USING(malloc(sizeof(dlist_t))) {
        list->head = (void*)0x1231bacd;
        list->tail = (void*)0xabcf2231;
        assertEquals(dlist_init(list, sizeof(int)), list);
        assertEquals(list->head, NULL);
        assertEquals(list->tail, NULL);
    }
}
