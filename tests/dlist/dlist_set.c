#include "helpers.h"

TEST(set_does_not_work_for_empty_list) {
    USING(dlist_new(sizeof(int))) {
        assertEquals(dlist_set(list, 0, NULL), NULL);
        assertEquals(dlist_set(list, 1, NULL), NULL);
        assertEquals(dlist_set(list, 2, NULL), NULL);
        assertEquals(dlist_set(list, 0, &ret), NULL);
        assertEquals(dlist_set(list, 1, &ret), NULL);
        assertEquals(dlist_set(list, 2, &ret), NULL);
    }
}

TEST(set_does_not_work_for_illegal_index) {
    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, NULL), NULL);
        assertEquals(dlist_set(list, 1, NULL), NULL);
        assertEquals(dlist_set(list, 1, &ret), NULL);

        assertNotEquals(dlist_append(list, NULL), NULL);
        assertEquals(dlist_set(list, 2, NULL), NULL);
        assertEquals(dlist_set(list, 2, &ret), NULL);

        assertNotEquals(dlist_append(list, NULL), NULL);
        assertEquals(dlist_set(list, 3, NULL), NULL);
        assertEquals(dlist_set(list, 3, &ret), NULL);
    }
}

TEST(set_with_null_data_returns_null) {
    USING(dlist_new(sizeof(int))) {
        ret = 5;
        assertNotEquals(dlist_append(list, &ret), NULL);
        assertEquals(dlist_set(list, 0, NULL), NULL);

        ret = 6;
        assertNotEquals(dlist_append(list, &ret), NULL);
        assertEquals(dlist_set(list, 0, NULL), NULL);
        assertEquals(dlist_set(list, 1, NULL), NULL);

        ret = 2;
        assertNotEquals(dlist_prepend(list, &ret), NULL);
        assertEquals(dlist_set(list, 0, NULL), NULL);
        assertEquals(dlist_set(list, 1, NULL), NULL);
        assertEquals(dlist_set(list, 2, NULL), NULL);
    }
}

TEST(set_works_with_data) {
    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, NULL), NULL);
        ret = 5;
        assertEquals(*((int*)dlist_set(list, 0, &ret)), ret);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), 5);

        ret = 6;
        assertNotEquals(dlist_append(list, NULL), NULL);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), 5);
        assertEquals(*((int*)dlist_set(list, 1, &ret)), ret);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), 6);

        ret = 2;
        assertNotEquals(dlist_prepend(list, NULL), NULL);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), 5);
        assertEquals(*((int*)dlist_get(list, 2, NULL)), 6);
        assertEquals(*((int*)dlist_set(list, 0, &ret)), ret);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), 2);
    }
}
