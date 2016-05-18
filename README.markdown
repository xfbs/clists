clists [![Build Status](https://travis-ci.org/xfbs/clists.svg?branch=master)](https://travis-ci.org/xfbs/clists)
======

This is a project to implement some data structures in C
so they are painless, obvious and flexible.

Currently, the following data structures are implemented:

| Name          | Description           |
| ------------- | --------------------- |
| `slist`       | (single) linked list  |
| `dlist`       | (doubly) linked list  |

documentation
-------------

Documentation is either [available here](xfbs.github.io/clists) or
can be generated from the code with:

    make docs

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

Some data structures that could be added:

| Name      | Description       |
| --------- | ----------------- |
| `alist`   | array list        |
| `sarray`  | sparse array      |
| `bitvec`  | bit vector        |
| `hashmap` | hash map          |
| `btree`   | binary tree       |

 -  write more tests for all functions
 -  finish some of the functions
 -  document the code more extensively
 -  think about alignment
 -  generic `list_t`
 -  some kind of iterator
 -  run tis-interpreter and valgrind against everything!
 -  document error codes
