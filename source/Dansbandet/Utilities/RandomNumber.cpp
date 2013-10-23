#include "RandomNumber.h"
#include <time.h>


RandomNumber::RandomNumber(void) {
	rseed = 1;

	rseed_sp = 0;
	mti = MATH_N + 1;
}

unsigned int RandomNumber::random(unsigned int n) {
	
	unsigned long y;
	static unsigned long mag01[2] = {0x0, MATH_MATRIX_A};

	if (n==0)
		return 0;

    if (mti >= MATH_N) { /* generate N words at one time */
        int kk;

        if (mti == MATH_N+1)   /* if sgenrand() has not been called, */
            setRandomSeed(4357); /* a default initial seed is used   */

        for (kk=0;kk<MATH_N-MATH_M;kk++) {
            y = (mt[kk]&MATH_UPPER_MASK)|(mt[kk+1]&MATH_LOWER_MASK);
            mt[kk] = mt[kk+MATH_M] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        for (;kk<MATH_N-1;kk++) {
            y = (mt[kk]&MATH_UPPER_MASK)|(mt[kk+1]&MATH_LOWER_MASK);
            mt[kk] = mt[kk+(MATH_M-MATH_N)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (mt[MATH_N-1]&MATH_UPPER_MASK)|(mt[0]&MATH_LOWER_MASK);
        mt[MATH_N-1] = mt[MATH_M-1] ^ (y >> 1) ^ mag01[y & 0x1];

        mti = 0;
    }
  
    y = mt[mti++];
    y ^= MATH_TEMPERING_SHIFT_U(y);
    y ^= MATH_TEMPERING_SHIFT_S(y) & MATH_TEMPERING_MASK_B;
    y ^= MATH_TEMPERING_SHIFT_T(y) & MATH_TEMPERING_MASK_C;
    y ^= MATH_TEMPERING_SHIFT_L(y);

    // ET - old engine added one to the result.
    // We almost NEVER wanted to use this function
    // like this.  So, removed the +1 to return a 
    // range from 0 to n (not including n).
    return (y%n);


}

float RandomNumber::random() {
    int r = (float)random(0xffffffff);
    float divisor = (float)0xffffffff;
    return (r / divisor) + 0.5f;
}

void RandomNumber::setRandomSeed(unsigned int n) {
      
	/* setting initial seeds to mt[N] using         */
	/* the generator Line 25 of Table 1 in          */
	/* [KNUTH 1981, The Art of Computer Programming */
	/*    Vol. 2 (2nd Ed.), pp102]                  */
	mt[0]= n & 0xffffffff;
	for (mti=1; mti<MATH_N; mti++)
			mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;

	rseed = n;	
}

unsigned int RandomNumber::getRandomSeed(void) {
	return(rseed);
}
void RandomNumber::randomize() {
	setRandomSeed((unsigned int)time(NULL));
}

RandomNumber::~RandomNumber(void)
{
}
