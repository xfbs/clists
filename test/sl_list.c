#include "sl_list.h"

int main()
{
    sl_list *list = sl_list_new();
    for(int i = 0; i < 5; i++)
    {
        list_append(list, &i);
    }
    list_debug(list);
}
