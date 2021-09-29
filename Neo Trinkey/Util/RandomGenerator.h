// RandomGenerator.h

#ifndef _RANDOMGENERATOR_h
#define _RANDOMGENERATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class RandomGenerator
{
 protected:

 public:
	void CreateSecret(int numBytes);
};

extern RandomGenerator random_generator;

#endif

