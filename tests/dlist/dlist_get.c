#include "helpers.h"

TEST(get_does_not_work_for_empty_list) {
    USING(dlist_new(sizeof(int))) {
        assertEquals(dlist_get(list, 0, NULL), NULL);
        assertEquals(dlist_get(list, 1, NULL), NULL);
        assertEquals(dlist_get(list, 2, NULL), NULL);
        assertEquals(dlist_get(list, 0, &ret), NULL);
        assertEquals(dlist_get(list, 1, &ret), NULL);
        assertEquals(dlist_get(list, 2, &ret), NULL);
    }
}

TEST(get_does_not_work_for_illegal_index) {
    USING(dlist_new(sizeof(int))) {
        assertNotEquals(dlist_append(list, NULL), NULL);
        assertEquals(dlist_get(list, 1, NULL), NULL);
        assertEquals(dlist_get(list, 1, &ret), NULL);

        assertNotEquals(dlist_append(list, NULL), NULL);
        assertEquals(dlist_get(list, 2, NULL), NULL);
        assertEquals(dlist_get(list, 2, &ret), NULL);

        assertNotEquals(dlist_append(list, NULL), NULL);
        assertEquals(dlist_get(list, 3, NULL), NULL);
        assertEquals(dlist_get(list, 3, &ret), NULL);
    }
}

TEST(get_works_without_data) {
    USING(dlist_new(sizeof(int))) {
        ret = 5;
        assertNotEquals(dlist_append(list, &ret), NULL);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), 5);

        ret = 6;
        assertNotEquals(dlist_append(list, &ret), NULL);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), 5);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), 6);

        ret = 2;
        assertNotEquals(dlist_prepend(list, &ret), NULL);
        assertEquals(*((int*)dlist_get(list, 0, NULL)), 2);
        assertEquals(*((int*)dlist_get(list, 1, NULL)), 5);
        assertEquals(*((int*)dlist_get(list, 2, NULL)), 6);
    }
}

TEST(get_works_with_data) {
    USING(dlist_new(sizeof(int))) {
        ret = 4;
        assertNotEquals(dlist_append(list, &ret), NULL);
        assertNotEquals(dlist_get(list, 0, &ret), NULL);
        assertEquals(ret, 4);

        ret = 6;
        assertNotEquals(dlist_append(list, &ret), NULL);
        assertNotEquals(dlist_get(list, 0, &ret), NULL);
        assertEquals(ret, 4);
        assertNotEquals(dlist_get(list, 1, &ret), NULL);
        assertEquals(ret, 6);

        ret = 9;
        assertNotEquals(dlist_prepend(list, &ret), NULL);
        assertNotEquals(dlist_get(list, 0, &ret), NULL);
        assertEquals(ret, 9);
        assertNotEquals(dlist_get(list, 1, &ret), NULL);
        assertEquals(ret, 4);
        assertNotEquals(dlist_get(list, 2, &ret), NULL);
        assertEquals(ret, 6);
    }
}
