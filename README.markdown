CLists
======

CLists is a collection of data structures implemented in C/C++. Currently, these are all linked list implementations (`slist` and `dlist`), but I plan to add implementations of vectors (similar to `std::vector` in C++) and of maps (similar to `std::map` in C++). All of these implementations aren't fully optimizied, but they are legible (I try to keep them well commented) so that anyone can understand, change or rewrite them.

slist
-----

SList is the implementation of a (single linked list)[http://en.wikipedia.org/wiki/Singly_linked_list#Singly_linked_lists]. The code is in `slist.h` and `slist.c`, testing code can be found in `stest.c` as well as `sbench.c`. It uses the struct `slist`, which contains a pointer to the first and last node and the size of the list. Having a pointer to the last node means that appending to the list is efficient, the pointer to the first node means that pushing to the list is efficient. All functions that work with slists are prefixed with `slist_`. Information about the functions and their parameters can be found in `slist.h`.

dlist
-----

DList is the implementation of a (doubly linked list)[http://en.wikipedia.org/wiki/Doubly_linked_list]. The code is in `dlist.h` and `dlist.c`, testing code can be found in `dtest.c` and `dbench.c`. It uses the struct `dlist` internally, which has pointers to the head of the list (first node), the tail of the list (last node) and the size of the list. Having a pointer to the head and the tail means that appending and pushing is efficient. All functions that work with dlists are prefixed with `dlist_`. Information of the API can be found in `dlist.h`.

compiling
---------

All C code in this project is C99, thus when compiling you may need to pass a flag to your compiler to make it aware of this. To compile the slist and dlist tests, you can use these commands:

    gcc -std=c99 -o stest stest.c slist.c debug.c
    gcc -std=c99 -o dtest dtest.c dlist.c debug.c

contributing
------------

Feel free to contribute to this project by sending pull requests or however you'd like. One thing to note is that I'd like the license of this code to remain free (preferably GPL).
