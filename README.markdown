clists [![Build Status](https://travis-ci.org/xfbs/clists.svg?branch=master)](https://travis-ci.org/xfbs/clists)
======

This is a project to implement some data structures in a reusable way so they are painless to use.

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

compiling and installing
------------------------

Using the Makefile, the code can be compiled, some tests can be run and the library can be installed to the system (check the Makefile
for further options, like where it should be installed to. 

    # compile the code
    make all
    
    # compile and run the tests
    make tests
    
    # install library
    sudo make install

todo
----

 -  write more tests for all functions
 -  finish some of the functions
 -  document the code more extensively
 -  think about alignment
 -  make a generic `list_t` type, along with functions to work with that
 -  run tis-interpreter and valgrind against everything!
 -  document error codes
