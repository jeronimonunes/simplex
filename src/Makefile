all: Fraction.o Vector.o Matrix.o Tabloid.o Main.o Coordinate.o StringUtil.o Simplex.o Io.o Base.o
	$(CXX) $(CXXFLAGS) -o a.exe Base.o Io.o Simplex.o StringUtil.o Fraction.o Vector.o Matrix.o Tabloid.o Main.o Coordinate.o ../bigint/BigUnsigned.o ../bigint/BigInteger.o ../bigint/BigIntegerAlgorithms.o ../bigint/BigUnsignedInABase.o ../bigint/BigIntegerUtils.o

test: Fraction.o Vector.o Matrix.o Tabloid.o Coordinate.o Tests.cc Base.o
	$(CXX) $(CXXFLAGS) -o test.exe Base.o Fraction.o Vector.o Matrix.o Tabloid.o Coordinate.o Tests.cc ../bigint/BigUnsigned.o ../bigint/BigInteger.o ../bigint/BigIntegerAlgorithms.o ../bigint/BigUnsignedInABase.o ../bigint/BigIntegerUtils.o
	./test.exe

Main.o: Main.cc
	$(CXX) $(CXXFLAGS) -c Main.cc

Fraction.o: Fraction.cc Fraction.hh
	$(CXX) $(CXXFLAGS) -c Fraction.cc

Vector.o: Vector.cc Vector.hh
	$(CXX) $(CXXFLAGS) -c Vector.cc

Matrix.o: Matrix.cc Matrix.hh
	$(CXX) $(CXXFLAGS) -c Matrix.cc

Tabloid.o: Tabloid.cc Tabloid.hh
	$(CXX) $(CXXFLAGS) -c Tabloid.cc

Coordinate.o: Coordinate.cc Coordinate.hh
	$(CXX) $(CXXFLAGS) -c Coordinate.cc

StringUtil.o: StringUtil.cc StringUtil.hh
	$(CXX) $(CXXFLAGS) -c StringUtil.cc

Simplex.o: Simplex.hh Simplex.cc
	$(CXX) $(CXXFLAGS) -c Simplex.cc

Io.o: Io.hh Io.cc
	$(CXX) $(CXXFLAGS) -c Io.cc

Base.o: Base.cc Base.hh
	$(CXX) $(CXXFLAGS) -c Base.cc

clean:
	rm *.o a.exe