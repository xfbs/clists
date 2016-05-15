#include "cu/cu.h"
#include "helpers.h"
#include "../../clists/slist.h"

TEST(insert_works_without_data) {
    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_insert(list, 0, NULL), NULL);
        assertEquals(slist_size(list), sizeof(int));
        assertEquals(slist_length(list), 1);
    }

    USING(slist_new(sizeof(int))) {
        // insert at beginning
        assertNotEquals(slist_insert(list, 0, NULL), NULL);
        assertNotEquals(slist_insert(list, 0, NULL), NULL);
        assertNotEquals(slist_insert(list, 0, NULL), NULL);
        assertEquals(slist_size(list), sizeof(int));
        assertEquals(slist_length(list), 3);
    }

    USING(slist_new(sizeof(int))) {
        // insert at end
        assertNotEquals(slist_insert(list, 0, NULL), NULL);
        assertNotEquals(slist_insert(list, 1, NULL), NULL);
        assertNotEquals(slist_insert(list, 2, NULL), NULL);
        assertEquals(slist_size(list), sizeof(int));
        assertEquals(slist_length(list), 3);
    }

    USING(slist_new(sizeof(int))) {
        // insert in middle
        assertNotEquals(slist_insert(list, 0, NULL), NULL);
        assertNotEquals(slist_insert(list, 1, NULL), NULL);
        assertNotEquals(slist_insert(list, 1, NULL), NULL);
        assertNotEquals(slist_insert(list, 1, NULL), NULL);
        assertEquals(slist_size(list), sizeof(int));
        assertEquals(slist_length(list), 4);
    }
}

TEST(insert_returns_null_on_illegal) {
    USING(slist_new(sizeof(int))) {
        assertEquals(slist_insert(list, 4, NULL), NULL);
    }

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_insert(list, 0, NULL), NULL);
        assertNotEquals(slist_insert(list, 0, NULL), NULL);
        assertEquals(slist_length(list), 2);

        assertEquals(slist_insert(list, 3, NULL), NULL);
        assertEquals(slist_insert(list, 5, NULL), NULL);
    }
}

TEST(insert_works_with_data) {
    int one = 1;
    int two = 2;
    int three = 3;
    int four = 4;

    USING(slist_new(sizeof(int))) {
        assertNotEquals(slist_insert(list, 0, &one), NULL);
        assertEquals(slist_size(list), sizeof(int));
        assertEquals(slist_length(list), 1);
        assertNotEquals(slist_get(list, 0, &ret), NULL);
        assertEquals(ret, one);
    }

    USING(slist_new(sizeof(int))) {
        // insert at beginning
        assertNotEquals(slist_insert(list, 0, &three), NULL);
        assertNotEquals(slist_insert(list, 0, &two), NULL);
        assertNotEquals(slist_insert(list, 0, &one), NULL);
        assertEquals(slist_size(list), sizeof(int));
        assertEquals(slist_length(list), 3);

        assertNotEquals(slist_get(list, 0, &ret), NULL);
        assertEquals(ret, one);
        assertNotEquals(slist_get(list, 1, &ret), NULL);
        assertEquals(ret, two);
        assertNotEquals(slist_get(list, 2, &ret), NULL);
        assertEquals(ret, three);
    }

    USING(slist_new(sizeof(int))) {
        // insert at end
        assertNotEquals(slist_insert(list, 0, &one), NULL);
        assertNotEquals(slist_insert(list, 1, &two), NULL);
        assertNotEquals(slist_insert(list, 2, &three), NULL);
        assertEquals(slist_size(list), sizeof(int));
        assertEquals(slist_length(list), 3);

        assertNotEquals(slist_get(list, 0, &ret), NULL);
        assertEquals(ret, one);
        assertNotEquals(slist_get(list, 1, &ret), NULL);
        assertEquals(ret, two);
        assertNotEquals(slist_get(list, 2, &ret), NULL);
        assertEquals(ret, three);
    }

    USING(slist_new(sizeof(int))) {
        // insert in middle
        assertNotEquals(slist_insert(list, 0, &one), NULL);
        assertNotEquals(slist_insert(list, 1, &four), NULL);
        assertNotEquals(slist_insert(list, 1, &three), NULL);
        assertNotEquals(slist_insert(list, 1, &two), NULL);
        assertEquals(slist_size(list), sizeof(int));
        assertEquals(slist_length(list), 4);

        assertNotEquals(slist_get(list, 0, &ret), NULL);
        assertEquals(ret, one);
        assertNotEquals(slist_get(list, 1, &ret), NULL);
        assertEquals(ret, two);
        assertNotEquals(slist_get(list, 2, &ret), NULL);
        assertEquals(ret, three);
        assertNotEquals(slist_get(list, 3, &ret), NULL);
        assertEquals(ret, four);
    }
}
