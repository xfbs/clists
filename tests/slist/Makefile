CC = gcc
CFLAGS = -g -Wall -pedantic --std=gnu99 -I.. -I../..
LDFLAGS = -L../cu/ -L../.. -lcu -lclists -lpthread

OBJS = size.o length.c first.c \
	   last.c new.c init.c purge.c \
	   append.c prepend.c insert.c \
	   pop.c remove.c \
	   get.c set.c \
	   swap.c copy.c split.c \
	   tests.o helpers.o
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
