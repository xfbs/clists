#include "cu/cu.h"
#include "helpers.h"
#include "../../clists/slist.h"

TEST(remove_on_empty_list_does_not_work) {
    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_remove(list, 0), 0);
    }

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_remove(list, 1), 0);
    }

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_remove(list, 2), 0);
    }
}

TEST(remove_in_beginning_works) {
    int data[] = {32422, 214235, 23452512, -3432212};
    
    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, &data[0]), NULL);
        assertNotEquals(slist_append(list, &data[1]), NULL);
        assertNotEquals(slist_append(list, &data[2]), NULL);
        assertNotEquals(slist_append(list, &data[3]), NULL);

        assertEquals(slist_length(list), 4);
        assertEquals(*((int*)slist_first(list)), data[0]);

        assertEquals(slist_remove(list, 0), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(slist_length(list), 3);
        assertEquals(*((int*)slist_first(list)), data[1]);

        assertEquals(slist_remove(list, 0), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(slist_length(list), 2);
        assertEquals(*((int*)slist_first(list)), data[2]);

        assertEquals(slist_remove(list, 0), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(slist_length(list), 1);
        assertEquals(*((int*)slist_first(list)), data[3]);

        assertEquals(slist_remove(list, 0), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(slist_length(list), 0);
        assertEquals(slist_first(list), NULL);

        assertNotEquals(slist_remove(list, 0), 0);
    }
}

TEST(remove_at_end_works) {
    int data[] = {32422, 214235, 23452512, -3432212};
    
    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, &data[0]), NULL);
        assertNotEquals(slist_append(list, &data[1]), NULL);
        assertNotEquals(slist_append(list, &data[2]), NULL);
        assertNotEquals(slist_append(list, &data[3]), NULL);

        assertEquals(slist_length(list), 4);
        assertEquals(*((int*)slist_last(list)), data[3]);

        assertNotEquals(slist_remove(list, 4), 0);
        assertEquals(slist_remove(list, 3), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(slist_length(list), 3);
        assertEquals(*((int*)slist_last(list)), data[2]);

        assertNotEquals(slist_remove(list, 3), 0);
        assertEquals(slist_remove(list, 2), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(slist_length(list), 2);
        assertEquals(*((int*)slist_last(list)), data[1]);

        assertNotEquals(slist_remove(list, 2), 0);
        assertEquals(slist_remove(list, 1), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(slist_length(list), 1);
        assertEquals(*((int*)slist_last(list)), data[0]);

        assertNotEquals(slist_remove(list, 1), 0);
        assertEquals(slist_remove(list, 0), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(slist_length(list), 0);
        assertEquals(slist_last(list), NULL);

        assertNotEquals(slist_remove(list, 0), 0);
    }
}

TEST(remove_in_middle_works) {
    int data[] = {32422, 214235, 23452512, -3432212};
    
    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, &data[0]), NULL);
        assertNotEquals(slist_append(list, &data[1]), NULL);
        assertNotEquals(slist_append(list, &data[2]), NULL);
        assertNotEquals(slist_append(list, &data[3]), NULL);

        assertEquals(slist_length(list), 4);
        assertEquals(*((int*)slist_get(list, 2, NULL)), data[2]);

        assertEquals(slist_remove(list, 2), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(slist_length(list), 3);
        assertEquals(*((int*)slist_get(list, 1, NULL)), data[1]);
        assertEquals(*((int*)slist_get(list, 2, NULL)), data[3]);

        assertEquals(slist_remove(list, 1), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(slist_length(list), 2);
        assertEquals(*((int*)slist_get(list, 0, NULL)), data[0]);
        assertEquals(*((int*)slist_get(list, 1, NULL)), data[3]);

        assertEquals(slist_remove(list, 0), 0);
        assertEquals(slist_verify(list), 0);

        assertEquals(slist_length(list), 1);
        assertEquals(*((int*)slist_get(list, 0, NULL)), data[3]);
    }
}
