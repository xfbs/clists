#include "helpers.h"

TEST(append_sets_both_head_and_tail) {
    USING(slist_new(sizeof(int))) {
        assertEquals(slist_length(list), 0);
        assertEquals(slist_size(list), sizeof(int));
        assertEquals(list->head, NULL);
        assertEquals(list->tail, NULL);

        assertNotEquals(slist_append(list, NULL), NULL);

        assertEquals(slist_length(list), 1);
        assertEquals(slist_size(list), sizeof(int));
        assertNotEquals(list->head, NULL);
        assertNotEquals(list->tail, NULL);
        assertEquals(list->head, list->tail);

        assertNotEquals(slist_append(list, NULL), NULL);

        assertEquals(slist_length(list), 2);
        assertEquals(slist_size(list), sizeof(int));
        assertNotEquals(list->head, NULL);
        assertNotEquals(list->tail, NULL);
        assertNotEquals(list->head, list->tail);
        assertEquals(list->head->next, list->tail);

        assertNotEquals(slist_append(list, NULL), NULL);

        assertEquals(slist_length(list), 3);
        assertEquals(slist_size(list), sizeof(int));
        assertNotEquals(list->head, NULL);
        assertNotEquals(list->head->next, NULL);
        assertNotEquals(list->tail, NULL);
        assertNotEquals(list->head, list->tail);
        assertEquals(list->head->next->next, list->tail);
    }
}

TEST(append_sets_data_correctly) {
    USING(slist_new(sizeof(int))) {
        int num = 1;
        assertNotEquals(slist_append(list, &num), list);

        num = 2;
        assertNotEquals(slist_append(list, &num), list);

        num = 3;
        assertNotEquals(slist_append(list, &num), list);

        assertNotEquals(slist_get(list, 0, &num), NULL);
        assertEquals(num, 1);

        assertNotEquals(slist_get(list, 1, &num), NULL);
        assertEquals(num, 2);

        assertNotEquals(slist_get(list, 2, &num), NULL);
        assertEquals(num, 3);
    }
}

TEST(append_sets_length_correctly) {
    USING(slist_new(sizeof(int))) {
        int num = 5;

        assertNotEquals(slist_append(list, &num), list);
        assertEquals(slist_length(list), 1);
        assertNotEquals(slist_append(list, &num), list);
        assertEquals(slist_length(list), 2);
        assertNotEquals(slist_append(list, &num), list);
        assertEquals(slist_length(list), 3);
    }
}
