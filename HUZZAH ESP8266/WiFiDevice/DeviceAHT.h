// DeviceAHT.h

#ifndef _DEVICEAHT_h
#define _DEVICEAHT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Adafruit_AHTX0.h>
#include <ESP8266WiFi.h>

#include "DeviceDisplay.h"

class DeviceAHT
{

 protected:
	 Adafruit_AHTX0 aht;
 public:
	void setup();
	void check();
};

extern DeviceAHT device_aht;

#endif

