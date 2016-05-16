#include "helpers.h"

TEST(remove_on_empty_list_does_not_work) {
    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_remove(list, 0), 0);
    }

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_remove(list, 1), 0);
    }

    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_remove(list, 2), 0);
    }
}

TEST(remove_in_beginning_works) {
    int data[] = {32422, 214235, 23452512, -3432212};
    
    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, &data[0]), NULL);
        assertNotEquals(dlist_append(list, &data[1]), NULL);
        assertNotEquals(dlist_append(list, &data[2]), NULL);
        assertNotEquals(dlist_append(list, &data[3]), NULL);

        assertEquals(dlist_length(list), 4);
        assertEquals(*((int*)dlist_first(list)), data[0]);

        assertEquals(dlist_remove(list, 0), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(dlist_length(list), 3);
        assertEquals(*((int*)dlist_first(list)), data[1]);

        assertEquals(dlist_remove(list, 0), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(dlist_length(list), 2);
        assertEquals(*((int*)dlist_first(list)), data[2]);

        assertEquals(dlist_remove(list, 0), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(dlist_length(list), 1);
        assertEquals(*((int*)dlist_first(list)), data[3]);

        assertEquals(dlist_remove(list, 0), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(dlist_length(list), 0);
        assertEquals(dlist_first(list), NULL);

        assertNotEquals(dlist_remove(list, 0), 0);
    }
}

TEST(remove_at_end_works) {
    int data[] = {32422, 214235, 23452512, -3432212};
    
    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, &data[0]), NULL);
        assertNotEquals(dlist_append(list, &data[1]), NULL);
        assertNotEquals(dlist_append(list, &data[2]), NULL);
        assertNotEquals(dlist_append(list, &data[3]), NULL);

        assertEquals(dlist_length(list), 4);
        assertEquals(*((int*)dlist_last(list)), data[3]);

        assertNotEquals(dlist_remove(list, 4), 0);
        assertEquals(dlist_remove(list, 3), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(dlist_length(list), 3);
        assertEquals(*((int*)dlist_last(list)), data[2]);

        assertNotEquals(dlist_remove(list, 3), 0);
        assertEquals(dlist_remove(list, 2), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(dlist_length(list), 2);
        assertEquals(*((int*)dlist_last(list)), data[1]);

        assertNotEquals(dlist_remove(list, 2), 0);
        assertEquals(dlist_remove(list, 1), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(dlist_length(list), 1);
        assertEquals(*((int*)dlist_last(list)), data[0]);

        assertNotEquals(dlist_remove(list, 1), 0);
        assertEquals(dlist_remove(list, 0), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(dlist_length(list), 0);
        assertEquals(dlist_last(list), NULL);

        assertNotEquals(dlist_remove(list, 0), 0);
    }
}

TEST(remove_in_middle_works) {
    int data[] = {32422, 214235, 23452512, -3432212};
    
    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, &data[0]), NULL);
        assertNotEquals(dlist_append(list, &data[1]), NULL);
        assertNotEquals(dlist_append(list, &data[2]), NULL);
        assertNotEquals(dlist_append(list, &data[3]), NULL);

        assertEquals(dlist_length(list), 4);
        assertEquals(*((int*)dlist_get(list, 2, NULL)), data[2]);

        assertEquals(dlist_remove(list, 2), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(dlist_length(list), 3);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), data[1]);
        assertEquals(*((int*)dlist_get(list, 2, NULL)), data[3]);

        assertEquals(dlist_remove(list, 1), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(dlist_length(list), 2);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), data[0]);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), data[3]);

        assertEquals(dlist_remove(list, 0), 0);
        assertEquals(dlist_verify(list), 0);

        assertEquals(dlist_length(list), 1);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), data[3]);
    }
}
