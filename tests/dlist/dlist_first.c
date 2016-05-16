#include "helpers.h"

TEST(first_returns_null_on_empty_list)
{
    USING(dlist_new(sizeof(int))) {
        assertEquals(dlist_first(list), NULL);
    }
}

TEST(first_returns_first_element)
{
    USING(dlist_new(sizeof(int))) {
        int num = 5;
        dlist_append(list, &num);
        assertEquals(*((int*)dlist_first(list)), 5);

        num = 9;
        dlist_append(list, &num);
        assertEquals(*((int*)dlist_first(list)), 5);

        num = 10;
        dlist_append(list, &num);
        assertEquals(*((int*)dlist_first(list)), 5);
    }
}

TEST(first_returns_correct_pointer)
{
    USING(dlist_new(sizeof(int))) {
        dlist_append(list, NULL);
        assertEquals(dlist_first(list), list->head->data);

        dlist_append(list, NULL);
        assertEquals(dlist_first(list), list->head->data);

        dlist_append(list, NULL);
        assertEquals(dlist_first(list), list->head->data);
    }
}
