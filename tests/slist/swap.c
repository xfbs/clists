#include "cu/cu.h"
#include "helpers.h"
#include "../../clists/slist.h"

TEST(swap_does_not_work_on_empty_list) {
    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_swap(list, 0, 1), 0);
    }

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_swap(list, 1, 0), 0);
    }

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_swap(list, 4, 2), 0);
    }

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_swap(list, 2, 4), 0);
    }

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_swap(list, 0, 0), 0);
    }
}

TEST(swap_does_not_work_on_nonexisting_indices) {
    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, NULL), NULL);
        assertNotEquals(slist_swap(list, 0, 1), 0);
        assertEquals(slist_verify(list), 0);
        assertNotEquals(slist_swap(list, 2, 0), 0);
        assertEquals(slist_verify(list), 0);
    }

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, NULL), NULL);
        assertNotEquals(slist_append(list, NULL), NULL);
        assertNotEquals(slist_swap(list, 1, 2), 0);
        assertEquals(slist_verify(list), 0);
        assertNotEquals(slist_swap(list, 2, 0), 0);
        assertEquals(slist_verify(list), 0);
    }

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, NULL), NULL);
        assertNotEquals(slist_append(list, NULL), NULL);
        assertNotEquals(slist_append(list, NULL), NULL);
        assertNotEquals(slist_swap(list, 1, 3), 0);
        assertEquals(slist_verify(list), 0);
        assertNotEquals(slist_swap(list, 5, 0), 0);
        assertEquals(slist_verify(list), 0);
    }
}

TEST(swap_does_nothing_when_indices_are_equal) {
    int one = 1, two = 2, three = 3, four = 4;

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, &one), NULL);
        assertNotEquals(slist_append(list, &two), NULL);

        assertEquals(slist_swap(list, 0, 0), 0);
        assertEquals(slist_verify(list), 0);
        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), two);

        assertEquals(slist_swap(list, 1, 1), 0);
        assertEquals(slist_verify(list), 0);
        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), two);
    }

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, &one), NULL);
        assertNotEquals(slist_append(list, &two), NULL);
        assertNotEquals(slist_append(list, &three), NULL);

        assertEquals(slist_swap(list, 0, 0), 0);
        assertEquals(slist_verify(list), 0);
        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), two);
        assertEquals(*((int*)slist_get(list, 2, NULL)), three);

        assertEquals(slist_swap(list, 1, 1), 0);
        assertEquals(slist_verify(list), 0);
        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), two);
        assertEquals(*((int*)slist_get(list, 2, NULL)), three);

        assertEquals(slist_swap(list, 2, 2), 0);
        assertEquals(slist_verify(list), 0);
        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), two);
        assertEquals(*((int*)slist_get(list, 2, NULL)), three);
    }
}

TEST(swap_works_correctly_with_different_indices) {
    int one = 1, two = 2, three = 3, four = 4;

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, &one), NULL);
        assertNotEquals(slist_append(list, &two), NULL);

        assertEquals(slist_swap(list, 1, 0), 0);
        assertEquals(slist_verify(list), 0);
        assertEquals(*((int*)slist_get(list, 0, NULL)), two);
        assertEquals(*((int*)slist_get(list, 1, NULL)), one);

        assertEquals(slist_swap(list, 0, 1), 0);
        assertEquals(slist_verify(list), 0);
        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), two);
    }

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, &one), NULL);
        assertNotEquals(slist_append(list, &two), NULL);
        assertNotEquals(slist_append(list, &three), NULL);

        assertEquals(slist_swap(list, 0, 1), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(*((int*)slist_get(list, 0, NULL)), two);
        assertEquals(*((int*)slist_get(list, 1, NULL)), one);
        assertEquals(*((int*)slist_get(list, 2, NULL)), three);

        assertEquals(slist_swap(list, 2, 1), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(*((int*)slist_get(list, 0, NULL)), two);
        assertEquals(*((int*)slist_get(list, 1, NULL)), three);
        assertEquals(*((int*)slist_get(list, 2, NULL)), one);

        assertEquals(slist_swap(list, 0, 2), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), three);
        assertEquals(*((int*)slist_get(list, 2, NULL)), two);

        assertNotEquals(slist_append(list, &four), NULL);

        assertEquals(slist_swap(list, 1, 2), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), two);
        assertEquals(*((int*)slist_get(list, 2, NULL)), three);
        assertEquals(*((int*)slist_get(list, 3, NULL)), four);
    }
}
