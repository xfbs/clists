#include "cu/cu.h"
#include "clists/pvec.h"

static int ret;
static pvec_t *vec;

TEST(purgingEmpty)
{
    vec = pvec_new(0);
    assertNotEquals(vec, NULL);

    ret = pvec_purge(vec);
    assertEquals(ret, 0);

    assertEquals(vec->data, NULL);
    assertEquals(vec->size, 0);
    assertEquals(vec->alloc, 0);

    ret = pvec_free(vec);
    assertEquals(ret, 0);
}

TEST(purgingSingle)
{
    vec = pvec_new(1);
    assertNotEquals(vec, NULL);
    assertTrue(vec->alloc >= 1);

    vec->data[0] = (void*)0x1234;
    vec->size = 1;

    ret = pvec_purge(vec);
    assertEquals(ret, 0);
    assertEquals(vec->data, NULL);
    assertEquals(vec->size, 0);
    assertEquals(vec->alloc, 0);

    ret = pvec_free(vec);
    assertEquals(ret, 0);
}

TEST(purgingReserved)
{
    vec = pvec_new(5);
    assertNotEquals(vec, NULL);
    assertTrue(vec->alloc >= 5);

    ret = pvec_purge(vec);
    assertEquals(ret, 0);
    assertEquals(vec->data, NULL);
    assertEquals(vec->size, 0);
    assertEquals(vec->alloc, 0);

    ret = pvec_free(vec);
    assertEquals(ret, 0);
}
