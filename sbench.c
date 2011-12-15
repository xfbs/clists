#include "slist.h"

int main()
{
    unsigned int size;
    printf(" -> how many items? ");
    scanf("%u", &size);

    unsigned int memory = sizeof(slist) + sizeof(slist_node)*size;
    printf(" -> going to use %.2fMiB of memory\n", memory/1024.0/1024.0);

    printf("[ ] allocating list\r");
    fflush(stdout);
    slist *list = slist_alloc();
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
            slist_append(list, data);
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
            slist_pop(list);
        }
    }
    printf("\n");

    printf("[ ] freeing list\r");
    fflush(stdout);
    slist_free(list, 0);
    printf("[*]\n");

    return 0;
}
