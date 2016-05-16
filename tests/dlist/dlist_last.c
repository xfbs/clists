#include "helpers.h"

TEST(last_returns_null_on_empty_list)
{
    USING(dlist_new(sizeof(int))) {
        assertEquals(dlist_last(list), NULL);
    }
}

TEST(last_returns_last_element)
{
    USING(dlist_new(sizeof(int))) {
        int num = 5;
        dlist_append(list, &num);
        assertEquals(*((int*)dlist_last(list)), 5);

        num = 9;
        dlist_append(list, &num);
        assertEquals(*((int*)dlist_last(list)), 9);

        num = 10;
        dlist_append(list, &num);
        assertEquals(*((int*)dlist_last(list)), 10);
    }
}

TEST(last_returns_correct_pointer)
{
    USING(dlist_new(sizeof(int))) {
        dlist_append(list, NULL);
        assertEquals(dlist_last(list), list->tail->data);

        dlist_append(list, NULL);
        assertEquals(dlist_last(list), list->tail->data);

        dlist_append(list, NULL);
        assertEquals(dlist_last(list), list->tail->data);
    }
}
