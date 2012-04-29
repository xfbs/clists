#include "cu/cu.h"
#include "clists/slist.h"

static int ret;
static slist_t *lista;
static slist_t *listb;

TEST(comparingEmpty)
{
    lista = slist_new();
    assertNotEquals(lista, NULL);
    listb = slist_new();
    assertNotEquals(listb, NULL);

    ret = slist_equal(lista, listb);
    assertEquals(ret, 1);

    ret = slist_equal(listb, lista);
    assertEquals(ret, 1);

    ret = slist_free(lista);
    assertEquals(ret, 0);
    ret = slist_free(listb);
    assertEquals(ret, 0);
}

TEST(comparingSingle)
{
    lista = slist_new();
    assertNotEquals(lista, NULL);
    listb = slist_new();
    assertNotEquals(listb, NULL);

    ret = slist_append(lista, (void*)0x1234);
    assertEquals(ret, 0);
    ret = slist_equal(lista, listb);
    assertEquals(ret, 0);
    ret = slist_equal(listb, lista);
    assertEquals(ret, 0);

    memcpy(listb, lista, sizeof(slist_t));
    ret = slist_equal(lista, listb);
    assertEquals(ret, 1);
    ret = slist_equal(listb, lista);
    assertEquals(ret, 1);

    memset(listb, 0, sizeof(slist_t));
    ret = slist_append(listb, (void*)0x1234);
    assertEquals(ret, 0);
    ret = slist_equal(lista, listb);
    assertEquals(ret, 1);
    ret = slist_equal(listb, lista);
    assertEquals(ret, 1);

    ret = slist_set(lista, 0, (void*)0x2341);
    assertEquals(ret, 0);
    ret = slist_equal(lista, listb);
    assertEquals(ret, 0);
    ret = slist_equal(listb, lista);
    assertEquals(ret, 0);

    ret = slist_free(lista);
    assertEquals(ret, 0);
    ret = slist_free(listb);
    assertEquals(ret, 0);
}

TEST(comparingDouble)
{
    lista = slist_new();
    assertNotEquals(lista, NULL);
    listb = slist_new();
    assertNotEquals(listb, NULL);

    ret = slist_append(lista, (void*)0x1234);
    assertEquals(ret, 0);
    ret = slist_append(listb, (void*)0x1234);
    assertEquals(ret, 0);
    ret = slist_append(lista, (void*)0x2341);
    assertEquals(ret, 0);
    ret = slist_append(listb, (void*)0x2341);
    assertEquals(ret, 0);

    ret = slist_equal(lista, listb);
    assertEquals(ret, 1);
    ret = slist_equal(listb, lista);
    assertEquals(ret, 1);

    ret = slist_set(lista, 1, (void*)0x2342);
    assertEquals(ret, 0);
    ret = slist_equal(lista, listb);
    assertEquals(ret, 0);
    ret = slist_equal(listb, lista);
    assertEquals(ret, 0);

    ret = slist_free(lista);
    assertEquals(ret, 0);
    ret = slist_free(listb);
    assertEquals(ret, 0);
}

TEST(comparingFull)
{
    lista = slist_new();
    assertNotEquals(lista, NULL);
    listb = slist_new();
    assertNotEquals(listb, NULL);

    ret = slist_append(lista, (void*)0x1234);
    assertEquals(ret, 0);
    ret = slist_append(listb, (void*)0x1234);
    assertEquals(ret, 0);
    ret = slist_append(lista, (void*)0x2341);
    assertEquals(ret, 0);
    ret = slist_append(listb, (void*)0x2341);
    assertEquals(ret, 0);
    ret = slist_append(lista, (void*)0x3412);
    assertEquals(ret, 0);
    ret = slist_append(listb, (void*)0x3412);
    assertEquals(ret, 0);
    
    ret = slist_equal(lista, listb);
    assertEquals(ret, 1);
    ret = slist_equal(listb, lista);
    assertEquals(ret, 1);

    ret = slist_set(listb, 2, (void*)0x2341);
    assertEquals(ret, 0);
    ret = slist_equal(lista, listb);
    assertEquals(ret, 0);
    ret = slist_equal(listb, lista);
    assertEquals(ret, 0);

    ret = slist_free(lista);
    assertEquals(ret, 0);
    ret = slist_free(listb);
    assertEquals(ret, 0);
}
