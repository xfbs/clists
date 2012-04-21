CC = gcc
CFLAGS = -g -Wall -pedantic -std=c99
LDFLAGS = 
OBJS = slist.o dlist.o
TARGETS = libclist.a
TESTS_DIR = tests
HEADER_DIR = clists

all: $(TARGETS)

libclist.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

%.o: %.c $(HEADER_DIR)/%.h
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(OBJS)
	@cd $(TESTS_DIR) && make run

clean:
	rm -f *.o *.a
	@cd $(TESTS_DIR) && make clean

.PHONY: all test clean
