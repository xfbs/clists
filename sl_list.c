#include <assert.h>
#include "sl_list.h"

int main()
{
    sl_list *list = list_new(SL_LIST);
    assert(list != 0);

    for(int i = 0; i < 5; i++)
    {
        // create an int
        int *item = (int*)malloc(sizeof(int));
        // append the into the the list
        list_append(list, item);
        // size should now be increased
        assert(list_size(list) == (i+1));
        // int should be at bottom of list
        assert(list_last(list) == item);
        // item should be at pos i
        assert(list_get(list, i) == item);
    }

    list_reset(list, true);
    assert(list_size(list) == 0);
    assert(list_first(list) == 0);
    assert(list_last(list) == 0);
    assert(list_pop(list) == 0);

    for(int i = 0; i < 5; i++)
    {
        list_append(list, 0);
        assert(list_get(list, i) == 0);
    }

    for(int i = 0; i < 5; i++)
    {
        list_set(list, i, malloc(sizeof(int)));
        assert(list_get(list, i));
    }

    list_reset(list, true);
    list_append(list, list);
    assert(list_first(list) == list);
    assert(list_pop(list) == list);
    assert(list_size(list) == 0);

    list_debug(list);

    list_delete(list, false);
}
