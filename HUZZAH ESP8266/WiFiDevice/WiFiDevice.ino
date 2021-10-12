//#include "Configs.h"
#include "DeviceAHT.h"
#include "DeviceOTA.h"
#include "DeviceDisplay.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SH110X.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_Sensor.h>
#include <Fonts/FreeSans9pt7b.h>

//int i = 1;


void setup() {
	Serial.begin(115200);
	device_display.setup();
	device_ota.setup();
	device_aht.setup();
}

void loop() {

	//device_display.display.print("TEST");
	//device_display.display.clearDisplay();
	//device_display.display.display();
	//device_display.display.setTextSize(1);
	//device_display.display.setTextColor(SH110X_WHITE);
	//device_display.display.setCursor(0, 0);
	//device_display.display.display(); // actually display all of the above
	//delay(1000);

	DeviceOTA::check();

	device_aht.check();

	//char integer_string[10];
	//sprintf(integer_string, "%d", i);
	//char other_string[20] = "Test: "; // make sure you allocate enough space to append the other string
	//strcat(other_string, integer_string); // other_string now contains "Integer: 1234"
	//device_display.printLine(other_string);
	//delay(1000);
	//i = i + 1;
}