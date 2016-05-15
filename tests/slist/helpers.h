#include "cu/cu.h"
#include "../../clists/slist.h"

// some default variables
slist_t *list;
int ret;
void *data;

// this is a simple function that sets list
// to whatever it gets from the first argument,
// runs the supplied block, and then frees the
// list at the end.
#define USING(l) \
    for(slist_t *list = (l), *__ran = NULL; __ran == NULL; check_and_free(list), __ran++)


void check_and_free(slist_t *list);
