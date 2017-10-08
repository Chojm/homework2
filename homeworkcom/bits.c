/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
	return ~(~x | ~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	return (x >> (n << 3)) & 0xFF;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
	return (x >> n) & ~((((0x1) << 31) >> n) << 1);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
	unsigned mask1 = 0x55;
	unsigned mask2 = 0x33;
	unsigned mask3 = 0x0F;
	mask1 = (mask1 << 8) + 0x55;
	mask1 = (mask1 << 8) + 0x55;
	mask1 = (mask1 << 8) + 0x55; /*shift it 3x so it is now 0x55555555*/
	/*mask1 = 010101...*/
	mask2 = (mask2 << 8) + 0x33;
    mask2 = (mask2 << 8) + 0x33;
    mask2 = (mask2 << 8) + 0x33;
	/*mask2 = 00110011...*/
	mask3 = (mask3 << 8) + 0x0F;
    mask3 = (mask3 << 8) + 0x0F;
    mask3 = (mask3 << 8) + 0x0F;
	/*mask3 = 00001111...*/
	x = x + (~((x>>1) & mask1) + 1); /*first split*/
	x = (x & mask2) + ((x >>2) & mask2); /*split 2*/
	x = (x & mask3) + ((x >>4) & mask3); /*split 3*/
	/*now we can just add the bits until they are "stacked" entirely*/
	x = x + (x>>8);
	x = x + (x>>16);
	/*the answer has a max size of 32, so & it with the last 6 bits*/
	return (x & 0x3F /*00...111111*/);
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	return (~((x >> 31) | (((~x) + 1) >> 31))) & 1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
   return  1 << 31; /*shift the '1' bit to get 0x80000000*/
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	int mask = x >> 31;
  	return !(((~x & mask) + (x & ~mask)) >> (n + ~0));
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	int xMSB = ((x>>31) & 1);
	int bias = xMSB;
	bias = bias << n;
	bias += ((xMSB<<31) >>31); /*1<<31>>31 == -1, or still 0 if xMSB = 0*/

	return ((x + bias) >> n);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	int t = ~x;
	int q = t + 1;
	return q;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	//two cases that x is equal or less than 0.
	int nx = ~x + 1;
	//1. sign bit is 0 when x is negated.
	int sign = (nx >> 31) & 1;
	//2. x is tmin.
	int check_tmin = !(x ^ (1<<31));
	return sign ^ check_tmin;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	//get sign of x and y.
	int sx = (x>>31) & 1;
	int sy = (y>>31) & 1;
	//calculate y-x. don't care about overflow.
	int y_x = y + (~x + 1);
	//get sign bit of y-x.
	int syx = (y_x>>31) & 1;
	//two cases that x<=y.
	//1. x is negative and y is positive.
	//2. both value have same sign bit, and syx indicates positive.
	int r = (sx & !sy) | (!(sx^sy) & !syx);
	return r;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	/* every time shift half length of the unknown part and record the rersult in ax then
	add axs together */	
	int a16, a8, a4, a2, a1, b16, b8, b4, b2;
	a16 = !(!(x >> 16));
	b16 = a16 << 4;
	a8 = !(!(x >> (8 + b16)));
	b8 = (a8 << 3) + b16;
	a4 = !(!(x >> (4 + b8)));
	b4 = (a4 << 2) + b8; 
	a2 = !(!(x >> (2 + b4)));
	b2 = (a2 << 1) + b4;
	a1 = (x >> (1 + b2));
	return a1 + b2;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
 	//change sign bit of the value. that's all.
	unsigned nonnan = (0x80000000 ^ uf);
	//check "Exp" bits.
	unsigned curry = 0xff << 23;
	//if "Exp" bits are filled with 1 and "Frac" bits have at least one bit, it is NaN.
	if(((curry & uf) == curry) && (uf & ((1<<23) + (~0)))) return uf;
	return nonnan;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
	int tx = x;
	unsigned result = 0; //= x & (1<<31);
	//b will be the sign bit with 31 times left shifted.
	int b = x&0x80000000;
	int cc = 0x7f;
	int qtx;
	int lastbit;
	int mask;
	int f,f1,f2,g,h,i,rr,q,lbx;
	if(x==0) return 0; //special case 1 : x is 0.
	if(x == 0x80000000) { //special case 2 : x is tmin. we can't negate this value.
		return 0xcf000000;
	}
	result = result | b; // mark sign bit.
	if(b) {
		tx = -x; // let's consider only positive value.
	}
	qtx = tx;
	while(qtx/=2) { // get E value.
		cc=cc+1;
	}
	//cc will be Exp value.
	lastbit = cc-0x7f; //last bit is E value.
	mask = (1<<lastbit) - 1;
	//get other bit under 'lastbit'.
	q = (mask & tx);
	lbx = 23-lastbit;
	if(lastbit<=23) {
		//less than 24 bits remain, then, M is just q<<lbx.
		result = result + (q<<lbx);
	} else {
		f = -lbx;
		f1 = f-1;
		f2 = 1<<f1;
		g = q & (f2-1);
		h = q & (1<<(f));
		i = q & (f2);
		rr = q >> (f);
		//rounding.
		//g : check under (lastbit-25) bit. if g is non-zero, there is a bit under the (lastbit-25) bit.
		//h : check (lastbit-23) bit. if h is non-zero, even-rounding is possible.
		//i : check (lastbit-24) bit. it's essential for round-up.
		rr = rr + (i && (g || h));	
		result = result | rr;
	}
	//add Exp bits.
	result = result + (cc<<23);
	return result;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  	//uf = +-0 case.
	if(uf==0 || uf == 0x80000000) return uf;
	//NaN case.
	if(((uf>>23) & 0xff) == 0xff) return uf;
	//Tiny value, but non-zero case.
	if(((uf>>23) & 0xff) == 0x00) {
		return (uf & (1<<31)) | (uf<<1);
	}
	//Otherwise, Add 1 to exp value.
	return uf + (1<<23);
}
