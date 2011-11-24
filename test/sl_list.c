#include <assert.h>
#include "sl_list.h"

int main()
{
    sl_list *list = sl_list_new();
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

}
