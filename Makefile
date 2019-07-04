CC=g++ -g -Ofast

all: Fraction.o Vector.o Matrix.o Tabloid.o Main.o Coordinate.o StringUtil.o Simplex.o Io.o Base.o
	$(CC) -o a.exe Base.o Io.o Simplex.o StringUtil.o Fraction.o Vector.o Matrix.o Tabloid.o Main.o Coordinate.o bigint/BigUnsigned.o bigint/BigInteger.o bigint/BigIntegerAlgorithms.o bigint/BigUnsignedInABase.o bigint/BigIntegerUtils.o

test: Fraction.o Vector.o Matrix.o Tabloid.o Coordinate.o Tests.cc Base.o
	$(CC) -o test.exe Base.o Fraction.o Vector.o Matrix.o Tabloid.o Coordinate.o Tests.cc bigint/BigUnsigned.o bigint/BigInteger.o bigint/BigIntegerAlgorithms.o bigint/BigUnsignedInABase.o bigint/BigIntegerUtils.o
	./test.exe

Main.o: Main.cc
	$(CC) -c Main.cc

Fraction.o: Fraction.cc Fraction.hh
	$(CC) -c Fraction.cc

Vector.o: Vector.cc Vector.hh
	$(CC) -c Vector.cc

Matrix.o: Matrix.cc Matrix.hh
	$(CC) -c Matrix.cc

Tabloid.o: Tabloid.cc Tabloid.hh
	$(CC) -c Tabloid.cc

Coordinate.o: Coordinate.cc Coordinate.hh
	$(CC) -c Coordinate.cc

StringUtil.o: StringUtil.cc StringUtil.hh
	$(CC) -c StringUtil.cc

Simplex.o: Simplex.hh Simplex.cc
	$(CC) -c Simplex.cc

Io.o: Io.hh Io.cc
	$(CC) -c Io.cc

Base.o: Base.cc Base.hh
	$(CC) -c Base.cc

clean:
	rm *.o a.exe