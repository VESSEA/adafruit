/*
File:
Author: Matthew David Elgert
Create Date: 9/28/2021
Last Updated: 9/28/2021
Note:
*/

#include "MenuConfiguration.h"
#include "MenuMain.h"

void setup() {
	Serial.begin(9600);
}

void loop() {
	menu_main.read();
}
