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

SOURCES=list.c sl_list.c dl_list.h
HEADERS=list.h sl_list.h dl_list.h
TARGETS=sl_list
.SUFFIXES: 

CTEST=$(CC) -c $(CFLAGS) -o $(OBJDIR)/$@_test.o test/$@.c
LTEST=$(CC) $(LFLAGS) -o $(BINDIR)/$@ $(OBJDIR)/$@_test.o $(patsubst %.c,$(OBJDIR)/%.o,$(filter %.c,$^)) $(patsubst %.cpp,$(OBJDIR)/%.o,$(filter %.cpp,$^))

$(filter %.c,$(SOURCES)): %.c: $(SRCDIR)/%.c
	$(CC)  -c $(CFLAGS) -o $(OBJDIR)/$*.o $<

$(filter %.cpp,$(SROUCES)): $(@:%=$(SRCDIR)/%)
	$(CXX) -c $(CFLAGS) -o $(@:%.cpp=$(OBJDIR)/%.o) $<

$(HEADERS): %.h: $(SRCDIR)/%.h
	cp $< $(INCDIR)/$@

sl_list: list.h sl_list.h list.c sl_list.c
	$(CTEST)
	$(LTEST)

sl_list_interactive: list.h sl_list.h list.c sl_list.c
	$(CTEST)
	$(LTEST)
