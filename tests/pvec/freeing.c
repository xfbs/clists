#include "cu/cu.h"
#include "clists/pvector.h"

static int ret;
static pvec_t *vec;

TEST(freeingEmpty)
{
    vec = pvec_new(0);
    assertNotEquals(vec, NULL);

    ret = pvec_free(vec);
    assertEquals(ret, 0);
}

TEST(freeingSingle)
{
    vec = pvec_new(1);
    assertNotEquals(vec, NULL);

    ret = pvec_free(vec);
    assertEquals(ret, 0);

    vec = pvec_new(1);
    assertNotEquals(vec, NULL);
    vec->size++;

    ret = pvec_free(vec);
    assertEquals(ret, 0);
}

TEST(freeingFull)
{
    vec = pvec_new(5);
    assertNotEquals(vec, NULL);

    vec->size = 5;
    ret = pvec_free(vec);
    assertEquals(ret, 0);
}
