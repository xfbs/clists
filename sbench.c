#include "slist.h"

int main()
{
    unsigned int size;
    printf(" -> how many items? ");
    scanf("%u", &size);

    printf("[ ] allocating list\r");
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
    slist_free(list, 0);
    printf("[*]\n");

    return 0;
}
