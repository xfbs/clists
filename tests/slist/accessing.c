/* tests for accessing linked lists's data
 */

#include "cu/cu.h"
#include "clists/slist.h"
int ret;

TEST(settingData)
{
    // test setting data
    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    int data[] = {0xDECAFBAD, 0xCAFEBABE, 0xC0DEC0DE, 0};

    // fill 'er up...
    for(int i = 0; data[i] != 0; i++) {
        ret = slist_append(list, &data[i]);
        assertEquals(ret, 0);
    }

    int newdata = 0xABCD1234;

    // overwrite middle element
    ret = slist_set(list, 1, &newdata);
    assertEquals(ret, 0);

    // check if it worked
    assertEquals(list->size, sizeof(int));
    assertEquals(list->length, 3);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(memcmp(&list->head->data[0], &data[0], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->data[0], &newdata, sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->next->data[0], &data[2], sizeof(int)), 0);
    
    // overwrite first element
    ret = slist_set(list, 0, &newdata);
    assertEquals(ret, 0);

    // check if it worked
    assertEquals(list->size, sizeof(int));
    assertEquals(list->length, 3);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(memcmp(&list->head->data[0], &newdata, sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->data[0], &newdata, sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->next->data[0], &data[2], sizeof(int)), 0);

    // overwrite last element
    ret = slist_set(list, 2, &newdata);
    assertEquals(ret, 0);

    // check if it worked
    assertEquals(list->size, sizeof(int));
    assertEquals(list->length, 3);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(memcmp(&list->head->data[0], &newdata, sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->data[0], &newdata, sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->next->data[0], &newdata, sizeof(int)), 0);

    // free list
    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(settingIllegal)
{
    // test setting illegal data
    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    int data[] = {0xDECAFBAD, 0xCAFEBABE, 0xC0DEC0DE, 0};
    int newdata = 0xABCD1234;

    // overwrite element of empty list
    ret = slist_set(list, 0, &newdata);
    assertNotEquals(ret, 0);

    // make sure list survived it
    assertEquals(list->length, 0);
    assertEquals(list->head, list->tail);
    assertEquals(list->head, NULL);
    assertEquals(list->size, sizeof(int));

    // fill 'er up...
    for(int i = 0; data[i] != 0; i++) {
        ret = slist_append(list, &data[i]);
        assertEquals(ret, 0);
    }

    // overwrite middle element
    ret = slist_set(list, 5, &newdata);
    assertNotEquals(ret, 0);

    // make sure list is fine
    assertEquals(list->length, 3);
    assertEquals(list->size, sizeof(int));
    assertEquals(list->head->next->next, list->tail);

    // free list
    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(gettingData)
{
}

TEST(gettingIllegal)
{
}

TEST(poppingData)
{
}

TEST(poppingEmpty)
{
}
