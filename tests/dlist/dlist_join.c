#include "helpers.h"

TEST(join_does_not_work_on_different_element_sizes) {
    USING(dlist_new(sizeof(int))) {
        dlist_t *other = dlist_new(sizeof(int)+2);
        assertEquals(dlist_join(list, other), NULL);
        assertEquals(dlist_join(other, list), NULL);
        dlist_free(other);
    }
}

TEST(join_works_on_empty_lists) {
    int one = 1, two = 2, three = 3;

    USING(dlist_new(sizeof(int))) {
        dlist_t *other = dlist_new(sizeof(int));
        assertEquals(dlist_join(list, other), list);
        assertEquals(dlist_length(other), 0);
        assertEquals(dlist_verify(other), 0);
        assertEquals(dlist_verify(list), 0);
        dlist_free(other);
    }

    USING(dlist_new(sizeof(int))) {
        dlist_t *other = dlist_new(sizeof(int));
        dlist_append(list, &one);

        assertEquals(dlist_join(list, other), list);
        assertEquals(dlist_length(other), 0);
        assertEquals(dlist_length(list), 1);
        assertEquals(dlist_verify(other), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);

        assertEquals(dlist_join(other, list), other);
        assertEquals(dlist_length(other), 1);
        assertEquals(dlist_length(list), 0);
        assertEquals(dlist_verify(other), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(*((int*)dlist_get(other, 0, NULL)), one);

        dlist_free(other);
    }
    
    USING(dlist_new(sizeof(int))) {
        dlist_t *other = dlist_new(sizeof(int));
        dlist_append(list, &one);
        dlist_append(list, &two);

        assertEquals(dlist_join(list, other), list);
        assertEquals(dlist_length(other), 0);
        assertEquals(dlist_length(list), 2);
        assertEquals(dlist_verify(other), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), two);

        assertEquals(dlist_join(other, list), other);
        assertEquals(dlist_length(other), 2);
        assertEquals(dlist_length(list), 0);
        assertEquals(dlist_verify(other), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(*((int*)dlist_get(other, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(other, 1, NULL)), two);
        dlist_free(other);
    }

    USING(dlist_new(sizeof(int))) {
        dlist_t *other = dlist_new(sizeof(int));
        dlist_append(list, &one);
        dlist_append(list, &two);
        dlist_append(list, &three);

        assertEquals(dlist_join(list, other), list);
        assertEquals(dlist_length(other), 0);
        assertEquals(dlist_length(list), 3);
        assertEquals(dlist_verify(other), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), two);
        assertEquals(*((int*)dlist_get(list, 2, NULL)), three);

        assertEquals(dlist_join(other, list), other);
        assertEquals(dlist_length(other), 3);
        assertEquals(dlist_length(list), 0);
        assertEquals(dlist_verify(other), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(*((int*)dlist_get(other, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(other, 1, NULL)), two);
        assertEquals(*((int*)dlist_get(other, 2, NULL)), three);
        dlist_free(other);
    }
}

TEST(join_works_on_full_lists) {
    int one = 1, two = 2, three = 3, four = 4;

    USING(dlist_new(sizeof(int))) {
        dlist_append(list, &one);
        
        dlist_t *other = dlist_new(sizeof(int));
        dlist_append(list, &two);

        assertEquals(dlist_join(list, other), list);
        assertEquals(dlist_length(other), 0);
        assertEquals(dlist_length(list), 2);
        assertEquals(dlist_verify(other), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), two);
        dlist_free(other);
    }

    USING(dlist_new(sizeof(int))) {
        dlist_append(list, &one);
        dlist_append(list, &two);
        
        dlist_t *other = dlist_new(sizeof(int));
        dlist_append(list, &three);

        assertEquals(dlist_join(list, other), list);
        assertEquals(dlist_length(other), 0);
        assertEquals(dlist_length(list), 3);
        assertEquals(dlist_verify(other), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), two);
        assertEquals(*((int*)dlist_get(list, 2, NULL)), three);
        dlist_free(other);
    }

    USING(dlist_new(sizeof(int))) {
        dlist_append(list, &one);
        dlist_append(list, &two);
        
        dlist_t *other = dlist_new(sizeof(int));
        dlist_append(list, &three);
        dlist_append(list, &four);

        assertEquals(dlist_join(list, other), list);
        assertEquals(dlist_length(other), 0);
        assertEquals(dlist_length(list), 4);
        assertEquals(dlist_verify(other), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), two);
        assertEquals(*((int*)dlist_get(list, 2, NULL)), three);
        assertEquals(*((int*)dlist_get(list, 3, NULL)), four);
        dlist_free(other);
    }
}
