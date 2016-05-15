#include "cu/cu.h"
#include "helpers.h"
#include "../../clists/slist.h"

TEST(last_returns_null_on_empty_list)
{
    USING(slist_new(sizeof(int))) {
        assertEquals(slist_last(list), NULL);
    }
}

TEST(last_returns_last_element)
{
    USING(slist_new(sizeof(int))) {
        int num = 5;
        slist_append(list, &num);
        assertEquals(*((int*)slist_last(list)), 5);

        num = 9;
        slist_append(list, &num);
        assertEquals(*((int*)slist_last(list)), 9);

        num = 10;
        slist_append(list, &num);
        assertEquals(*((int*)slist_last(list)), 10);
    }
}

TEST(last_returns_correct_pointer)
{
    USING(slist_new(sizeof(int))) {
        slist_append(list, NULL);
        assertEquals(slist_last(list), list->tail->data);

        slist_append(list, NULL);
        assertEquals(slist_last(list), list->tail->data);

        slist_append(list, NULL);
        assertEquals(slist_last(list), list->tail->data);
    }
}
