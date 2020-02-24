# Makefile for CSE 101 Programming Assignment 3
# CruzID: jabendro
#
#       make                   makes Arithmetic
#       make BigIntegerTest    makes BigIntegerTest
#       make ListTest          makes ListTest
#       make BigIntegerClient  makes BigIntegerClient
#       make ListClient        makes ListClient
#       make memcheck          makes memcheck (valgrind)
#       make clean             cleans the directory
#------------------------------------------------------------------------------

Arithmetic: Arithmetic.o Biginteger.o  List.o
	gcc -o Arithmetic Arithmetic.o BigInteger.o List.o

Arithmetic.o : Arithmetic.c BigInteger.h
	gcc -c -std=c99 -Wall Arithmetic.c

BigInteger.o : BigInteger.c BigInteger.h List.h
	gcc -c -std=c99 -Wall BigInteger.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

BigIntegerTest : BigIntegerTest.o BigInteger.o List.o
	gcc -o BigIntegerTest BigIntegerTest.o BigInteger.o List.o -lm

BigIntegerTest.o : BigIntegerTest.c BigInteger.h List.h
	gcc -c -std=c99 -Wall BigIntegerTest.c

ListTest : ListTest.o List.o
	gcc -o ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	gcc -c -std=c99 -Wall ListTest.c

ListClient : ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

BigIntegerClient : BigIntegerClient.o BigInteger.o List.o
	gcc -o BigIntegerClient BigIntegerClient.o BigInteger.o List.o

BigIntegerClient.o : BigIntegerClient.c BigInteger.h List.h
	gcc -c -std=c99 -Wall BigIntegerClient.c

memcheck : Sparse 
	valgrind --leak-check=full -v Arithmetic in.txt out.txt

clean :
	rm -f Arithmetic BigIntegerTest ListTest BigIntegerClient ListClient *.o *.txt