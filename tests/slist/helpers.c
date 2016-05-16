#include "../cu/cu.h"
#include "../../clists/slist.h"
#include "helpers.h"

void check_and_free(slist_t *list) {
    assertEquals(slist_verify(list), 0);
    slist_free(list);
}
