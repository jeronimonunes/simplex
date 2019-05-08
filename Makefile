CC=g++ -g

all: Fraction.o Vector.o Matrix.o Tabloid.o Main.o Coordinate.o Io.o
	$(CC) -o a.exe Fraction.o Vector.o Matrix.o Tabloid.o Main.o Coordinate.o Io.o

test: Fraction.o Vector.o Matrix.o Tabloid.o Coordinate.o Tests.cc
	$(CC) -o test.exe Fraction.o Vector.o Matrix.o Tabloid.o Coordinate.o Tests.cc
	./test.exe

Main.o: Main.cc
	$(CC) -c Main.cc

Fraction.o: Fraction.cc
	$(CC) -c Fraction.cc

Vector.o: Vector.cc
	$(CC) -c Vector.cc

Matrix.o: Matrix.cc
	$(CC) -c Matrix.cc

Tabloid.o: Tabloid.cc
	$(CC) -c Tabloid.cc

Coordinate.o: Coordinate.cc
	$(CC) -c Coordinate.cc

Io.o: Io.cc
	$(CC) -c Io.cc

clean:
	rm *.o a.exe