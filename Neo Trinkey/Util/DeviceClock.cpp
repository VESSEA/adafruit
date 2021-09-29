// 
// 
// 

#include "DeviceClock.h"
#include "DeviceConfiguration.h"
#include <Mouse.h>

void DeviceClock::run()
{
	if (millis() >= device_configuration.time_laps)
	{
		device_configuration.time_laps += CLOCK_LAPS;
		//Serial.println("Timer reached millis = " + String(millis()) + " device_configuration.time_laps = " + String(device_configuration.time_laps));
		Mouse.move(1, 1, 0);
	}
}

DeviceClock device_clock;

