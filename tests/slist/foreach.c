#include "cu/cu.h"
#include "clists/slist.h"

static int ret;
static slist_t *list;

TEST(foreachEmpty)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    slist_foreach(list, data) {
        assertTrue(0);
    }

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(foreachSingle)
{
    list = slist_new();
    assertNotEquals(list, NULL);

    ret = slist_append(list, (void*)0x1234);
    assertEquals(ret, 0);

    ret = 0;
    slist_foreach(list, data) {
        ret = 1;
        assertEquals(data, (void*)0x1234);
    }

    assertEquals(ret, 1);
    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(foreachFull)
{
    list = slist_new();
    assertNotEquals(list, NULL);
    void *dats[] = {(void*)0x1234, (void*)0x2341, (void*)0x3412, (void*)0x4123};

    for(int i = 0; i < 4; i++) {
        ret = slist_append(list, dats[i]);
        assertEquals(ret, 0);
    }
    
    ret = 0;
    slist_foreach(list, data) {
        assertEquals(data, dats[ret]);
        ret++;
    }

    assertEquals(ret, 4);
    ret = slist_free(list);
    assertEquals(ret, 0);
}

