#include "cu/cu.h"
#include "clists/dlist.h"

static int ret;
static void *data;
static dlist_t *list;

TEST(gettingEmpty)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    data = dlist_get(list, 0);
    assertEquals(data, NULL);

    data = dlist_get(list, 1);
    assertEquals(data, NULL);
    
    data = dlist_get(list, 2);
    assertEquals(data, NULL);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(gettingSingle)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_append(list, (void*)0x1234);
    assertEquals(ret, 0);
    
    data = dlist_get(list, 0);
    assertEquals(data, (void*)0x1234);

    data = dlist_get(list, 1);
    assertEquals(data, NULL);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(gettingFull)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_append(list, (void*)0x1234);
    assertEquals(ret, 0);
    ret = dlist_append(list, (void*)0x2341);
    assertEquals(ret, 0);

    data = dlist_get(list, 0);
    assertEquals(data, (void*)0x1234);
    data = dlist_get(list, 1);
    assertEquals(data, (void*)0x2341);
    data = dlist_get(list, 2);
    assertEquals(data, NULL);

    ret = dlist_append(list, (void*)0x3412);
    assertEquals(ret, 0);

    data = dlist_get(list, 2);
    assertEquals(data, (void*)0x3412);
    
    ret = dlist_free(list);
    assertEquals(ret, 0);
}
