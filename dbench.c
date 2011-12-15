#include "dlist.h"

int main()
{
    unsigned int size;
    printf(" -> how many items? ");
    scanf("%u", &size);

    unsigned int memory = sizeof(dlist) + sizeof(dlist_node)*size;
    printf(" -> going to use %.2fMiB of memory\n", memory/1024.0/1024.0);

    printf("[ ] allocating list\r");
    fflush(stdout);
    dlist *list = dlist_alloc();
    printf("[*]\n");

    void *data = (void*)0xDECAFBAD;

    size /= 100;
    printf("[%3i%%] filling list\r", 0);
    fflush(stdout);

    for(int percent = 0; percent <= 100; percent++)
    {
        printf("[%3i%%]\r", percent);
        fflush(stdout);

        for(int i = 0; i < size; i++)
        {
            dlist_append(list, data);
        }
    }
    printf("\n");
    printf("[%3i%%] deleting list\r", 0);

    for(int percent = 0; percent <= 100; percent++)
    {
        printf("[%3i%%]\r", percent);
        fflush(stdout);

        for(int i = 0; i < size; i++)
        {
            dlist_pop(list);
        }
    }
    printf("\n");

    printf("[ ] freeing list\r");
    fflush(stdout);
    dlist_free(list, 0);
    printf("[*]\n");

    return 0;
}