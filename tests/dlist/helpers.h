#include "cu/cu.h"
#include "../../clists/dlist.h"

// some default variables
dlist_t *list;
int ret;
void *data;

// this is a simple function that sets list
// to whatever it gets from the first argument,
// runs the supplied block, and then frees the
// list at the end.
#define USING(l) \
    for(dlist_t *list = (l), *__ran = NULL; __ran == NULL; check_and_free(list), __ran++)

void check_and_free(dlist_t *list);
