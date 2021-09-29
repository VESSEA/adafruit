#include <Keyboard.h>
#include <Mouse.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_FreeTouch.h>

// Create the neopixel strip with the built in definitions NUM_NEOPIXEL and PIN_NEOPIXEL
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NEOPIXEL, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// Create the two touch pads on pins 1 and 2:
Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(1, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_2 = Adafruit_FreeTouch(2, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

unsigned long timer = 0;
unsigned long timerInterval = 60000;

#define NUMPIXELS 16 // Popular NeoPixel ring size

void setup()
{
	Serial.begin(9600);
	//while (!Serial);
	strip.begin();
	//strip.setBrightness(neo_brightness);
	strip.show(); // Initialize all pixels to 'off'

	// initialize control over the keyboard:
	Keyboard.begin();

	if (!qt_1.begin())
		Serial.println("Failed to begin qt on pin 1");
	if (!qt_2.begin())
		Serial.println("Failed to begin qt on pin 2");
}

uint32_t Wheel(byte WheelPos)
{
	if (WheelPos < 85)
	{
		return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	}
	else if (WheelPos < 170)
	{
		WheelPos -= 85;
		return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	else
	{
		WheelPos -= 170;
		return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
}

void WheelCycle()
{
	for (uint16_t j = 0; j < 256; j++)
	{
		// cycles of all colors on wheel
		for (uint16_t i = 0; i < strip.numPixels(); i++)
		{
			strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
		}
		strip.show();
		//delay(10);
	}
}

void MoveCycle()
{

	if (millis() >= timer)
	{
		timer += timerInterval;

		Serial.println(millis());
		Serial.println("Time reached!");
		Mouse.move(1, 1, 0);

		strip.clear(); // Set all pixel colors to 'off'

		for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
			strip.setPixelColor(i, strip.Color(0, 0, 20));
			strip.show();   // Send the updated pixel colors to the hardware.
			delay(100); // Pause before next pass through loop
			strip.clear(); // Set all pixel colors to 'off'
		}

	}
}

void theaterChaseRainbow(int wait) {
	strip.setBrightness(20);
	int firstPixelHue = 0;     // First pixel starts at red (hue 0)
	for (int a = 0; a < 30; a++) {  // Repeat 30 times...
		for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
			strip.clear();         //   Set all pixels in RAM to 0 (off)
			// 'c' counts up from 'b' to end of strip in increments of 3...
			for (int c = b; c < strip.numPixels(); c += 3) {
				// hue of pixel 'c' is offset by an amount to make one full
				// revolution of the color wheel (range 65536) along the length
				// of the strip (strip.numPixels() steps):
				int      hue = firstPixelHue + c * 65536L / strip.numPixels();
				uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
				strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
			}
			strip.show();                // Update strip with new contents
			delay(wait);                 // Pause for a moment
			firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
		}
	}
	strip.setBrightness(0);
	strip.show();
}

void loop()
{
	MoveCycle();

	if (qt_1.measure() > 500)
	{
		Keyboard.print("");
		strip.setBrightness(20);
		WheelCycle();
		delay(1000);
		strip.setBrightness(0);
		WheelCycle();
	}

	if (qt_2.measure() > 500)
	{
		Keyboard.print("");
		strip.setBrightness(20);
		WheelCycle();
		delay(1000);
		strip.setBrightness(0);
		WheelCycle();
		//theaterChaseRainbow(10);
		//Mouse.move(1, 1, 0);
		//strip.setBrightness(20);
		//WheelCycle();
		//delay(1000);
		//strip.setBrightness(0);
		//WheelCycle();
	}

}
