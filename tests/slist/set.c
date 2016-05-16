#include "cu/cu.h"
#include "helpers.h"
#include "../../clists/slist.h"

TEST(set_does_not_work_for_empty_list) {
    USING(slist_new(sizeof(int))) {
        assertEquals(slist_set(list, 0, NULL), NULL);
        assertEquals(slist_set(list, 1, NULL), NULL);
        assertEquals(slist_set(list, 2, NULL), NULL);
        assertEquals(slist_set(list, 0, &ret), NULL);
        assertEquals(slist_set(list, 1, &ret), NULL);
        assertEquals(slist_set(list, 2, &ret), NULL);
    }
}

TEST(set_does_not_work_for_illegal_index) {
    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, NULL), NULL);
        assertEquals(slist_set(list, 1, NULL), NULL);
        assertEquals(slist_set(list, 1, &ret), NULL);

        assertNotEquals(slist_append(list, NULL), NULL);
        assertEquals(slist_set(list, 2, NULL), NULL);
        assertEquals(slist_set(list, 2, &ret), NULL);

        assertNotEquals(slist_append(list, NULL), NULL);
        assertEquals(slist_set(list, 3, NULL), NULL);
        assertEquals(slist_set(list, 3, &ret), NULL);
    }
}

TEST(set_with_null_data_returns_null) {
    USING(slist_new(sizeof(int))) {
        ret = 5;
        assertNotEquals(slist_append(list, &ret), NULL);
        assertEquals(slist_set(list, 0, NULL), NULL);

        ret = 6;
        assertNotEquals(slist_append(list, &ret), NULL);
        assertEquals(slist_set(list, 0, NULL), NULL);
        assertEquals(slist_set(list, 1, NULL), NULL);

        ret = 2;
        assertNotEquals(slist_prepend(list, &ret), NULL);
        assertEquals(slist_set(list, 0, NULL), NULL);
        assertEquals(slist_set(list, 1, NULL), NULL);
        assertEquals(slist_set(list, 2, NULL), NULL);
    }
}

TEST(set_works_with_data) {
    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, NULL), NULL);
        ret = 5;
        assertEquals(*((int*)slist_set(list, 0, &ret)), ret);
        assertEquals(*((int*)slist_get(list, 0, NULL)), 5);

        ret = 6;
        assertNotEquals(slist_append(list, NULL), NULL);
        assertEquals(*((int*)slist_get(list, 0, NULL)), 5);
        assertEquals(*((int*)slist_set(list, 1, &ret)), ret);
        assertEquals(*((int*)slist_get(list, 1, NULL)), 6);

        ret = 2;
        assertNotEquals(slist_prepend(list, NULL), NULL);
        assertEquals(*((int*)slist_get(list, 1, NULL)), 5);
        assertEquals(*((int*)slist_get(list, 2, NULL)), 6);
        assertEquals(*((int*)slist_set(list, 0, &ret)), ret);
        assertEquals(*((int*)slist_get(list, 0, NULL)), 2);
    }
}
