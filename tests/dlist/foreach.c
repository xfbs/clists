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

TEST(foreachFull)
{
    list = dlist_new();
    assertNotEquals(list, NULL);
    void *dats[] = {(void*)0x1234, (void*)0x2341, (void*)0x3412, (void*)0x4123};

    for(int i = 0; i < 4; i++) {
        ret = dlist_append(list, dats[i]);
        assertEquals(ret, 0);
    }

    ret = 0;
    dlist_foreach(list, data) {
        assertEquals(data, dats[ret]);
        ret++;
    }
    assertEquals(ret, 4);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(foreachBackEmpty)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    dlist_foreach_backwards(list, data) {
        assertTrue(0);
    }

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(foreachBackSingle)
{
    list = dlist_new();
    assertNotEquals(list, NULL);

    ret = dlist_append(list, (void*)0x1234);
    assertEquals(ret, 0);

    ret = 0;
    dlist_foreach_backwards(list, data) {
        ret++;
        assertEquals(data, (void*)0x1234);
    }
    assertEquals(ret, 1);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}

TEST(foreachBackFull)
{
    list = dlist_new();
    assertNotEquals(list, NULL);
    void *dats[] = {(void*)0x1234, (void*)0x2341, (void*)0x3412, (void*)0x4123};

    for(int i = 0; i < 4; i++) {
        ret = dlist_prepend(list, dats[i]);
        assertEquals(ret, 0);
    }

    ret = 0;
    dlist_foreach_backwards(list, data) {
        assertEquals(data, dats[ret]);
        ret++;
    }
    assertEquals(ret, 4);

    ret = dlist_free(list);
    assertEquals(ret, 0);
}
