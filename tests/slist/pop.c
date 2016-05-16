#include "cu/cu.h"
#include "helpers.h"
#include "../../clists/slist.h"

TEST(pop_works_on_empty_list) {
    USING(slist_new(sizeof(int))) {
        assertEquals(slist_pop(list, NULL), NULL);
    }

    USING(slist_new(sizeof(int))) {
        assertEquals(slist_pop(list, &ret), NULL);
    }
}

TEST(pop_works_on_single_list) {
    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, &ret), NULL);
        assertEquals(slist_pop(list, NULL), NULL);
        assertEquals(slist_length(list), 0);
        assertEquals(slist_size(list), sizeof(int));
    }

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_append(list, &ret), NULL);
        assertEquals(slist_pop(list, &ret), &ret);
        assertEquals(slist_length(list), 0);
        assertEquals(slist_size(list), sizeof(int));
    }
}

TEST(pop_works_on_full_list) {
    USING(slist_new(sizeof(int))) {
        ret = 1;
        assertNotEquals(slist_append(list, &ret), NULL);
        ret = 2;
        assertNotEquals(slist_append(list, &ret), NULL);
        ret = 3;
        assertNotEquals(slist_append(list, &ret), NULL);

        assertNotEquals(slist_get(list, 0, &ret), NULL);
        assertEquals(ret, 1);

        assertEquals(slist_pop(list, &ret), &ret);
        assertEquals(slist_length(list), 2);
        assertEquals(slist_size(list), sizeof(int));
        assertEquals(slist_verify(list), 0);

        assertNotEquals(slist_get(list, 0, &ret), NULL);
        assertEquals(ret, 2);

        assertEquals(slist_pop(list, &ret), &ret);
        assertEquals(slist_length(list), 1);
        assertEquals(slist_size(list), sizeof(int));
        assertEquals(slist_verify(list), 0);

        assertNotEquals(slist_get(list, 0, &ret), NULL);
        assertEquals(ret, 3);

        assertEquals(slist_pop(list, &ret), &ret);
        assertEquals(slist_length(list), 0);
        assertEquals(slist_size(list), sizeof(int));
        assertEquals(slist_verify(list), 0);
    }
}
