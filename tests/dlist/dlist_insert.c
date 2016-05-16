#include "helpers.h"

TEST(insert_works_without_data) {
    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_insert(list, 0, NULL), NULL);
        assertEquals(dlist_size(list), sizeof(int));
        assertEquals(dlist_length(list), 1);
    }

    USING(dlist_new(sizeof(int))) {
        // insert at beginning
        assertNotEquals(dlist_insert(list, 0, NULL), NULL);
        assertNotEquals(dlist_insert(list, 0, NULL), NULL);
        assertNotEquals(dlist_insert(list, 0, NULL), NULL);
        assertEquals(dlist_size(list), sizeof(int));
        assertEquals(dlist_length(list), 3);
    }

    USING(dlist_new(sizeof(int))) {
        // insert at end
        assertNotEquals(dlist_insert(list, 0, NULL), NULL);
        assertNotEquals(dlist_insert(list, 1, NULL), NULL);
        assertNotEquals(dlist_insert(list, 2, NULL), NULL);
        assertEquals(dlist_size(list), sizeof(int));
        assertEquals(dlist_length(list), 3);
    }

    USING(dlist_new(sizeof(int))) {
        // insert in middle
        assertNotEquals(dlist_insert(list, 0, NULL), NULL);
        assertNotEquals(dlist_insert(list, 1, NULL), NULL);
        assertNotEquals(dlist_insert(list, 1, NULL), NULL);
        assertNotEquals(dlist_insert(list, 1, NULL), NULL);
        assertEquals(dlist_size(list), sizeof(int));
        assertEquals(dlist_length(list), 4);
    }
}

TEST(insert_returns_null_on_illegal) {
    USING(dlist_new(sizeof(int))) {
        assertEquals(dlist_insert(list, 4, NULL), NULL);
    }

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_insert(list, 0, NULL), NULL);
        assertNotEquals(dlist_insert(list, 0, NULL), NULL);
        assertEquals(dlist_length(list), 2);

        assertEquals(dlist_insert(list, 3, NULL), NULL);
        assertEquals(dlist_insert(list, 5, NULL), NULL);
    }
}

TEST(insert_works_with_data) {
    int one = 1;
    int two = 2;
    int three = 3;
    int four = 4;

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_insert(list, 0, &one), NULL);
        assertEquals(dlist_size(list), sizeof(int));
        assertEquals(dlist_length(list), 1);
        assertNotEquals(dlist_get(list, 0, &ret), NULL);
        assertEquals(ret, one);
    }

    USING(dlist_new(sizeof(int))) {
        // insert at beginning
        assertNotEquals(dlist_insert(list, 0, &three), NULL);
        assertNotEquals(dlist_insert(list, 0, &two), NULL);
        assertNotEquals(dlist_insert(list, 0, &one), NULL);
        assertEquals(dlist_size(list), sizeof(int));
        assertEquals(dlist_length(list), 3);

        assertNotEquals(dlist_get(list, 0, &ret), NULL);
        assertEquals(ret, one);
        assertNotEquals(dlist_get(list, 1, &ret), NULL);
        assertEquals(ret, two);
        assertNotEquals(dlist_get(list, 2, &ret), NULL);
        assertEquals(ret, three);
    }

    USING(dlist_new(sizeof(int))) {
        // insert at end
        assertNotEquals(dlist_insert(list, 0, &one), NULL);
        assertNotEquals(dlist_insert(list, 1, &two), NULL);
        assertNotEquals(dlist_insert(list, 2, &three), NULL);
        assertEquals(dlist_size(list), sizeof(int));
        assertEquals(dlist_length(list), 3);

        assertNotEquals(dlist_get(list, 0, &ret), NULL);
        assertEquals(ret, one);
        assertNotEquals(dlist_get(list, 1, &ret), NULL);
        assertEquals(ret, two);
        assertNotEquals(dlist_get(list, 2, &ret), NULL);
        assertEquals(ret, three);
    }

    USING(dlist_new(sizeof(int))) {
        // insert in middle
        assertNotEquals(dlist_insert(list, 0, &one), NULL);
        assertNotEquals(dlist_insert(list, 1, &four), NULL);
        assertNotEquals(dlist_insert(list, 1, &three), NULL);
        assertNotEquals(dlist_insert(list, 1, &two), NULL);
        assertEquals(dlist_size(list), sizeof(int));
        assertEquals(dlist_length(list), 4);

        assertNotEquals(dlist_get(list, 0, &ret), NULL);
        assertEquals(ret, one);
        assertNotEquals(dlist_get(list, 1, &ret), NULL);
        assertEquals(ret, two);
        assertNotEquals(dlist_get(list, 2, &ret), NULL);
        assertEquals(ret, three);
        assertNotEquals(dlist_get(list, 3, &ret), NULL);
        assertEquals(ret, four);
    }
}
