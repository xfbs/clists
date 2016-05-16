#include "cu/cu.h"
#include "helpers.h"
#include "../../clists/slist.h"

TEST(get_does_not_work_for_empty_list) {
    USING(slist_new(sizeof(int))) {
        assertEquals(slist_get(list, 0, NULL), NULL);
        assertEquals(slist_get(list, 1, NULL), NULL);
        assertEquals(slist_get(list, 2, NULL), NULL);
        assertEquals(slist_get(list, 0, &ret), NULL);
        assertEquals(slist_get(list, 1, &ret), NULL);
        assertEquals(slist_get(list, 2, &ret), NULL);
    }
}

TEST(get_does_not_work_for_illegal_index) {
    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, NULL), NULL);
        assertEquals(slist_get(list, 1, NULL), NULL);
        assertEquals(slist_get(list, 1, &ret), NULL);

        assertNotEquals(slist_append(list, NULL), NULL);
        assertEquals(slist_get(list, 2, NULL), NULL);
        assertEquals(slist_get(list, 2, &ret), NULL);

        assertNotEquals(slist_append(list, NULL), NULL);
        assertEquals(slist_get(list, 3, NULL), NULL);
        assertEquals(slist_get(list, 3, &ret), NULL);
    }
}

TEST(get_works_without_data) {
    USING(slist_new(sizeof(int))) {
        ret = 5;
        assertNotEquals(slist_append(list, &ret), NULL);
        assertEquals(*((int*)slist_get(list, 0, NULL)), 5);

        ret = 6;
        assertNotEquals(slist_append(list, &ret), NULL);
        assertEquals(*((int*)slist_get(list, 0, NULL)), 5);
        assertEquals(*((int*)slist_get(list, 1, NULL)), 6);

        ret = 2;
        assertNotEquals(slist_prepend(list, &ret), NULL);
        assertEquals(*((int*)slist_get(list, 0, NULL)), 2);
        assertEquals(*((int*)slist_get(list, 1, NULL)), 5);
        assertEquals(*((int*)slist_get(list, 2, NULL)), 6);
    }
}

TEST(get_works_with_data) {
    USING(slist_new(sizeof(int))) {
        ret = 4;
        assertNotEquals(slist_append(list, &ret), NULL);
        assertNotEquals(slist_get(list, 0, &ret), NULL);
        assertEquals(ret, 4);

        ret = 6;
        assertNotEquals(slist_append(list, &ret), NULL);
        assertNotEquals(slist_get(list, 0, &ret), NULL);
        assertEquals(ret, 4);
        assertNotEquals(slist_get(list, 1, &ret), NULL);
        assertEquals(ret, 6);

        ret = 9;
        assertNotEquals(slist_prepend(list, &ret), NULL);
        assertNotEquals(slist_get(list, 0, &ret), NULL);
        assertEquals(ret, 9);
        assertNotEquals(slist_get(list, 1, &ret), NULL);
        assertEquals(ret, 4);
        assertNotEquals(slist_get(list, 2, &ret), NULL);
        assertEquals(ret, 6);
    }
}
