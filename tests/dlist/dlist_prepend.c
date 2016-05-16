#include "helpers.h"

TEST(prepend_sets_both_head_and_tail) {
    USING(dlist_new(sizeof(int))) {
        assertEquals(dlist_length(list), 0);
        assertEquals(dlist_size(list), sizeof(int));
        assertEquals(list->head, NULL);
        assertEquals(list->tail, NULL);

        assertNotEquals(dlist_prepend(list, NULL), NULL);

        assertEquals(dlist_length(list), 1);
        assertEquals(dlist_size(list), sizeof(int));
        assertNotEquals(list->head, NULL);
        assertNotEquals(list->tail, NULL);
        assertEquals(list->head, list->tail);

        assertNotEquals(dlist_prepend(list, NULL), NULL);

        assertEquals(dlist_length(list), 2);
        assertEquals(dlist_size(list), sizeof(int));
        assertNotEquals(list->head, NULL);
        assertNotEquals(list->tail, NULL);
        assertNotEquals(list->head, list->tail);
        assertEquals(list->head->next, list->tail);

        assertNotEquals(dlist_prepend(list, NULL), NULL);

        assertEquals(dlist_length(list), 3);
        assertEquals(dlist_size(list), sizeof(int));
        assertNotEquals(list->head, NULL);
        assertNotEquals(list->head->next, NULL);
        assertNotEquals(list->tail, NULL);
        assertNotEquals(list->head, list->tail);
        assertEquals(list->head->next->next, list->tail);
    }
}

TEST(prepend_sets_data_correctly) {
    USING(dlist_new(sizeof(int))) {
        int num = 1;
        assertNotEquals(dlist_prepend(list, &num), NULL);

        num = 2;
        assertNotEquals(dlist_prepend(list, &num), NULL);

        num = 3;
        assertNotEquals(dlist_prepend(list, &num), NULL);

        assertNotEquals(dlist_get(list, 0, &num), NULL);
        assertEquals(num, 3);

        assertNotEquals(dlist_get(list, 1, &num), NULL);
        assertEquals(num, 2);

        assertNotEquals(dlist_get(list, 2, &num), NULL);
        assertEquals(num, 1);
    }
}

TEST(prepend_sets_length_correctly) {
    USING(dlist_new(sizeof(int))) {
        int num = 5;

        assertNotEquals(dlist_prepend(list, &num), NULL);
        assertEquals(dlist_length(list), 1);
        assertNotEquals(dlist_prepend(list, &num), NULL);
        assertEquals(dlist_length(list), 2);
        assertNotEquals(dlist_prepend(list, &num), NULL);
        assertEquals(dlist_length(list), 3);
    }
}
