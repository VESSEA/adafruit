// 
// 
// 

#include "DeviceDisplay.h"

//Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
//Adafruit_SH1107 display(64, 128, &Wire);

void DeviceDisplay::setup()
{
	display.begin(0x3C, true); // Address 0x3C default

	// Show image buffer on the display hardware.
	// Since the buffer is intialized with an Adafruit splashscreen
	// internally, this will display the splashscreen.
	display.display();
	delay(1000);

	// Clear the buffer.
	display.clearDisplay();
	display.display();

	display.setRotation(1);

	//Serial.println("Button test");

	pinMode(BUTTON_A, INPUT_PULLUP);
	pinMode(BUTTON_B, INPUT_PULLUP);
	pinMode(BUTTON_C, INPUT_PULLUP);

	// text display tests
	//display.setTextSize(1);
	//display.setTextColor(SH110X_WHITE);
	//display.setCursor(0, 0);
	//display.println("OLED setup");
	//display.display(); // actually display all of the above
}

void DeviceDisplay::printLine(const char* value)
{
	display.clearDisplay();
	display.display();
	display.setTextSize(1);
	display.setTextColor(SH110X_WHITE);
	display.setCursor(0, 0);
	display.println(value);
	display.display(); // actually display all of the above
}

DeviceDisplay device_display;

