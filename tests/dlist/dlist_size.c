#include "helpers.h"

TEST(size_works_with_dlist_new)
{
    USING(dlist_new(sizeof(float))) {
        assertEquals(dlist_size(list), sizeof(float));
    }

    USING(dlist_new(sizeof(double))) {
        assertEquals(dlist_size(list), sizeof(double));
    }
}

TEST(size_works_with_dlist_init)
{
    dlist_t list;
    dlist_init(&list, sizeof(float));
    assertEquals(dlist_size(&list), sizeof(float));

    dlist_init(&list, sizeof(double));
    assertEquals(dlist_size(&list), sizeof(double));
}

TEST(size_works_manually)
{
    dlist_t list;
    dlist_init(&list, sizeof(int));
    
    list.size = 5;
    assertEquals(dlist_size(&list), 5);

    list.size = 9;
    assertEquals(dlist_size(&list), 9);
}
