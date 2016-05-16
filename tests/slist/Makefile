CC = gcc
RM = rm -rf

TEST_LIB = clists
TEST_TARGET = slist
TEST_BIN = $(TEST_LIB)_$(TEST_TARGET)_test
TEST_LIB_PATH = ../../lib$(TEST_LIB).a
TESTS = $(wildcard $(TEST_TARGET)*.c)
TESTS_O = $(TESTS:%.c=%.o)
HELPERS = helpers.c tests.c
HELPERS_O = $(HELPERS:%.c=%.o)

CFLAGS = -g -Wall -pedantic --std=gnu99 -I.. -I../..
LDFLAGS = -L../cu/ -L../.. -lcu -l$(TEST_LIB) -lpthread

all: $(TEST_BIN)

$(TEST_BIN): $(TESTS_O) $(HELPERS_O) $(TEST_LIB_PATH)
	$(CC) $(CFLAGS) -o $@ $(TESTS_O) $(HELPERS_O) $(LDFLAGS)

%.o: %.c $(wildcard %.h)
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(TESTS_O) $(HELPERS_O) $(TEST_BIN)
	$(RM) output/

run: $(TEST_BIN)
	@test -d output || mkdir output
	@./$(TEST_BIN)

.PHONY: all clean run
