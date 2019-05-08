CC=g++ -g -Ofast

all: Fraction.o Vector.o Matrix.o Tabloid.o Main.o Coordinate.o Io.o
	$(CC) -o a.exe Fraction.o Vector.o Matrix.o Tabloid.o Main.o Coordinate.o Io.o bigint/BigUnsigned.o bigint/BigInteger.o bigint/BigIntegerAlgorithms.o bigint/BigUnsignedInABase.o bigint/BigIntegerUtils.o

test: Fraction.o Vector.o Matrix.o Tabloid.o Coordinate.o Tests.cc BigInteger.o
	$(CC) -o test.exe Fraction.o Vector.o Matrix.o Tabloid.o Coordinate.o Tests.cc BigInteger.o
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

Io.o: Io.cc Io.hh
	$(CC) -c Io.cc

clean:
	rm *.o a.exe