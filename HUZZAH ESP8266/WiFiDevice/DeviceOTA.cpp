// 
// 
// 

#include "DeviceOTA.h"

void DeviceOTA::setup() const
{
	//DeviceDisplay::setup();

	Serial.println("Booting");
	device_display.printLine("Booting");

	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	while (WiFi.waitForConnectResult() != WL_CONNECTED)
	{
		Serial.println("Connection Failed! Rebooting...");
		device_display.printLine("Connection Failed! Rebooting...");

		delay(5000);
		ESP.restart();
	}

	// Port defaults to 8266
	// ArduinoOTA.setPort(8266);

	// Hostname defaults to esp8266-[ChipID]
	// ArduinoOTA.setHostname("myesp8266");

	// No authentication by default
	// ArduinoOTA.setPassword("admin");

	// Password can be set with it's md5 value as well
	// MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
	// ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

	ArduinoOTA.onStart([]()
	{
		String type;
		if (ArduinoOTA.getCommand() == U_FLASH)
		{
			type = "sketch";
		}
		else
		{
			// U_FS
			type = "filesystem";
		}

		// NOTE: if updating FS this would be the place to unmount FS using FS.end()
		Serial.println("Start updating " + type);
	});
	ArduinoOTA.onEnd([]()
	{
		Serial.println("\nEnd");
	});
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
	{
		Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
	});
	ArduinoOTA.onError([](ota_error_t error)
	{
		Serial.printf("Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR)
		{
			Serial.println("Auth Failed");
		}
		else if (error == OTA_BEGIN_ERROR)
		{
			Serial.println("Begin Failed");
		}
		else if (error == OTA_CONNECT_ERROR)
		{
			Serial.println("Connect Failed");
		}
		else if (error == OTA_RECEIVE_ERROR)
		{
			Serial.println("Receive Failed");
		}
		else if (error == OTA_END_ERROR)
		{
			Serial.println("End Failed");
		}
	});
	ArduinoOTA.begin();
	Serial.println("Ready");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());


	//https://stackoverflow.com/questions/55804381/how-do-i-convert-wifi-localip-to-string-and-store-it-to-external-variable
	//https://gist.github.com/loosak/76019faaefd5409fca67

	IPAddress ip = WiFi.localIP();
	char buffer[50];
	sprintf(buffer, "IP V8: %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
	//sprintf(buffer, 0, 10, " IP address: " + WiFi.localIP().toString());

	//device_display.printLine(buffer);

	device_display.display.clearDisplay();
	device_display.display.display();
	device_display.display.setTextSize(1);
	device_display.display.setTextColor(SH110X_WHITE);
	device_display.display.setCursor(0, 0);
	device_display.display.println(buffer);
	device_display.display.display(); // actually display all of the above

}

void DeviceOTA::check()
{
	ArduinoOTA.handle();
}

DeviceOTA device_ota;

