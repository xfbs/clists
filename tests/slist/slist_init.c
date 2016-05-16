#include "helpers.h"

TEST(init_works_with_all_sizes)
{
    USING(malloc(sizeof(slist_t))) {
        assertEquals(slist_init(list, sizeof(int)), list);
        assertEquals(slist_size(list), sizeof(int));
        assertEquals(slist_length(list), 0);
    }

    USING(malloc(sizeof(slist_t))) {
        assertEquals(slist_init(list, sizeof(float)), list);
        assertEquals(slist_size(list), sizeof(float));
        assertEquals(slist_length(list), 0);
    }

    USING(malloc(sizeof(slist_t))) {
        assertEquals(slist_init(list, 56), list);
        assertEquals(slist_size(list), 56);
        assertEquals(slist_length(list), 0);
    }
}

TEST(init_sets_all_pointers_to_null)
{
    USING(malloc(sizeof(slist_t))) {
        list->head = (void*)0x1231bacd;
        list->tail = (void*)0xabcf2231;
        assertEquals(slist_init(list, sizeof(int)), list);
        assertEquals(list->head, NULL);
        assertEquals(list->tail, NULL);
    }
}
