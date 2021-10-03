#include "DeviceOTA.h"
#include "DeviceDisplay.h"

//int i = 1;

void setup() {
	Serial.begin(115200);
	DeviceDisplay::setup();
	device_ota.setup();
}

void loop() {
	DeviceOTA::check();
	//char integer_string[10];
	//sprintf(integer_string, "%d", i);
	//char other_string[20] = "Test: "; // make sure you allocate enough space to append the other string
	//strcat(other_string, integer_string); // other_string now contains "Integer: 1234"
	//device_display.printLine(other_string);
	//delay(1000);
	//i = i + 1;
}