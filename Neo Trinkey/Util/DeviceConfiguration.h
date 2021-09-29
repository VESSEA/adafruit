// DeviceConfiguration.h

#ifndef _DEVICECONFIGURATION_h
#define _DEVICECONFIGURATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define CLOCK_LAPS 60000

class DeviceConfiguration
{
 protected:

 public:
	unsigned long time_laps = CLOCK_LAPS;
	static void read_flash();
	static void write_flash();
};

extern DeviceConfiguration device_configuration;

#endif

