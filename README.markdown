clists
======

This is a project to build some simple reusable data structures in C that are simple to use.

slist
-----

SList is an implementation of a singly linked list (the nodes only store a pointer to the next node, not the previous node). To use the code, include `clists/slist.h` and link against `libclists.a`. The functions found in the header file are pretty much self-explanatory, a simple usage could look like this:

    // allocate new list
    slist_t *list = slist_new();
    int number = 5;
    
    // add pointer to number to list
    slist_append(list, &number);
    
    // output the number
    printf("the number is: %d\n", slist_get(list, 0));
    
    // free the list
    slist_free(list);

dlist
-----

Similar to SList, DList is also an implementation of a linked list, but this one is double linked (the nodes have both pointers to the previous and next node). The header file to include is located in `clists/dlist.h`, again you have to link agains `libclists.a`. The usage is also similar (pretty much the same, but with dlist_ prefixed instead of slist_):

    // allocate new list
    dlist_t *list = dlist_new();
    int number = 5;
    
    // add pointer to number
    dlist_append(list, &number);
    
    // output number
    printf("the number is: %d\n", dlist_get(list, 0));
    
    // free the list
    slist_free(list);

compiling
---------

The Makefile knows both how to compile the code (and produce a library file called `libclists.a`) and how to compile and run the tests.

    # compile the code
    make all
    
    # compile and run the tests
    make tests

contributing
------------

Feel free to contribute to this project by sending pull requests or however you'd like. One thing to note is that I'd like the license of this code to remain free (preferably GPL).
