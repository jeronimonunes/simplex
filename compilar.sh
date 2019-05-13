#!/bin/bash
g++ -Ofast Vector.cc Tabloid.cc Matrix.cc Main.cc Fraction.cc Coordinate.cc \
bigint/BigUnsigned.cc bigint/BigInteger.cc bigint/BigIntegerAlgorithms.cc \
bigint/BigUnsignedInABase.cc bigint/BigIntegerUtils.cc -o a.exe