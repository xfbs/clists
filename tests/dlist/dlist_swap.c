#include "helpers.h"

TEST(swap_does_not_work_on_empty_list) {
    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_swap(list, 0, 1), 0);
    }

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_swap(list, 1, 0), 0);
    }

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_swap(list, 4, 2), 0);
    }

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_swap(list, 2, 4), 0);
    }

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_swap(list, 0, 0), 0);
    }
}

TEST(swap_does_not_work_on_nonexisting_indices) {
    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, NULL), NULL);
        assertNotEquals(dlist_swap(list, 0, 1), 0);
        assertEquals(dlist_verify(list), 0);
        assertNotEquals(dlist_swap(list, 2, 0), 0);
        assertEquals(dlist_verify(list), 0);
    }

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, NULL), NULL);
        assertNotEquals(dlist_append(list, NULL), NULL);
        assertNotEquals(dlist_swap(list, 1, 2), 0);
        assertEquals(dlist_verify(list), 0);
        assertNotEquals(dlist_swap(list, 2, 0), 0);
        assertEquals(dlist_verify(list), 0);
    }

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, NULL), NULL);
        assertNotEquals(dlist_append(list, NULL), NULL);
        assertNotEquals(dlist_append(list, NULL), NULL);
        assertNotEquals(dlist_swap(list, 1, 3), 0);
        assertEquals(dlist_verify(list), 0);
        assertNotEquals(dlist_swap(list, 5, 0), 0);
        assertEquals(dlist_verify(list), 0);
    }
}

TEST(swap_does_nothing_when_indices_are_equal) {
    int one = 1, two = 2, three = 3, four = 4;

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, &one), NULL);
        assertNotEquals(dlist_append(list, &two), NULL);

        assertEquals(dlist_swap(list, 0, 0), 0);
        assertEquals(dlist_verify(list), 0);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), two);

        assertEquals(dlist_swap(list, 1, 1), 0);
        assertEquals(dlist_verify(list), 0);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), two);
    }

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, &one), NULL);
        assertNotEquals(dlist_append(list, &two), NULL);
        assertNotEquals(dlist_append(list, &three), NULL);

        assertEquals(dlist_swap(list, 0, 0), 0);
        assertEquals(dlist_verify(list), 0);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), two);
        assertEquals(*((int*)dlist_get(list, 2, NULL)), three);

        assertEquals(dlist_swap(list, 1, 1), 0);
        assertEquals(dlist_verify(list), 0);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), two);
        assertEquals(*((int*)dlist_get(list, 2, NULL)), three);

        assertEquals(dlist_swap(list, 2, 2), 0);
        assertEquals(dlist_verify(list), 0);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), two);
        assertEquals(*((int*)dlist_get(list, 2, NULL)), three);
    }
}

TEST(swap_works_correctly_with_different_indices) {
    int one = 1, two = 2, three = 3, four = 4;

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, &one), NULL);
        assertNotEquals(dlist_append(list, &two), NULL);

        assertEquals(dlist_swap(list, 1, 0), 0);
        assertEquals(dlist_verify(list), 0);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), two);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), one);

        assertEquals(dlist_swap(list, 0, 1), 0);
        assertEquals(dlist_verify(list), 0);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), two);
    }

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, &one), NULL);
        assertNotEquals(dlist_append(list, &two), NULL);
        assertNotEquals(dlist_append(list, &three), NULL);

        assertEquals(dlist_swap(list, 0, 1), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(*((int*)dlist_get(list, 0, NULL)), two);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 2, NULL)), three);

        assertEquals(dlist_swap(list, 2, 1), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(*((int*)dlist_get(list, 0, NULL)), two);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), three);
        assertEquals(*((int*)dlist_get(list, 2, NULL)), one);

        assertEquals(dlist_swap(list, 0, 2), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), three);
        assertEquals(*((int*)dlist_get(list, 2, NULL)), two);

        assertNotEquals(dlist_append(list, &four), NULL);

        assertEquals(dlist_swap(list, 1, 2), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), two);
        assertEquals(*((int*)dlist_get(list, 2, NULL)), three);
        assertEquals(*((int*)dlist_get(list, 3, NULL)), four);
    }
}
