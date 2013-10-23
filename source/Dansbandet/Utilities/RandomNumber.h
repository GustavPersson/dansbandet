#pragma once

/* Period parameters */  
#define MATH_N 624
#define MATH_M 397
#define MATH_MATRIX_A 0x9908b0df   /* constant vector a */
#define MATH_UPPER_MASK 0x80000000 /* most significant w-r bits */
#define MATH_LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */   
#define MATH_TEMPERING_MASK_B 0x9d2c5680
#define MATH_TEMPERING_MASK_C 0xefc60000
#define MATH_TEMPERING_SHIFT_U(y)  (y >> 11)
#define MATH_TEMPERING_SHIFT_S(y)  (y << 7)
#define MATH_TEMPERING_SHIFT_T(y)  (y << 15)
#define MATH_TEMPERING_SHIFT_L(y)  (y >> 18)

class RandomNumber
{
private:
	unsigned int rseed;
	unsigned int rseed_sp;
	unsigned long mt[MATH_N];
	int mti;


public:
	RandomNumber(void);
	unsigned int random(unsigned int n);
	float random();
	void setRandomSeed(unsigned int n);
	unsigned int getRandomSeed(void);
	void randomize();
	virtual ~RandomNumber(void);
};