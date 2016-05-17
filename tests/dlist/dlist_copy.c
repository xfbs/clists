#include "helpers.h"

TEST(copy_works_on_empty_list) {
    USING(dlist_new(sizeof(int))) {
        dlist_t *copy = dlist_copy(list);
        assertEquals(dlist_length(copy), 0);
        assertEquals(dlist_size(copy), dlist_size(list));
        assertEquals(dlist_verify(copy), 0);
        dlist_free(copy);
    }

    USING(dlist_new(sizeof(float))) {
        dlist_t *copy = dlist_copy(list);
        assertEquals(dlist_length(copy), 0);
        assertEquals(dlist_size(copy), dlist_size(list));
        assertEquals(dlist_verify(copy), 0);
        dlist_free(copy);
    }
}

TEST(copy_works_on_full_list) {
    int one = 1, two = 2, three = 3, four = 4;

    USING(dlist_new(sizeof(int))) {
        dlist_append(list, &one);

        dlist_t *copy = dlist_copy(list);
        assertNotEquals(copy, NULL);
        assertEquals(dlist_verify(copy), 0);
        assertEquals(dlist_length(copy), dlist_length(list));
        assertEquals(dlist_size(copy), dlist_size(list));
        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(copy, 0, NULL)), one);
        
        dlist_free(copy);
    }

    USING(dlist_new(sizeof(int))) {
        dlist_append(list, &one);
        dlist_append(list, &two);

        dlist_t *copy = dlist_copy(list);
        assertNotEquals(copy, NULL);
        assertEquals(dlist_verify(copy), 0);
        assertEquals(dlist_length(copy), dlist_length(list));
        assertEquals(dlist_size(copy), dlist_size(list));
        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(copy, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), two);
        assertEquals(*((int*)dlist_get(copy, 1, NULL)), two);
        
        dlist_free(copy);
    }

    USING(dlist_new(sizeof(int))) {
        dlist_append(list, &one);
        dlist_append(list, &two);
        dlist_append(list, &three);

        dlist_t *copy = dlist_copy(list);
        assertNotEquals(copy, NULL);
        assertEquals(dlist_verify(copy), 0);
        assertEquals(dlist_length(copy), dlist_length(list));
        assertEquals(dlist_size(copy), dlist_size(list));
        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(copy, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), two);
        assertEquals(*((int*)dlist_get(copy, 1, NULL)), two);
        assertEquals(*((int*)dlist_get(list, 2, NULL)), three);
        assertEquals(*((int*)dlist_get(copy, 2, NULL)), three);

        dlist_free(copy);
    }
}
