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

TEST(insertFirst)
{
    // tests if insertion at beginning works.
    int data[] = {0xDECAFBAD, 0xCAFEBABE, 0xC0DEC0DE, 0};

    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    // add nodes
    for(int i = 0; data[i] != 0; i++) {
        ret = slist_insert(list, 0, &data[i]);
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

TEST(insertLast)
{
    // tests if insertion at the end works
    int data[] = {0xDECAFBAD, 0xCAFEBABE, 0xC0DEC0DE, 0};

    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    // add nodes
    for(int i = 0; data[i] != 0; i++) {
        ret = slist_insert(list, slist_length(list), &data[i]);
        assertEquals(ret, 0);
    }

    // verify those exist
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

TEST(insertMiddle)
{
    // tests if insertion at the middle works
    int data[] = {0xDECAFBAD, 0xCAFEBABE, 0xC0DEC0DE, 0};

    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    // add nodes
    for(int i = 0; data[i] != 0; i++) {
        ret = slist_insert(list, slist_length(list), &data[i]);
        assertEquals(ret, 0);
    }

    // verify those exist
    assertEquals(list->size, sizeof(int));
    assertEquals(list->length, 3);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(memcmp(&list->head->data[0], &data[0], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->data[0], &data[1], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->next->data[0], &data[2], sizeof(int)), 0);

    // now we add some in the middle
    int newdata[] = {0xABCD1234, 0xFEFE7000, 0};

    ret = slist_insert(list, 1, &newdata[0]);
    assertEquals(ret, 0);

    // verify that it exists
    assertEquals(list->size, sizeof(int));
    assertEquals(list->length, 4);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(memcmp(&list->head->data[0], &data[0], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->data[0], &newdata[0], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->next->data[0], &data[1], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->next->next->data[0], &data[2], sizeof(int)), 0);

    // add another one
    ret = slist_insert(list, 3, &newdata[1]);
    assertEquals(ret, 0);

    // verify that it exists
    assertEquals(list->size, sizeof(int));
    assertEquals(list->length, 5);
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(memcmp(&list->head->data[0], &data[0], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->data[0], &newdata[0], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->next->data[0], &data[1], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->next->next->data[0], &newdata[1], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->next->next->next->data[0], &data[2], sizeof(int)), 0);

    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(insertIllegal)
{
    ///...
}

TEST(removeFirst)
{
    // test removal of the first element of
    // a list

    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    // fill 'er up!
    int data[] = {0xDECAFBAD, 0xCAFEBABE, 0xC0DEC0DE, 0};
    for(int i = 0; data[i] != 0; i++) {
        ret = slist_append(list, &data[i]);
        assertEquals(ret, 0);
    }

    // make sure she's fill up
    assertEquals(list->length, 3);

    // remove first
    ret = slist_remove(list, 0);
    assertEquals(ret, 0);

    // make sure removal worked
    assertEquals(list->length, 2);
    assertEquals(list->size, sizeof(int));
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->head->next, list->tail);
    assertNotEquals(list->head, list->tail);
    assertEquals(memcmp(&list->head->data[0], &data[1], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->data[0], &data[2], sizeof(int)), 0);

    // free 'er
    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(removeLast)
{
    // test removal of the last element of
    // a list

    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    // fill 'er up!
    int data[] = {0xDECAFBAD, 0xCAFEBABE, 0xC0DEC0DE, 0};
    for(int i = 0; data[i] != 0; i++) {
        ret = slist_append(list, &data[i]);
        assertEquals(ret, 0);
    }

    // make sure she's fill up
    assertEquals(list->length, 3);

    // remove last
    ret = slist_remove(list, slist_length(list)-1);
    assertEquals(ret, 0);

    // make sure removal worked
    assertEquals(list->length, 2);
    assertEquals(list->size, sizeof(int));
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->head->next, list->tail);
    assertNotEquals(list->head, list->tail);
    assertEquals(memcmp(&list->head->data[0], &data[0], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->data[0], &data[1], sizeof(int)), 0);

    // free 'er
    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(removeMiddle)
{
    // test removal of the middle element of
    // a list

    slist_t *list = slist_new(sizeof(int));
    assertNotEquals(list, NULL);

    // fill 'er up!
    int data[] = {0xDECAFBAD, 0xCAFEBABE, 0xC0DEC0DE, 0};
    for(int i = 0; data[i] != 0; i++) {
        ret = slist_append(list, &data[i]);
        assertEquals(ret, 0);
    }

    // make sure she's fill up
    assertEquals(list->length, 3);

    // remove middle
    ret = slist_remove(list, 1);
    assertEquals(ret, 0);

    // make sure removal worked
    assertEquals(list->length, 2);
    assertEquals(list->size, sizeof(int));
    assertNotEquals(list->head, NULL);
    assertNotEquals(list->tail, NULL);
    assertEquals(list->head->next, list->tail);
    assertNotEquals(list->head, list->tail);
    assertEquals(memcmp(&list->head->data[0], &data[0], sizeof(int)), 0);
    assertEquals(memcmp(&list->head->next->data[0], &data[2], sizeof(int)), 0);

    // free 'er
    ret = slist_free(list);
    assertEquals(ret, 0);
}

TEST(removeIllegal) 
{
    //...
}
