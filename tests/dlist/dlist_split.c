#include "helpers.h"

TEST(split_does_not_work_on_empty_list) {
    USING(dlist_new(sizeof(int))) {
        assertEquals(dlist_split(list, 0), NULL);
    }
}

TEST(split_does_not_work_on_illegal_pos) {
    USING(dlist_new(sizeof(int))) {
        dlist_append(list, NULL);

        assertEquals(dlist_split(list, 1), NULL);
    }

    USING(dlist_new(sizeof(int))) {
        dlist_append(list, NULL);
        dlist_append(list, NULL);

        assertEquals(dlist_split(list, 2), NULL);
        assertEquals(dlist_split(list, 3), NULL);
    }
}

TEST(split_on_head_works_on_full_list) {
    int one = 1, two = 2, three = 3;

    USING(dlist_new(sizeof(int))) {
        dlist_append(list, &one);

        dlist_t *splt = dlist_split(list, 0);
        assertNotEquals(splt, NULL);
        assertEquals(dlist_verify(list), 0);
        assertEquals(dlist_verify(splt), 0);
        assertEquals(dlist_length(splt), 1);
        assertEquals(dlist_length(list), 0);
        assertEquals(*((int*)dlist_get(splt, 0, NULL)), one);
        assertEquals(dlist_size(splt), sizeof(int));
        assertEquals(dlist_size(list), sizeof(int));
        
        dlist_free(splt);
    }

    USING(dlist_new(sizeof(int))) {
        dlist_append(list, &one);
        dlist_append(list, &two);

        dlist_t *splt = dlist_split(list, 0);
        assertNotEquals(splt, NULL);
        assertEquals(dlist_verify(list), 0);
        assertEquals(dlist_verify(splt), 0);
        assertEquals(dlist_length(splt), 2);
        assertEquals(dlist_length(list), 0);
        assertEquals(*((int*)dlist_get(splt, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(splt, 1, NULL)), two);
        assertEquals(dlist_size(splt), sizeof(int));
        assertEquals(dlist_size(list), sizeof(int));
        
        dlist_free(splt);
    }

    USING(dlist_new(sizeof(int))) {
        dlist_append(list, &one);
        dlist_append(list, &two);
        dlist_append(list, &three);

        dlist_t *splt = dlist_split(list, 0);
        assertNotEquals(splt, NULL);
        assertEquals(dlist_verify(list), 0);
        assertEquals(dlist_verify(splt), 0);
        assertEquals(dlist_length(splt), 3);
        assertEquals(dlist_length(list), 0);
        assertEquals(*((int*)dlist_get(splt, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(splt, 1, NULL)), two);
        assertEquals(*((int*)dlist_get(splt, 2, NULL)), three);
        assertEquals(dlist_size(splt), sizeof(int));
        assertEquals(dlist_size(list), sizeof(int));
        
        dlist_free(splt);
    }
}

TEST(split_on_rest_works_on_full_list) {
    int one = 1, two = 2, three = 3, four = 4;

    USING(dlist_new(sizeof(int))) {
        dlist_append(list, &one);
        dlist_append(list, &two);

        dlist_t *splt = dlist_split(list, 1);
        assertNotEquals(splt, NULL);
        assertEquals(dlist_verify(list), 0);
        assertEquals(dlist_verify(splt), 0);
        assertEquals(dlist_length(splt), 1);
        assertEquals(dlist_length(list), 1);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(splt, 0, NULL)), two);
        assertEquals(dlist_size(splt), sizeof(int));
        assertEquals(dlist_size(list), sizeof(int));
        
        dlist_free(splt);
    }

    USING(dlist_new(sizeof(int))) {
        dlist_append(list, &one);
        dlist_append(list, &two);
        dlist_append(list, &three);

        dlist_t *splt = dlist_split(list, 1);
        assertNotEquals(splt, NULL);
        assertEquals(dlist_verify(list), 0);
        assertEquals(dlist_verify(splt), 0);
        assertEquals(dlist_length(splt), 2);
        assertEquals(dlist_length(list), 1);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(splt, 0, NULL)), two);
        assertEquals(*((int*)dlist_get(splt, 1, NULL)), three);
        assertEquals(dlist_size(splt), sizeof(int));
        assertEquals(dlist_size(list), sizeof(int));
        
        dlist_free(splt);
    }

    USING(dlist_new(sizeof(int))) {
        dlist_append(list, &one);
        dlist_append(list, &two);
        dlist_append(list, &three);

        dlist_t *splt = dlist_split(list, 2);
        assertNotEquals(splt, NULL);
        assertEquals(dlist_verify(list), 0);
        assertEquals(dlist_verify(splt), 0);
        assertEquals(dlist_length(splt), 1);
        assertEquals(dlist_length(list), 2);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), two);
        assertEquals(*((int*)dlist_get(splt, 0, NULL)), three);
        assertEquals(dlist_size(splt), sizeof(int));
        assertEquals(dlist_size(list), sizeof(int));
        
        dlist_free(splt);
    }

    USING(dlist_new(sizeof(int))) {
        dlist_append(list, &one);
        dlist_append(list, &two);
        dlist_append(list, &three);
        dlist_append(list, &four);

        dlist_t *splt = dlist_split(list, 2);
        assertNotEquals(splt, NULL);
        assertEquals(dlist_verify(list), 0);
        assertEquals(dlist_verify(splt), 0);
        assertEquals(dlist_length(splt), 2);
        assertEquals(dlist_length(list), 2);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), one);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), two);
        assertEquals(*((int*)dlist_get(splt, 0, NULL)), three);
        assertEquals(*((int*)dlist_get(splt, 1, NULL)), four);
        assertEquals(dlist_size(splt), sizeof(int));
        assertEquals(dlist_size(list), sizeof(int));
        
        dlist_free(splt);
    }
}
