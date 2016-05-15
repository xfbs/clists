#include "cu/cu.h"
#include "helpers.h"
#include "../../clists/slist.h"

TEST(length_works_with_basic_ops)
{
    USING(slist_new(sizeof(float))) {
        assertEquals(slist_length(list), 0);
        slist_append(list, NULL);
        assertEquals(slist_length(list), 1);
        slist_prepend(list, NULL);
        assertEquals(slist_length(list), 2);
        slist_prepend(list, NULL);
        assertEquals(slist_length(list), 3);
        slist_remove(list, 1);
        assertEquals(slist_length(list), 2);
        slist_pop(list, NULL);
        assertEquals(slist_length(list), 1);
        slist_purge(list);
        assertEquals(slist_length(list), 0);
    }
}

TEST(length_works_manually)
{
    slist_t list;
    slist_init(&list, sizeof(int));
    
    list.length = 5;
    assertEquals(slist_length(&list), 5);

    list.length = 9;
    assertEquals(slist_length(&list), 9);
}
