all: program test

ifdef OS
   RM = del /Q
else
   ifeq ($(shell uname), Linux)
      RM = rm -f
   endif
endif

bigint:
	$(MAKE) -C bigint library

simplex:
	$(MAKE) -C src all

test:
	$(MAKE) -C test all

.PHONY: bigint simplex test

program: bigint simplex
	$(CXX) $(CXXFLAGS) $(wildcard bigint/*.o) $(wildcard src/*.o) src/Main.cc -o a.exe

clean:
	$(MAKE) -C bigint clean
	$(MAKE) -C src clean
	$(RM) a.exe
