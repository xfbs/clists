#include "cu/cu.h"
#include "clists/pvec.h"

TEST(heapAlloc)
{
    pvec_t *vec = pvec_new(0);
    assertNotEquals(vec, NULL);
    assertEquals(vec->size, 0);
    assertEquals(vec->alloc, 0);
    assertEquals(vec->data, NULL);
    free(vec);
}

TEST(allocSize)
{
    pvec_t *vec = pvec_new(5);
    assertNotEquals(vec, NULL);
    assertEquals(vec->size, 0);
    assertNotEquals(vec->alloc, 0);
    assertNotEquals(vec->data, NULL);
    free(vec->data);
    free(vec);
}

TEST(heapInit)
{
    pvec_t *vec = malloc(sizeof(pvec_t));
    assertNotEquals(vec, NULL);
    assertEquals(pvec_init(vec), 0);
    assertEquals(vec->size, 0);
    assertEquals(vec->alloc, 0);
    assertEquals(vec->data, NULL);
    free(vec);
}

TEST(stackInit)
{
    pvec_t vec;
    assertEquals(pvec_init(&vec), 0);
    assertEquals(vec.size, 0);
    assertEquals(vec.alloc, 0);
    assertEquals(vec.data, NULL);
}
