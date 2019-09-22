# Mention default target.
all:

# Implicit rule to compile C++ files.
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

ifdef OS
   RM = del /Q
else
   ifeq ($(shell uname), Linux)
      RM = rm -f
   endif
endif

# Components of the library.
library-objects = \
	Fraction.o Vector.o Matrix.o Tabloid.o \
	Coordinate.o StringUtil.o Simplex.o Io.o Base.o

library-headers = \
	Fraction.hh Vector.hh Matrix.hh Tabloid.hh \
	Coordinate.hh StringUtil.hh Simplex.hh Io.hh Base.hh

# To ``make the library'', make all its objects using the implicit rule.
library: $(library-objects)

# Conservatively assume that all the objects depend on all the headers.
$(library-objects): $(library-headers)

# Delete all generated files we know about.
clean :
	$(RM) $(library-objects) $(testsuite-cleanfiles) $(program-objects)

# Come back and define default target.
all : library