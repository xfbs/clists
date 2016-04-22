CC = gcc
CFLAGS = -g -Wall -pedantic -std=gnu99
OBJS = slist.o dlist.o
TARGET = libclists.a
HEADERS = dlist.h slist.h
HEADERS_DIR = clists
TESTS_DIR = tests

INSTALL = install -p -m 0644
INSTALL_TOP = /usr/local
INSTALL_INC = $(INSTALL_TOP)/include/clists
INSTALL_LIB = $(INSTALL_TOP)/lib

MKDIR = mkdir -p
RM = rm -f

all: $(TARGET)

libclists.a: $(OBJS)
	ar cr $@ $^
	ranlib $@

%.o: %.c $(HEADERS_DIR)/%.h
	$(CC) $(CFLAGS) -c -o $@ $<

tests: $(TARGET) $(OBJS)
	@cd $(TESTS_DIR) && make run

install: $(TARGET)
	$(MKDIR) $(INSTALL_INC) $(INSTALL_LIB)
	$(INSTALL) $(TARGET) $(INSTALL_LIB)
	cd $(HEADERS_DIR) && $(INSTALL) $(HEADERS) $(INSTALL_INC)

clean:
	$(RM) -f *.o *.a
	@cd $(TESTS_DIR) && make clean

.PHONY: all tests clean
