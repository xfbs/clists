#include "helpers.h"

TEST(copy_works_on_empty_list) {
    USING(slist_new(sizeof(int))) {
        slist_t *copy = slist_copy(list);
        assertEquals(slist_length(copy), 0);
        assertEquals(slist_size(copy), slist_size(list));
        assertEquals(slist_verify(copy), 0);
        slist_free(copy);
    }

    USING(slist_new(sizeof(float))) {
        slist_t *copy = slist_copy(list);
        assertEquals(slist_length(copy), 0);
        assertEquals(slist_size(copy), slist_size(list));
        assertEquals(slist_verify(copy), 0);
        slist_free(copy);
    }
}

TEST(copy_works_on_full_list) {
    int one = 1, two = 2, three = 3, four = 4;

    USING(slist_new(sizeof(int))) {
        slist_append(list, &one);

        slist_t *copy = slist_copy(list);
        assertNotEquals(copy, NULL);
        assertEquals(slist_verify(copy), 0);
        assertEquals(slist_length(copy), slist_length(list));
        assertEquals(slist_size(copy), slist_size(list));
        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        
        slist_free(copy);
    }

    USING(slist_new(sizeof(int))) {
        slist_append(list, &one);
        slist_append(list, &two);

        slist_t *copy = slist_copy(list);
        assertNotEquals(copy, NULL);
        assertEquals(slist_verify(copy), 0);
        assertEquals(slist_length(copy), slist_length(list));
        assertEquals(slist_size(copy), slist_size(list));
        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), two);
        
        slist_free(copy);
    }

    USING(slist_new(sizeof(int))) {
        slist_append(list, &one);
        slist_append(list, &two);
        slist_append(list, &three);

        slist_t *copy = slist_copy(list);
        assertNotEquals(copy, NULL);
        assertEquals(slist_verify(copy), 0);
        assertEquals(slist_length(copy), slist_length(list));
        assertEquals(slist_size(copy), slist_size(list));
        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), two);
        assertEquals(*((int*)slist_get(list, 2, NULL)), three);

        slist_free(copy);
    }
}
