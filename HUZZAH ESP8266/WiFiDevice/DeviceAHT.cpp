// 
// 
// 

#include "DeviceAHT.h"

void DeviceAHT::setup()
{
    if (aht.begin()) {
        Serial.println("Found AHT20");
    }
    else {
        Serial.println("Didn't find AHT20");
    }

}

void DeviceAHT::check()
{
    //device_display.display.

    sensors_event_t humidity, temp;

    aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data

    IPAddress ip = WiFi.localIP();
    char buffer[50];
    sprintf(buffer, "IP V8: %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

    device_display.display.clearDisplay();

    device_display.display.setCursor(0, 10);
    device_display.display.println(buffer);

    device_display.display.setCursor(0, 20);
    device_display.display.print("Temp: "); device_display.display.print(temp.temperature); device_display.display.println(" C");

    device_display.display.setCursor(0, 30);
    device_display.display.print("Hum: "); device_display.display.print(humidity.relative_humidity); device_display.display.println(" %");

    yield();
    device_display.display.display();
    delay(100);
}

DeviceAHT device_aht;

