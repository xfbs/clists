#include "slist.h"
#include "dlist.h"

int main()
{
    unsigned int size;
    printf(" -> how many items? ");
    scanf("%u", &size);

    unsigned int memory = 0;
    memory += sizeof(dlist) + sizeof(dlist_node)*size;
    memory += sizeof(slist) + sizeof(slist_node)*size;
    printf(" -> going to use %.2fMiB of memory\n", memory/1024.0/1024.0);

    void *data = (void*)0xDECAFBAD;

    /* SLIST */
    printf("[ ] allocating slist\r");
    fflush(stdout);
    slist *slist = slist_alloc();
    printf("[*]\n");

    size /= 100;
    printf("[%3i%%] filling slist\r", 0);
    fflush(stdout);

    for(int percent = 0; percent <= 100; percent++)
    {
        printf("[%3i%%]\r", percent);
        fflush(stdout);

        for(int i = 0; i < size; i++)
        {
            slist_append(slist, data);
        }
    }
    printf("\n");
    printf("[%3i%%] deleting slist\r", 0);

    for(int percent = 0; percent <= 100; percent++)
    {
        printf("[%3i%%]\r", percent);
        fflush(stdout);

        for(int i = 0; i < size; i++)
        {
            slist_pop(slist);
        }
    }
    printf("\n");

    printf("[ ] freeing slist\r");
    fflush(stdout);
    slist_free(slist, 0);
    printf("[*]\n");


    /* DLIST */
    printf("[ ] allocating list\r");
    fflush(stdout);
    dlist *dlist = dlist_alloc();
    printf("[*]\n");

    size /= 100;
    printf("[%3i%%] filling dlist\r", 0);
    fflush(stdout);

    for(int percent = 0; percent <= 100; percent++)
    {
        printf("[%3i%%]\r", percent);
        fflush(stdout);

        for(int i = 0; i < size; i++)
        {
            dlist_append(dlist, data);
        }
    }
    printf("\n");
    printf("[%3i%%] deleting dlist\r", 0);

    for(int percent = 0; percent <= 100; percent++)
    {
        printf("[%3i%%]\r", percent);
        fflush(stdout);

        for(int i = 0; i < size; i++)
        {
            dlist_pop(dlist);
        }
    }
    printf("\n");

    printf("[ ] freeing dlist\r");
    fflush(stdout);
    dlist_free(dlist, 0);
    printf("[*]\n");

    return 0;
}
