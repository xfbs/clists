#include "cu/cu.h"
#include "helpers.h"
#include "../../clists/slist.h"

TEST(split_does_not_work_on_empty_list) {
    USING(slist_new(sizeof(int))) {
        assertEquals(slist_split(list, 0), NULL);
    }
}

TEST(split_does_not_work_on_illegal_pos) {
    USING(slist_new(sizeof(int))) {
        slist_append(list, NULL);

        assertEquals(slist_split(list, 1), NULL);
    }

    USING(slist_new(sizeof(int))) {
        slist_append(list, NULL);
        slist_append(list, NULL);

        assertEquals(slist_split(list, 2), NULL);
        assertEquals(slist_split(list, 3), NULL);
    }
}

TEST(split_on_head_works_on_full_list) {
    int one = 1, two = 2, three = 3;

    USING(slist_new(sizeof(int))) {
        slist_append(list, &one);

        slist_t *splt = slist_split(list, 0);
        assertNotEquals(splt, NULL);
        assertEquals(slist_verify(list), 0);
        assertEquals(slist_verify(splt), 0);
        assertEquals(slist_length(splt), 1);
        assertEquals(slist_length(list), 0);
        assertEquals(*((int*)slist_get(splt, 0, NULL)), one);
        assertEquals(slist_size(splt), sizeof(int));
        assertEquals(slist_size(list), sizeof(int));
        
        slist_free(splt);
    }

    USING(slist_new(sizeof(int))) {
        slist_append(list, &one);
        slist_append(list, &two);

        slist_t *splt = slist_split(list, 0);
        assertNotEquals(splt, NULL);
        assertEquals(slist_verify(list), 0);
        assertEquals(slist_verify(splt), 0);
        assertEquals(slist_length(splt), 2);
        assertEquals(slist_length(list), 0);
        assertEquals(*((int*)slist_get(splt, 0, NULL)), one);
        assertEquals(*((int*)slist_get(splt, 1, NULL)), two);
        assertEquals(slist_size(splt), sizeof(int));
        assertEquals(slist_size(list), sizeof(int));
        
        slist_free(splt);
    }

    USING(slist_new(sizeof(int))) {
        slist_append(list, &one);
        slist_append(list, &two);
        slist_append(list, &three);

        slist_t *splt = slist_split(list, 0);
        assertNotEquals(splt, NULL);
        assertEquals(slist_verify(list), 0);
        assertEquals(slist_verify(splt), 0);
        assertEquals(slist_length(splt), 3);
        assertEquals(slist_length(list), 0);
        assertEquals(*((int*)slist_get(splt, 0, NULL)), one);
        assertEquals(*((int*)slist_get(splt, 1, NULL)), two);
        assertEquals(*((int*)slist_get(splt, 2, NULL)), three);
        assertEquals(slist_size(splt), sizeof(int));
        assertEquals(slist_size(list), sizeof(int));
        
        slist_free(splt);
    }
}

TEST(split_on_rest_works_on_full_list) {
    int one = 1, two = 2, three = 3, four = 4;

    USING(slist_new(sizeof(int))) {
        slist_append(list, &one);
        slist_append(list, &two);

        slist_t *splt = slist_split(list, 1);
        assertNotEquals(splt, NULL);
        assertEquals(slist_verify(list), 0);
        assertEquals(slist_verify(splt), 0);
        assertEquals(slist_length(splt), 1);
        assertEquals(slist_length(list), 1);
        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(splt, 0, NULL)), two);
        assertEquals(slist_size(splt), sizeof(int));
        assertEquals(slist_size(list), sizeof(int));
        
        slist_free(splt);
    }

    USING(slist_new(sizeof(int))) {
        slist_append(list, &one);
        slist_append(list, &two);
        slist_append(list, &three);

        slist_t *splt = slist_split(list, 1);
        assertNotEquals(splt, NULL);
        assertEquals(slist_verify(list), 0);
        assertEquals(slist_verify(splt), 0);
        assertEquals(slist_length(splt), 2);
        assertEquals(slist_length(list), 1);
        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(splt, 0, NULL)), two);
        assertEquals(*((int*)slist_get(splt, 1, NULL)), three);
        assertEquals(slist_size(splt), sizeof(int));
        assertEquals(slist_size(list), sizeof(int));
        
        slist_free(splt);
    }

    USING(slist_new(sizeof(int))) {
        slist_append(list, &one);
        slist_append(list, &two);
        slist_append(list, &three);

        slist_t *splt = slist_split(list, 2);
        assertNotEquals(splt, NULL);
        assertEquals(slist_verify(list), 0);
        assertEquals(slist_verify(splt), 0);
        assertEquals(slist_length(splt), 1);
        assertEquals(slist_length(list), 2);
        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), two);
        assertEquals(*((int*)slist_get(splt, 0, NULL)), three);
        assertEquals(slist_size(splt), sizeof(int));
        assertEquals(slist_size(list), sizeof(int));
        
        slist_free(splt);
    }

    USING(slist_new(sizeof(int))) {
        slist_append(list, &one);
        slist_append(list, &two);
        slist_append(list, &three);
        slist_append(list, &four);

        slist_t *splt = slist_split(list, 2);
        assertNotEquals(splt, NULL);
        assertEquals(slist_verify(list), 0);
        assertEquals(slist_verify(splt), 0);
        assertEquals(slist_length(splt), 2);
        assertEquals(slist_length(list), 2);
        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), two);
        assertEquals(*((int*)slist_get(splt, 0, NULL)), three);
        assertEquals(*((int*)slist_get(splt, 1, NULL)), four);
        assertEquals(slist_size(splt), sizeof(int));
        assertEquals(slist_size(list), sizeof(int));
        
        slist_free(splt);
    }
}
