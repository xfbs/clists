CC = gcc
CFLAGS = -g -Wall -pedantic --std=gnu99 -I.. -I../..
LDFLAGS = -L../cu/ -L../.. -lcu -lclists

OBJS = alloc.o freeing.o purging.o tests.o
TSTS = ../../libclists.a

all: test

test: $(OBJS) $(TSTS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

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
