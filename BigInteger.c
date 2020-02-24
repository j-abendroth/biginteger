//-----------------------------------------------------------------------------
// BigInteger.c
// Implementation file for BigInteger.c
// John Abendroth
// CruzID: jabendro
// Assignment: PA3
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "BigInteger.h"
#include "List.h"

#define POWER 9
#define BASE 1000000000

// Structs -----------------------------------

// Private BigIntegerObj type
typedef struct BigIntegerObj {
	int sign;
	List list;
}BigIntegerObj;

// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(void) {
	BigInteger L;
	L = malloc(sizeof(BigIntegerObj));
	L->sign = 0;
	L->list = newList();
	return(L);
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN) {
	if (pN != NULL && *pN != NULL) {
		freeList(&((*pN)->list));
		free(*pN);
		*pN = NULL;
	}
}

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N) {
	if (N == NULL) {
		printf("BigInteger Error: Calling sign() on null BigInteger reference\n");
		exit(1);
	}
	if (N->sign == 0) return(0);
	else if (N->sign == 1) return(1);
	else
		return(-1);
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B
int compare(BigInteger A, BigInteger B) {
	if (A == NULL || B == NULL) {
		printf("BigInteger Error: Calling compare() on null BigInteger reference\n");
		exit(1);
	}
	if (equals(A, B) == 1)
		return(0);
	//if the signs of A and B are mixed, 1 is automatically larger
	if (sign(A) != sign(B))
	{
		if (sign(A) > sign(B))
			return(1);
		else
			return(-1);
	}

	//lengths are not equal
	//signs guaranteed to be equal
	if (length(A->list) != length(B->list))
	{
		//if signs are pos, smaller most significant digit is acutally larger number
		if (sign(B) == -1 && sign(B) == -1)
		{
			if(length(A->list) > length(B->list))
				return(-1);
			else //length(A) < length(B)
				return(1);
		}
		else //else A & B are pos
		{
			if(length(A->list) > length(B->list))
				return(1);
			else //length(A) < length(B)
				return(-1);
		}
	}
	else //else length is the same and signs are the same
	{
		if (sign(A) == 1)
		{
			long line1, line2;
			moveFront(A->list);
			moveFront(B->list);
			line1 = get(A->list);
			line2 = get(B->list);
			//if the 2 most significant digits are the same, move to the next
			while (line1 == line2)
			{
				moveNext(A->list);
				moveNext(B->list);
				line1 = get(A->list);
				line2 = get(B->list);
			}
			if (line1 > line2)
				return(1);
			else
				return(-1);
		}
		else //else A is neg
		{
			long line1, line2;
			moveFront(A->list);
			moveFront(B->list);
			line1 = get(A->list);
			line2 = get(B->list);
			//if the 2 most significant digits are the same, move to the next
			while (line1 == line2)
			{
				moveNext(A->list);
				moveNext(B->list);
				line1 = get(A->list);
				line2 = get(B->list);
			}
			if (line1 > line2)
				return(-1);
			else
				return(1);
		}
	}
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
	if(A == NULL || B == NULL){
		printf("BigInteger Error: Calling equals() on NULL BigInteger reference\n");
		exit(1);
	}
	if(sign(A) != sign(B)){
		return(0);
	}
	
	if(length(A->list) != length(B->list)){
		return(0);
	}
	

	moveFront(A->list);
	moveFront(B->list);
	while (index(A->list) >= 0 || index(B->list) >= 0)
	{
		if(get(A->list) != get(B->list))
			return(0);
		moveNext(A->list);
		moveNext(B->list);
	}
	//if none of the characters were found unequal, then the BigIntegers are the same
	return(1);
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state
void makeZero(BigInteger N) {
	if (N == NULL) {
		printf("BigInteger Error: Calling makeZero() on null BigInteger reference\n");
		exit(1);
	}
	clear(N->list);
	N->sign = 0;
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N) {
	if (N == NULL) {
		printf("BigInteger Error: Calling negate() on null BigInteger reference\n");
		exit(1);
	}
	if (N->sign != 0)
	{
		if (N->sign == -1)
			N->sign = 1;
		else
			N->sign = -1;
	}
}

// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s) {
	if (s == NULL) {
		printf("BigInteger Error: Calling stringToBigInteger() on NULL string pointer\n");
		exit(1);
	}
	BigInteger N = newBigInteger();
	int len = strlen(s), count = 0, ten = 1;
    long temp, new_long = 0;

	for (int i = 0; i < len; i++)
	{
		if (s[i] < 48 || s[i] > 57){
			if (s[i] != 43 && s[i] != 45){
				printf("BigInteger Error: Calling stringToBigInteger on string with non base ten digits\n");
				exit(1);
			}
		}
	}

	if (s[0] == 43 || s[0] == 45)
	{
		if (s[0] == 43)
		{
			//if s[0] == 43, then the character is "+"
			//set sign positive, decrement length, and move address of ptr *s forward 1
			N->sign = 1;
			len--;
			s++;
		}
		if (s[0] == 45)
		{
			//if s[0] == 45, then character is "-"
			//set sign negative, decrement length, and move address of ptr *s forward 1
			N->sign = -1;
			len--;
			s++;
		}
	}
	//don't input leading zeros
	//move address of ptr *s forward while the first digits are 0s
	while (s[0] == 48)
	{
		len--;
		s++;
	}

	for (int i = 1; i <= len; i++)
	{
		//start at the back of the char array and loop backwards until s[len-len]
		//multiply ten by ten each time so that it's the same as 10^i but doesn't need pow function
		temp = s[len-i] - '0';
		new_long = new_long + (temp * ten);
		ten = ten * 10;
		++count;

		// if the counter is equal to the defined power, place the current long into the list and reset everything
		if (count == POWER)
		{
			prepend(N->list, new_long);
			new_long = 0;
			count = 0;
			ten = 1;
		}
	}
	// if something is left inside new_long, insert into list
	if (count != 0)
	{
		prepend(N->list, new_long);
	}
	//if sign still isn't set by now, it defaults to pos
	if(N->sign == 0)
	{
		N->sign = 1;
	}
	return(N);
}

//private helper function for multiplying
//prodstringToBigInteger()
//returns reference to new BigInteger object, same as stringToBigInteger but the power is always 1
//used as a temp BigInt reference to store each digit individually so that prod() works properly
BigInteger prodstringToBigInteger(char* s) {
	if (s == NULL) {
		printf("BigInteger Error: Calling stringToBigInteger() on NULL string pointer\n");
		exit(1);
	}
	BigInteger N = newBigInteger();
	int len = strlen(s), count = 0, ten = 1;
    long temp, new_long = 0;

	for (int i = 1; i <= len; i++)
	{
		//start at the back of the char array and loop backwards until s[len-len]
		//multiply ten by ten each time so that it's the same as 10^i but doesn't need pow function
		temp = s[len-i] - '0';
		new_long = new_long + (temp * ten);
		ten = ten * 10;
		++count;

		// if the counter is equal to the defined power, place the current long into the list and reset everything
		if (count == 1)
		{
			prepend(N->list, new_long);
			new_long = 0;
			count = 0;
			ten = 1;
		}
	}
	// if something is left inside new_long, insert into list
	if (count != 0)
	{
		prepend(N->list, new_long);
	}
	//if sign still isn't set by now, it defaults to pos
	if(N->sign == 0)
	{
		N->sign = 1;
	}
	return(N);
}
// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N) {
	if (N == NULL) {
		printf("BigInteger Error: Calling copy() on NULL BigInteger reference\n");
		exit(1);
	}
	BigInteger new_BigInteger = newBigInteger();
	moveBack(N->list);
	while (index(N->list) >= 0) {
		long copy = get(N->list);
		prepend(new_BigInteger->list, copy);
		movePrev(N->list);
	}
	new_BigInteger->sign = N->sign;
	return(new_BigInteger);
}


//makeneg()
//private helper function
//Returns a reference to a BigInteger oebject that has all elements in the list negative
BigInteger makeneg(BigInteger A) {
	BigInteger Aneg = copy(A);
	moveBack(Aneg->list);
	while (index(Aneg->list) >= 0)
	{
		long temp = get(Aneg->list);
		temp = temp * -1;
		set(Aneg->list, temp);
		movePrev(Aneg->list);
	}
	return(Aneg);
}

// normalize()
// private helper function
// Returns a normalized a BigInteger reference from a BigInteger reference whose list longs were outside the range of the current base
BigInteger normalize(BigInteger A) {
	if (length(A->list) == 0) {
		return(A);
	}
	moveFront(A->list);
	long check_sign = get(A->list);
	// if front number is negative, consider the whole list a negative number and flip everything
	if (check_sign < 0)
	{
		BigInteger Aneg = makeneg(A);
		BigInteger B = normalize(Aneg);
		B->sign = -1;
		freeBigInteger(&Aneg);
		return(B);
	}

	int carry = 0;
	BigInteger B = newBigInteger();

	moveBack(A->list);
	while (index(A->list) >= 0) {
		if (get(A->list) < 0) // long is neg
		{
			long temp = get(A->list);
			if (carry != 0)
			{
				temp += carry;
			}
			temp += BASE;
			prepend(B->list, temp);
			carry = -1;
		}
		else if (get(A->list) > (BASE - 1)) // long is past base
		{
			long temp = get(A->list);
			if (carry != 0)
			{
				temp += carry;
			}
			temp -= BASE;
			prepend(B->list, temp);
			carry = 1;
		}
		else // long doesn't need to be normalized
		{
			long temp = get(A->list);
			if (carry != 0)
			{
				temp += carry;
			}
			prepend(B->list, temp);
			carry = 0;
		}
		movePrev(A->list);
	}
	// if there's a carry left over, put it at front of list
	// shouldn't be possible to have negative left over carry
	if (carry != 0)
	{
		prepend(B->list, carry);
	}
	//if the result returns through general case with the front digit not negative
	//then the normalized number should be positive
	B->sign = 1;
	return(B);
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B) {
	if (S == NULL || A == NULL || B == NULL)
	{
		printf("BigInteger Error: Calling add() on NULL BigInteger reference\n");
		exit(1);
	}

	BigInteger Acopy = copy(A);
	BigInteger Bcopy = copy(B);

	BigInteger Sum = sum(Acopy, Bcopy);
	
    freeList(&S->list);
	S->list = copyList(Sum->list);
	S->sign = sign(Sum);
    freeBigInteger(&Sum);
	freeBigInteger(&Acopy);
	freeBigInteger(&Bcopy);
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B) {
	if (A == NULL || B == NULL) {
		printf("BigInteger Error: Calling sum() on NULL BigInteger reference\n");
		exit(1);
	}

	if (sign(A) == -1 || sign(B) == -1)
	{
		if (sign(A) == -1 && sign(B) == -1) // if both A and B are negatively signed, the answer is the same as considering them positive and just making it negative at the end
		{
			//sum of 2 negatives is the same as just adding the 2 positive versions
			//and setting the sign negative after
			BigInteger Acopy = copy(A);
			BigInteger Bcopy = copy(B);
			Acopy->sign = Bcopy->sign = 1;
			BigInteger Sum = sum(Acopy,Bcopy);
			Sum->sign = -1;
			freeBigInteger(&Acopy);
			freeBigInteger(&Bcopy);
			return(Sum);
		}
		else if (sign(A) == -1 && sign(B) != -1) // else since only one is signed negatively, if it's A
		{
			//want to compare magnitudes, so copy A and negate to compare to B
			BigInteger Acopy = copy(A);
			negate(Acopy);
			if(equals(Acopy, B) == 1)
			{
				BigInteger result = newBigInteger();
				freeBigInteger(&Acopy);
				return(result);
			}
			BigInteger Aneg = makeneg(A);
			negate(Aneg);
			BigInteger result = sum(Aneg, B);
			freeBigInteger (&Aneg);
			freeBigInteger(&Acopy);
			return(result);
		}
		else // else it's B that's just negatively signed
		{
			BigInteger Bcopy = copy(B);
			negate(Bcopy);
			if(compare(A, Bcopy) == 0)
			{
				BigInteger result = newBigInteger();
				freeBigInteger(&Bcopy);
				return(result);
			}
			BigInteger Bneg = makeneg(B);
			negate(Bneg);
			BigInteger result = sum(A, Bneg);
			freeBigInteger(&Bneg);
			freeBigInteger(&Bcopy);
			return(result);	
		}
	}

	BigInteger S, temp = newBigInteger();
	long line1, line2, result;

	moveBack(A->list);
	moveBack(B->list);
	while (index(A->list) >= 0 || index(B->list) >= 0)
	{
		if (index(A->list) >= 0 && index(B->list) >= 0) //both A and B will have non-zero numbers
		{
			line1 = get(A->list);
			line2 = get(B->list);

			result = line1 + line2;
			prepend(temp->list, result);
		}
		else if (index(A->list) >= 0 && index(B->list) < 0) // A still has numbers left, B doesn't, so add A numbers with 0
		{
			line1 = get(A->list);
			prepend(temp->list, line1);
		}
		else // B still has numbers left, A doesn't, so add B numbers with 0
		{
			line2 = get(B->list);
			prepend(temp->list, line2);
		}
		movePrev(A->list);
		movePrev(B->list);
	}
	S = normalize(temp);
	freeBigInteger(&temp);
	return(S);
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting //itscurrentstate: D=A-B
void subtract(BigInteger D, BigInteger A, BigInteger B){
	if(D == NULL || A== NULL || B== NULL)
	{
		printf("BigInteger Error: Calling subtract() on NULL BigInteger reference\n");
		exit(1);
	}

	BigInteger Acopy = copy(A);
	BigInteger Bcopy = copy(B);

	BigInteger Diff = diff(Acopy, Bcopy);

	freeBigInteger(&Acopy);
	freeBigInteger(&Bcopy);
	freeList(&D->list);

	D->list = copyList(Diff->list);
	D->sign = sign(Diff);
	freeBigInteger (&Diff);
}

// diff()
// Returns a reference to a new BigInteger object representing A - B
BigInteger diff(BigInteger A, BigInteger B){
	if (A == NULL || B == NULL) {
		printf("BigInteger Error: Calling diff() on NULL BigInteger reference\n");
		exit(1);
	}

	if (sign(A) == -1 || sign(B) == -1)
	{
		if (sign(A) == -1 && sign(B) == -1)
		{
			BigInteger Acopy = copy(A);
			BigInteger Bcopy = copy(B);
			negate(Acopy);
			negate(Bcopy);
			//if A & B are the same, -x-(-x)=0, so return 0 state BigInteger
			if (equals(Acopy,Bcopy) == 1)
			{
				BigInteger result = newBigInteger();
				freeBigInteger(&Acopy);
				freeBigInteger(&Bcopy);
				return(result);
			}
			//negative minus negative is negative plus first
			//makeneg() on first and sum
			BigInteger Aneg = makeneg(A);
			negate(Aneg);
			BigInteger result = sum(Aneg, Bcopy);
			freeBigInteger(&Bcopy);
			freeBigInteger(&Acopy);
			freeBigInteger(&Aneg);
			return(result);
		}
		else if (sign(A) == -1 && sign(B) != -1) //A neg and B isn't. Same as adding numbers and making sign neg
		{
			//BigInteger Aneg = makeneg(A);
			//negate(Aneg);
			//BigInteger result = diff(Aneg, B);
			//freeBigInteger(&Aneg);
			BigInteger Acopy = copy(A);
			negate(Acopy);
			BigInteger result = sum(Acopy,B);
			result->sign = -1;
			freeBigInteger(&Acopy);
			return(result);
		}
		else //it's just B negative sign
		{
			//positive number minus negative is like adding the two numbers
			BigInteger Bcopy = copy(B);
			negate(Bcopy);
			BigInteger result = sum(A, Bcopy);
			freeBigInteger(&Bcopy);
			return(result);
		}
	}

	if(equals(A,B) == 1)
	{
		BigInteger result = newBigInteger();
		return(result);
	}

	BigInteger S, temp = newBigInteger();
	long line1, line2, result;

	moveBack(A->list);
	moveBack(B->list);
	while(index(A->list) >= 0 || index(B->list) >= 0)
	{
		if(index(A->list) >= 0 && index(B->list) >= 0)
		{
			line1 = get(A->list);
			line2 = get(B->list);

			result = line1 - line2;
			prepend(temp->list, result);
		}
		else if (index(A->list) >= 0 && index(B->list) < 0)
		{
			line1 = get(A->list);
			prepend(temp->list, line1);
		}
		else
		{
			line2 = get(B->list);
			line2 = line2 * -1;
			prepend(temp->list, line2);
		}
		movePrev(A->list);
		movePrev(B->list);
	}
	S = normalize(temp);
	freeBigInteger(&temp);
	return(S);
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
	if (P == NULL || A == NULL || B == NULL){
		printf("BigInteger Error: Calling multiply() on NULL BigInteger reference\n");
		exit(1);
	}
	BigInteger Acopy = copy(A);
	BigInteger Bcopy = copy(B);

	BigInteger Mult = prod(A,B);
	freeBigInteger(&Acopy);
	freeBigInteger(&Bcopy);
	freeList(&P->list);

	P->list = copyList(Mult->list);
	P->sign = sign(Mult);
	freeBigInteger(&Mult);
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
	if (A==NULL || B == NULL){
		printf("BigInteger Error: Calling prod() on NULL BigInteger reference");
		exit(1);
	}
	BigInteger Acopy, Bcopy, temp_BigInt, line1BigInt, line2BigInt, S = newBigInteger();
	long line1, line2, Along, Blong;
	int count = 0;
	unsigned long long offset_ten = 1, result = 0;
	char temp_string [100000];

	if (compare(A, B) == -1)
	{
		Acopy = copy(B);
		Bcopy = copy(A);
	}
	else
	{
		Acopy = copy(A);
		Bcopy = copy(B);
	}
	
	moveBack(Bcopy->list);
	while (index(Bcopy->list) >= 0)
	{
		Blong = get(Bcopy->list);
		char temp [100000];
		sprintf(temp, "%ld", Blong);
		line2BigInt = prodstringToBigInteger(temp);
		moveBack(line2BigInt->list);
		while(index(line2BigInt->list) >= 0)
		{
			//line2 = get(line2BigInt->list);
			moveBack(Acopy->list);
			while(index(Acopy->list) >= 0)
			{
				Along = get(Acopy->list);
				//turn line 1 into a string and pass to prodstringToBigInteger()
				//want each digit as its own node in the list
				char temp2 [100000];
				sprintf(temp2, "%ld", Along);
				line1BigInt = prodstringToBigInteger(temp2);
				moveBack(line1BigInt->list);
				while(index(line1BigInt->list) >=0)
				{
					line1 = get(line1BigInt->list);
					line2 = get(line2BigInt->list);
					result += line2 * (line1 * offset_ten);
					offset_ten = offset_ten * 10;
					movePrev(line1BigInt->list);
				}
				movePrev(Acopy->list);
				freeBigInteger(&line1BigInt);
			}
			sprintf(temp_string, "%lld", result);
			temp_BigInt = stringToBigInteger(temp_string);
			add(S, S, temp_BigInt);
			freeBigInteger(&temp_BigInt);

			++count;
			offset_ten = 1;
			for (int i = 0; i < count; i++)
			{
				offset_ten = offset_ten * 10;
			}
			result = 0;
			movePrev(line2BigInt->list);
		}
		/*
		sprintf(temp_string, "%ld", result);
		temp_BigInt = stringToBigInteger(temp_string);
		add(S, S, temp_BigInt);
		freeBigInteger(&temp_BigInt);

		++count;
		offset_ten = 1;
		for (int i = 0; i < count; i++)
		{
			offset_ten = offset_ten * 10;
		}
		result = 0;
		*/
		freeBigInteger(&line2BigInt);
		movePrev(Bcopy->list);
	}
	if (sign(A) != sign(B))
	{
		S->sign = -1;
	}
	else
	{
		S->sign = 1;
	}
	freeBigInteger(&Acopy);
	freeBigInteger(&Bcopy);
	return(S);
}

// Other operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N) {
	if (N == NULL) {
		printf("BigInteger Error: Calling printBigInteger() on NULL BigInteger reference\n");
		exit(1);
	}

	if(length(N->list) == 0)
	{
		fprintf(out, "0");
	}

	if (sign(N) == -1)
		fprintf(out, "-");

	moveFront(N->list);
	if (length(N->list) > 0)
		fprintf(out, "%ld", get(N->list));
	moveNext(N->list);
	while (index(N->list) >= 0) {
		// add edge case about not printing leading zeroes with front number
		fprintf(out, "%0*ld", POWER, get(N->list));
		moveNext(N->list);
	}
	fprintf(out, "\n");
	fprintf(out, "\n");
}
