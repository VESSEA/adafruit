// DeviceClock.h

#ifndef _DEVICECLOCK_h
#define _DEVICECLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class DeviceClock
{
 protected:


 public:
	static void run();
};

extern DeviceClock device_clock;

#endif

