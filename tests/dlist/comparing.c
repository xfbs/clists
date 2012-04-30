#include "cu/cu.h"
#include "clists/dlist.h"

static int ret;
static dlist_t *lista;
static dlist_t *listb;

TEST(comparingEmpty)
{
    lista = dlist_new();
    assertNotEquals(lista, NULL);
    listb = dlist_new();
    assertNotEquals(listb, NULL);

    ret = dlist_equal(lista, listb);
    assertEquals(ret, 1);

    ret = dlist_equal(listb, lista);
    assertEquals(ret, 1);

    ret = dlist_free(lista);
    assertEquals(ret, 0);
    ret = dlist_free(listb);
    assertEquals(ret, 0);
}

TEST(comparingSingle)
{
    lista = dlist_new();
    assertNotEquals(lista, NULL);
    listb = dlist_new();
    assertNotEquals(listb, NULL);

    ret = dlist_append(lista, (void*)0x1234);
    assertEquals(ret, 0);
    ret = dlist_equal(lista, listb);
    assertEquals(ret, 0);
    ret = dlist_equal(listb, lista);
    assertEquals(ret, 0);

    memcpy(listb, lista, sizeof(dlist_t));
    ret = dlist_equal(lista, listb);
    assertEquals(ret, 1);
    ret = dlist_equal(listb, lista);
    assertEquals(ret, 1);

    memset(listb, 0, sizeof(dlist_t));
    ret = dlist_append(listb, (void*)0x1234);
    assertEquals(ret, 0);
    ret = dlist_equal(lista, listb);
    assertEquals(ret, 1);
    ret = dlist_equal(listb, lista);
    assertEquals(ret, 1);

    ret = dlist_set(lista, 0, (void*)0x2341);
    assertEquals(ret, 0);
    ret = dlist_equal(lista, listb);
    assertEquals(ret, 0);
    ret = dlist_equal(listb, lista);
    assertEquals(ret, 0);

    ret = dlist_free(lista);
    assertEquals(ret, 0);
    ret = dlist_free(listb);
    assertEquals(ret, 0);
}

TEST(comparingDouble)
{
    lista = dlist_new();
    assertNotEquals(lista, NULL);
    listb = dlist_new();
    assertNotEquals(listb, NULL);

    ret = dlist_append(lista, (void*)0x1234);
    assertEquals(ret, 0);
    ret = dlist_append(listb, (void*)0x1234);
    assertEquals(ret, 0);
    ret = dlist_append(lista, (void*)0x2341);
    assertEquals(ret, 0);
    ret = dlist_append(listb, (void*)0x2341);
    assertEquals(ret, 0);

    ret = dlist_equal(lista, listb);
    assertEquals(ret, 1);
    ret = dlist_equal(listb, lista);
    assertEquals(ret, 1);

    ret = dlist_set(lista, 1, (void*)0x2342);
    assertEquals(ret, 0);
    ret = dlist_equal(lista, listb);
    assertEquals(ret, 0);
    ret = dlist_equal(listb, lista);
    assertEquals(ret, 0);

    ret = dlist_free(lista);
    assertEquals(ret, 0);
    ret = dlist_free(listb);
    assertEquals(ret, 0);
}

TEST(comparingFull)
{
    lista = dlist_new();
    assertNotEquals(lista, NULL);
    listb = dlist_new();
    assertNotEquals(listb, NULL);

    ret = dlist_append(lista, (void*)0x1234);
    assertEquals(ret, 0);
    ret = dlist_append(listb, (void*)0x1234);
    assertEquals(ret, 0);
    ret = dlist_append(lista, (void*)0x2341);
    assertEquals(ret, 0);
    ret = dlist_append(listb, (void*)0x2341);
    assertEquals(ret, 0);
    ret = dlist_append(lista, (void*)0x3412);
    assertEquals(ret, 0);
    ret = dlist_append(listb, (void*)0x3412);
    assertEquals(ret, 0);
    
    ret = dlist_equal(lista, listb);
    assertEquals(ret, 1);
    ret = dlist_equal(listb, lista);
    assertEquals(ret, 1);

    ret = dlist_set(listb, 2, (void*)0x2341);
    assertEquals(ret, 0);
    ret = dlist_equal(lista, listb);
    assertEquals(ret, 0);
    ret = dlist_equal(listb, lista);
    assertEquals(ret, 0);

    ret = dlist_free(lista);
    assertEquals(ret, 0);
    ret = dlist_free(listb);
    assertEquals(ret, 0);
}
