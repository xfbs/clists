CC = gcc
CFLAGS = -g -Wall -pedantic -std=c99
LDFLAGS = 
OBJS = slist.o dlist.o
TARGETS = libclists.a
TESTS_DIR = tests
HEADER_DIR = clists

all: $(TARGETS)

libclists.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

%.o: %.c $(HEADER_DIR)/%.h
	$(CC) $(CFLAGS) -c -o $@ $<

tests: libclists.a $(OBJS)
	@cd $(TESTS_DIR) && make run

clean:
	rm -f *.o *.a
	@cd $(TESTS_DIR) && make clean

.PHONY: all tests clean
