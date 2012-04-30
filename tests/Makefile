.DEFAULT: all
TESTS = slist dlist pvec

all: compile
clean: $(TESTS:%=%/clean) cu/clean

compile: libcu.a $(TESTS:%=%/test)
run: compile $(TESTS:%=%/run)

%/test:
	cd $* && make

%/run:
	@cd $* && make run
	@echo

%/clean:
	cd $* && make clean

libcu.a: cu/libcu.a
cu/libcu.a:
	cd cu && make libcu.a

.PHONY: all clean compile run libcu.a
