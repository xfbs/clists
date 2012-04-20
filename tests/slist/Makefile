CC ?= gcc
CFLAGS = -g -Wall -pedantic --std=gnu99 -I.. -I../..
LDFLAGS = -L../cu/ -lcu

LIBS = slist.o
OBJS = alloc.o freeing.o appending.o tests.o

all: test

test: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS:%=../../%) $(LDFLAGS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o test
	rm -rf output

run: test
	@test -d output || mkdir output
	@./test

.PHONY: all clean run
