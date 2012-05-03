#include "cu/cu.h"
#include "clists/pvec.h"

static int ret;
static pvec_t *vec;

TEST(reservingEmpty)
{
    vec = pvec_new(0);
    assertNotEquals(vec, NULL);

    ret = pvec_reserve(vec, 0);
    assertEquals(ret, 0);
    assertEquals(vec->data, NULL);
    assertEquals(vec->size, 0);
    assertEquals(vec->alloc, 0);

    ret = pvec_free(vec);
    assertEquals(ret, 0);
}

TEST(reservingMore)
{
    vec = pvec_new(0);
    assertNotEquals(vec, NULL);

    for(int i = 1; i <= 10; i++) {
        ret = pvec_reserve(vec, i);
        assertEquals(ret, 0);
        assertNotEquals(vec->data, NULL);
        assertEquals(vec->size, 0);
        assertTrue(vec->alloc >= i);
    }

    ret = pvec_free(vec);
    assertEquals(ret, 0);
}

TEST(reservingLess)
{
    vec = pvec_new(0);
    assertNotEquals(vec, NULL);

    for(int i = 10; i > 0; i--) {
        ret = pvec_reserve(vec, i);
        assertEquals(ret, 0);
        assertNotEquals(vec->data, NULL);
        assertEquals(vec->size, 0);
        assertTrue(vec->alloc >= i);
    }

    ret = pvec_free(vec);
    assertEquals(ret, 0);
}
