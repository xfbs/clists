#include "cu/cu.h"
#include "clists/slist.h"

static int ret;
static void *data;
static slist_t *list;

TEST(gettingEmpty)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    data = slist_get(list, 0);
    assertEquals(data, NULL);

    data = slist_get(list, 1);
    assertEquals(data, NULL);
    
    data = slist_get(list, 2);
    assertEquals(data, NULL);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(gettingSingle)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_append(list, (void*)0x1234);
    assertEquals(ret, 0);
    
    data = slist_get(list, 0);
    assertEquals(data, (void*)0x1234);

    data = slist_get(list, 1);
    assertEquals(data, NULL);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(gettingFull)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_append(list, (void*)0x1234);
    assertEquals(ret, 0);
    ret = slist_append(list, (void*)0x2341);
    assertEquals(ret, 0);

    data = slist_get(list, 0);
    assertEquals(data, (void*)0x1234);
    data = slist_get(list, 1);
    assertEquals(data, (void*)0x2341);
    data = slist_get(list, 2);
    assertEquals(data, NULL);

    ret = slist_append(list, (void*)0x3412);
    assertEquals(ret, 0);

    data = slist_get(list, 2);
    assertEquals(data, (void*)0x3412);
    
    ret = slist_free(list);
    assertEquals(ret, 0);
}
