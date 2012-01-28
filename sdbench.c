/*  File: sdbench.c
 *  
 *  Copyright (C) 2011, Patrick M. Elsen
 *
 *  This file is part of CLists (http://github.com/xfbs/CLists)
 *  Author: Patrick M. Elsen <pelsen.vn (a) gmail.com>
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include <stdio.h>
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
