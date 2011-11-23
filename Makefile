SRCDIR:=src
OBJDIR:=obj
LIBDIR:=lib
BINDIR:=bin
TSTDIR:=test
INCDIR:=include

CFLAGS+=-I$(INCDIR) -O0 -ggdb3
LFLAGS+=-L$(LIBDIR) -O0 -ggdb3
CXX    =g++
CC     =gcc -std=c99

SOURCES=l_list.c llist.cpp
HEADERS=l_list.h
TARGETS=l_list

CTEST=$(CXX) -c $(CFLAGS) -o $(OBJDIR)/$@_test.o test/$@.c

$(filter %.c,$(SOURCES)): %.c: $(SRCDIR)/%.c
	echo $@ $* $<
	$(CC)  -c $(CFLAGS) -o $(OBJDIR)/$*.o $<

$(filter %.cpp,$(SROUCES)): $(@:%=$(SRCDIR)/%)
	$(CXX) -c $(CFLAGS) -o $(@:%.cpp=$(OBJDIR)/%.o) $<

$(HEADERS): %.h: $(SRCDIR)/%.h
	cp $< $(INCDIR)/$@
