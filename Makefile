all: program test

bigint:
	$(MAKE) -C bigint library

simplex:
	$(MAKE) -C src all

test:
	$(MAKE) -C test all

.PHONY: bigint simplex test

program: bigint simplex
	$(CXX) $(CXXFLAGS) $(wildcard bigint/*.o) $(wildcard src/*.o) src/Main.cc -o a.exe

tp: bigint simplex
	$(CXX) $(CXXFLAGS) $(wildcard bigint/*.o) $(wildcard src/*.o) tp.cc -o a.exe

clean:
	$(MAKE) -C bigint clean
	$(MAKE) -C src clean
  rm a.exe
