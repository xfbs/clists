#include "sl_list.h"

int
main(void)
{
    sl_list *list = sl_list_new();
    printf("Please enter the names of the suspects. \n");

    do
    {
        printf("Name: ");
        char *name = malloc(256);
        // get line
        fgets(name, 256, stdin);
        // get rid of the \n
        name[strlen(name)-1] = '\0';
        list_append(list, name);
    } while(strcmp(list_last(list), "exit") != 0);

    list_pop(list);

    unsigned int size = list_size(list);
    printf("There are %u suspects. \n", size);

    for(int i = 0; i < size; i++)
    {
        printf("%2u: %s\n", i, (char*)list_get(list, i));
    }

    printf("Some diagnostics:\n");
    list_debug(list);
    list_delete(list, true);
}
