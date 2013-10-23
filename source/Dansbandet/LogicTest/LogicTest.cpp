#ifndef __LOGICTEST_LOGICTEST_CPP__
#define __LOGICTEST_LOGICTEST_CPP__

#include "../Utilities/Macros.h"
#include "../Utilities/RandomNumber.h"


int main() {
	initMemoryCheck();
	RandomNumber* mRandomNumber;

	mRandomNumber = new RandomNumber();

	for (int i= 0; i < 15; i++) {
		std::cout << mRandomNumber->random(11) << "\n";
	}
	std::cout << "nr 2\n";
	for (int i= 0; i < 15; i++) {
		std::cout << mRandomNumber->random(11) << "\n";
	}
	std::cout << "nr 23\n";
	mRandomNumber->setRandomSeed(123);
	for (int i= 0; i < 15; i++) {
		std::cout << mRandomNumber->random(11) << "\n";
	}

	return 0;
}

#endif