#include "helpers.h"

TEST(pop_works_on_empty_list) {
    USING(dlist_new(sizeof(int))) {
        assertEquals(dlist_pop(list, NULL), NULL);
    }

    USING(dlist_new(sizeof(int))) {
        assertEquals(dlist_pop(list, &ret), NULL);
    }
}

TEST(pop_works_on_single_list) {
    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, &ret), NULL);
        assertEquals(dlist_pop(list, NULL), NULL);
        assertEquals(dlist_length(list), 0);
        assertEquals(dlist_size(list), sizeof(int));
    }

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, &ret), NULL);
        assertEquals(dlist_pop(list, &ret), &ret);
        assertEquals(dlist_length(list), 0);
        assertEquals(dlist_size(list), sizeof(int));
    }
}

TEST(pop_works_on_full_list) {
    USING(dlist_new(sizeof(int))) {
        ret = 1;
        assertNotEquals(dlist_append(list, &ret), NULL);
        ret = 2;
        assertNotEquals(dlist_append(list, &ret), NULL);
        ret = 3;
        assertNotEquals(dlist_append(list, &ret), NULL);

        assertNotEquals(dlist_get(list, 0, &ret), NULL);
        assertEquals(ret, 1);

        assertEquals(dlist_pop(list, &ret), &ret);
        assertEquals(dlist_length(list), 2);
        assertEquals(dlist_size(list), sizeof(int));
        assertEquals(dlist_verify(list), 0);

        assertNotEquals(dlist_get(list, 0, &ret), NULL);
        assertEquals(ret, 2);

        assertEquals(dlist_pop(list, &ret), &ret);
        assertEquals(dlist_length(list), 1);
        assertEquals(dlist_size(list), sizeof(int));
        assertEquals(dlist_verify(list), 0);

        assertNotEquals(dlist_get(list, 0, &ret), NULL);
        assertEquals(ret, 3);

        assertEquals(dlist_pop(list, &ret), &ret);
        assertEquals(dlist_length(list), 0);
        assertEquals(dlist_size(list), sizeof(int));
        assertEquals(dlist_verify(list), 0);
    }
}
