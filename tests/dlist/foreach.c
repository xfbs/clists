#include "cu/cu.h"
#include "clists/dlist.h"

static int ret;
static dlist_t *list;

TEST(foreachEmpty)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    dlist_foreach(list, data) {
        assertTrue(0);
    }

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(foreachSingle)
{
    list = dlist_new();
    assertNotEquals(list, NULL);
    
    ret = dlist_append(list, (void*)0x1234);
    assertEquals(ret, 0);

    ret = 0;
    dlist_foreach(list, data) {
        ret += 1;
        assertEquals(data, (void*)0x1234);
    }

    assertEquals(ret, 1);
    ret = dlist_free(list);
    assertEquals(ret, 0);
}
