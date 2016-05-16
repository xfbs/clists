#include "helpers.h"

TEST(size_works_with_slist_new)
{
    USING(slist_new(sizeof(float))) {
        assertEquals(slist_size(list), sizeof(float));
    }

    USING(slist_new(sizeof(double))) {
        assertEquals(slist_size(list), sizeof(double));
    }
}

TEST(size_works_with_slist_init)
{
    slist_t list;
    slist_init(&list, sizeof(float));
    assertEquals(slist_size(&list), sizeof(float));

    slist_init(&list, sizeof(double));
    assertEquals(slist_size(&list), sizeof(double));
}

TEST(size_works_manually)
{
    slist_t list;
    slist_init(&list, sizeof(int));
    
    list.size = 5;
    assertEquals(slist_size(&list), 5);

    list.size = 9;
    assertEquals(slist_size(&list), 9);
}
