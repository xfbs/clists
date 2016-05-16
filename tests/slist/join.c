#include "cu/cu.h"
#include "helpers.h"
#include "../../clists/slist.h"

TEST(join_does_not_work_on_different_element_sizes) {
    USING(slist_new(sizeof(int))) {
        slist_t *other = slist_new(sizeof(int)+2);
        assertEquals(slist_join(list, other), NULL);
        assertEquals(slist_join(other, list), NULL);
        slist_free(other);
    }
}

TEST(join_works_on_empty_lists) {
    int one = 1, two = 2, three = 3;

    USING(slist_new(sizeof(int))) {
        slist_t *other = slist_new(sizeof(int));
        assertEquals(slist_join(list, other), list);
        assertEquals(slist_length(other), 0);
        assertEquals(slist_verify(other), 0);
        assertEquals(slist_verify(list), 0);
        slist_free(other);
    }

    USING(slist_new(sizeof(int))) {
        slist_t *other = slist_new(sizeof(int));
        slist_append(list, &one);

        assertEquals(slist_join(list, other), list);
        assertEquals(slist_length(other), 0);
        assertEquals(slist_length(list), 1);
        assertEquals(slist_verify(other), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(*((int*)slist_get(list, 0, NULL)), one);

        assertEquals(slist_join(other, list), other);
        assertEquals(slist_length(other), 1);
        assertEquals(slist_length(list), 0);
        assertEquals(slist_verify(other), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(*((int*)slist_get(other, 0, NULL)), one);

        slist_free(other);
    }
    
    USING(slist_new(sizeof(int))) {
        slist_t *other = slist_new(sizeof(int));
        slist_append(list, &one);
        slist_append(list, &two);

        assertEquals(slist_join(list, other), list);
        assertEquals(slist_length(other), 0);
        assertEquals(slist_length(list), 2);
        assertEquals(slist_verify(other), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), two);

        assertEquals(slist_join(other, list), other);
        assertEquals(slist_length(other), 2);
        assertEquals(slist_length(list), 0);
        assertEquals(slist_verify(other), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(*((int*)slist_get(other, 0, NULL)), one);
        assertEquals(*((int*)slist_get(other, 1, NULL)), two);
        slist_free(other);
    }

    USING(slist_new(sizeof(int))) {
        slist_t *other = slist_new(sizeof(int));
        slist_append(list, &one);
        slist_append(list, &two);
        slist_append(list, &three);

        assertEquals(slist_join(list, other), list);
        assertEquals(slist_length(other), 0);
        assertEquals(slist_length(list), 3);
        assertEquals(slist_verify(other), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), two);
        assertEquals(*((int*)slist_get(list, 2, NULL)), three);

        assertEquals(slist_join(other, list), other);
        assertEquals(slist_length(other), 3);
        assertEquals(slist_length(list), 0);
        assertEquals(slist_verify(other), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(*((int*)slist_get(other, 0, NULL)), one);
        assertEquals(*((int*)slist_get(other, 1, NULL)), two);
        assertEquals(*((int*)slist_get(other, 2, NULL)), three);
        slist_free(other);
    }
}

TEST(join_works_on_full_lists) {
    int one = 1, two = 2, three = 3, four = 4;

    USING(slist_new(sizeof(int))) {
        slist_append(list, &one);
        
        slist_t *other = slist_new(sizeof(int));
        slist_append(list, &two);

        assertEquals(slist_join(list, other), list);
        assertEquals(slist_length(other), 0);
        assertEquals(slist_length(list), 2);
        assertEquals(slist_verify(other), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), two);
        slist_free(other);
    }

    USING(slist_new(sizeof(int))) {
        slist_append(list, &one);
        slist_append(list, &two);
        
        slist_t *other = slist_new(sizeof(int));
        slist_append(list, &three);

        assertEquals(slist_join(list, other), list);
        assertEquals(slist_length(other), 0);
        assertEquals(slist_length(list), 3);
        assertEquals(slist_verify(other), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), two);
        assertEquals(*((int*)slist_get(list, 2, NULL)), three);
        slist_free(other);
    }

    USING(slist_new(sizeof(int))) {
        slist_append(list, &one);
        slist_append(list, &two);
        
        slist_t *other = slist_new(sizeof(int));
        slist_append(list, &three);
        slist_append(list, &four);

        assertEquals(slist_join(list, other), list);
        assertEquals(slist_length(other), 0);
        assertEquals(slist_length(list), 4);
        assertEquals(slist_verify(other), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(*((int*)slist_get(list, 0, NULL)), one);
        assertEquals(*((int*)slist_get(list, 1, NULL)), two);
        assertEquals(*((int*)slist_get(list, 2, NULL)), three);
        assertEquals(*((int*)slist_get(list, 3, NULL)), four);
        slist_free(other);
    }
}
