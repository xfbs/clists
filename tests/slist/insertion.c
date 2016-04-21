/* tests for insertions to the list
 */

#include "cu/cu.h"
#include "clists/slist.h"
int ret;

TEST(appendingSingle)
{
    // tests if appending works
    int data = 0xDECAFBAD;

    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    // add single node
    ret = slist_append(list, &data);
    assertEquals(ret, 0);

    // verify the nodes exist
    assertEquals(list->size, sizeof(int));
    assertEquals(list->length, 1);
    assertNotEquals(list->head, NULL);
    assertEquals(list->head, list->tail);
    assertEquals(memcmp(&list->head->data[0], &data, sizeof(int)), 0);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(appendingMultiple)
{
    // tests if appending works
    int data[] = {0xDECAFBAD, 0xCAFEBABE, 0xC0DEC0DE, 0};

    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    // add nodes
    for(int i = 0; data[i] != 0; i++) {
        ret = slist_append(list, &data[i]);
        assertEquals(ret, 0);
    }

    // verify those exist too
    assertEquals(list->size, sizeof(int));
    assertEquals(list->length, 3);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(memcmp(&list->head->data[0], &data[0], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->data[0], &data[1], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->next->data[0], &data[2], sizeof(int)), 0);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(prependingSingle)
{
    // tests if prepending works
    int data = 0xDECAFBAD;

    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    // add single node
    ret = slist_prepend(list, &data);
    assertEquals(ret, 0);

    // verify the nodes exist
    assertEquals(list->size, sizeof(int));
    assertEquals(list->length, 1);
    assertNotEquals(list->head, NULL);
    assertEquals(list->head, list->tail);
    assertEquals(memcmp(&list->head->data[0], &data, sizeof(int)), 0);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(prependingMultiple)
{
    // tests if prepending works
    int data[] = {0xDECAFBAD, 0xCAFEBABE, 0xC0DEC0DE, 0};

    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    // add nodes
    for(int i = 0; data[i] != 0; i++) {
        ret = slist_prepend(list, &data[i]);
        assertEquals(ret, 0);
    }

    // verify those exist too
    assertEquals(list->size, sizeof(int));
    assertEquals(list->length, 3);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(memcmp(&list->head->data[0], &data[2], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->data[0], &data[1], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->next->data[0], &data[0], sizeof(int)), 0);

    ret = slist_free(list);
    assertEquals(ret, 0);
}


