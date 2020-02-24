//-----------------------------------------------------------------------------
// Arithmetic.c
// Client Module for BigInteger ADT
// John Abendroth
// CruzID: jabendro
// Assignment: PA3
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

int main(int argc, char* argv[]){
	 int i, j;
	 FILE *in, *out;

	 //check for correct number of arguments
	 if(argc != 3){
		  fprintf(stderr, "Incorrect argument format!");
		  exit(1);
	 }

	 //open files for read and write
	 in = fopen(argv[1], "r");
	 out = fopen(argv[2], "w");
	 if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if( out==NULL ){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}

	fscanf(in, "%d", &i);
	char input1 [i+1];
	fscanf(in, "%s", input1);
	BigInteger A = stringToBigInteger(input1);

	fscanf(in, "%d", &j);
	char input2 [j+1];
	fscanf(in, "%s", input2);
	BigInteger B = stringToBigInteger(input2);

	//print the BigIntegers A & B
	printBigInteger(out, A);
	printBigInteger(out, B);

	//A+B
	BigInteger Sum = sum(A,B);
	printBigInteger(out, Sum);

	//A-B
	BigInteger Diff = diff(A,B);
	printBigInteger(out, Diff);

	//A-A
	BigInteger Diff2 = diff(A,A);
	printBigInteger(out, Diff2);

	//3A-2B
	BigInteger three = stringToBigInteger("3");
	BigInteger A3 = prod(A, three);
	BigInteger two = stringToBigInteger("2");
	BigInteger B2 = prod(B, two);
	BigInteger Diff3 = diff(A3, B2);
	printBigInteger(out, Diff3);

	//AB
	BigInteger Prod = prod(A,B);
	printBigInteger(out, Prod);

	//A^2
	BigInteger AA = prod(A, A);
	printBigInteger(out, AA);

	//B^2
	//printBigInteger(out, B);
	BigInteger BB = prod(B,B);
	printBigInteger (out, BB);

	//9A^4
	BigInteger nine = stringToBigInteger("9");
	BigInteger A_4 = prod(A, A);
	multiply(A_4, A_4, A);
	multiply(A_4, A_4, A);
	multiply(A_4, A_4, nine);
	printBigInteger(out, A_4);

	//16B^5
	BigInteger sixteen = stringToBigInteger("16");
	BigInteger B_5 = prod(B,B);
	multiply(B_5, B_5, B);
	multiply(B_5, B_5, B);
	multiply(B_5, B_5, B);
	multiply(B_5, B_5, sixteen);
	printBigInteger(out, B_5);

	freeBigInteger(&A);
	freeBigInteger(&B);
	freeBigInteger(&Sum);
	freeBigInteger(&Diff);
	freeBigInteger(&Diff2);
	freeBigInteger(&three);
	freeBigInteger(&A3);
	freeBigInteger(&two);
	freeBigInteger(&B2);
	freeBigInteger(&Diff3);
	freeBigInteger(&Prod);
	freeBigInteger(&AA);
	freeBigInteger(&BB);
	freeBigInteger(&nine);
	freeBigInteger(&A_4);
	freeBigInteger(&sixteen);
	freeBigInteger(&B_5);

	//close files
	fclose(in);
	fclose(out);

	return(0);
}