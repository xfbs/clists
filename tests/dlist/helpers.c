#include "helpers.h"

void check_and_free(dlist_t *list) {
    assertEquals(dlist_verify(list), 0);
    dlist_free(list);
}
