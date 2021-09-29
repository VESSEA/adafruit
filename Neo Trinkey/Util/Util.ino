/*
File:
Author: Matthew David Elgert
Create Date: 9/28/2021
Last Updated: 9/28/2021
Note:
*/

#include "RandomGenerator.h"
#include "DeviceClock.h"
#include "MenuMain.h"

void setup() {
	Serial.begin(9600);
}

void loop() {
	//menu_main.read();
	//DeviceClock::run();
	random_generator.CreateSecret(20);
}
