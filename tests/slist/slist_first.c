#include "helpers.h"

TEST(first_returns_null_on_empty_list)
{
    USING(slist_new(sizeof(int))) {
        assertEquals(slist_first(list), NULL);
    }
}

TEST(first_returns_first_element)
{
    USING(slist_new(sizeof(int))) {
        int num = 5;
        slist_append(list, &num);
        assertEquals(*((int*)slist_first(list)), 5);

        num = 9;
        slist_append(list, &num);
        assertEquals(*((int*)slist_first(list)), 5);

        num = 10;
        slist_append(list, &num);
        assertEquals(*((int*)slist_first(list)), 5);
    }
}

TEST(first_returns_correct_pointer)
{
    USING(slist_new(sizeof(int))) {
        slist_append(list, NULL);
        assertEquals(slist_first(list), list->head->data);

        slist_append(list, NULL);
        assertEquals(slist_first(list), list->head->data);

        slist_append(list, NULL);
        assertEquals(slist_first(list), list->head->data);
    }
}
