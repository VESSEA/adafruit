// DeviceOTA.h

#ifndef _DEVICEOTA_h
#define _DEVICEOTA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "DeviceDisplay.h"

#ifndef STASSID
#define STASSID "SSID"
#define STAPSK  "PASS"
#endif

class DeviceOTA
{
 protected:
	 const char* ssid = STASSID;
	 const char* password = STAPSK;

 public:
	void setup() const;
	 static void check();
};

extern DeviceOTA device_ota;

#endif

