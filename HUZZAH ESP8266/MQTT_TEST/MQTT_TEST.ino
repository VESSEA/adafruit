/***************************************************
  Adafruit MQTT Library ESP8266 Adafruit IO SSL/TLS example

  Must use the latest version of ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  SSL/TLS additions by Todd Treece for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "bsec.h"
#include "Wire.h"
#include "SPI.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_I2CDevice.h>
#include <Arduino_JSON.h>

 /*****************^************** OLED *****************^**********************/
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

 /*****************^************** BSEC *****************^**********************/
// Create an object of the class Bsec
Bsec iaqSensor;
String output;

 /************************* WiFi Access Point *********************************/
#define WLAN_SSID       "SSID"
#define WLAN_PASS       "PASS"

/************************* Adafruit.io Setup *********************************/
#define AIO_SERVER      "io.adafruit.com"
// Using port 8883 for MQTTS
#define AIO_SERVERPORT  8883
// Adafruit IO Account Configuration
// (to obtain these values, visit https://io.adafruit.com and click on Active Key)
#define AIO_USERNAME    "USER"
#define AIO_KEY         "KEY"

/************ Global State (you don't need to change this!) ******************/

// WiFiFlientSecure for SSL/TLS support
WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// io.adafruit.com SHA1 fingerprint
static const char* fingerprint PROGMEM = "59 3C 48 0A B1 8B 39 4E 0D 58 50 47 9A 13 55 60 CC A0 1D AF";

/****************************** Feeds ***************************************/

// Setup a feed called 'test' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish test = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/test");

// JSON message creation part
#define STATIC_MESSAGE_BUF_LEN 256

JSONVar message_object;         // to store message parameters
String json_msg_string;         // to stringify JSON message object
char message_string_buf[STATIC_MESSAGE_BUF_LEN];   // to use in mqtt publish function

void setup() {
    Serial.begin(115200);
    delay(10);

    Serial.println(F("Adafruit IO MQTTS (SSL/TLS) Example"));

    // Connect to WiFi access point.
    Serial.println(); Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WLAN_SSID);

    delay(1000);

    WiFi.begin(WLAN_SSID, WLAN_PASS);
    delay(2000);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.println("WiFi connected");
    Serial.println("IP address: "); Serial.println(WiFi.localIP());

    // check the fingerprint of io.adafruit.com's SSL cert
    client.setFingerprint(fingerprint);

    /*****************^************** BSEC *****************^**********************/
    display.begin(0x3C, true); // Address 0x3C default

    display.display();
    delay(100);
    display.clearDisplay();
    display.display();
    display.setRotation(1);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);

    iaqSensor.begin(BME680_I2C_ADDR_SECONDARY, Wire);
    output = "\nBSEC library version " + String(iaqSensor.version.major) + "." + String(iaqSensor.version.minor) + "." + String(iaqSensor.version.major_bugfix) + "." + String(iaqSensor.version.minor_bugfix);
    Serial.println(output);
    checkIaqSensorStatus();
    bsec_virtual_sensor_t sensorList[10] = {
      BSEC_OUTPUT_RAW_TEMPERATURE,
      BSEC_OUTPUT_RAW_PRESSURE,
      BSEC_OUTPUT_RAW_HUMIDITY,
      BSEC_OUTPUT_RAW_GAS,
      BSEC_OUTPUT_IAQ,
      BSEC_OUTPUT_STATIC_IAQ,
      BSEC_OUTPUT_CO2_EQUIVALENT,
      BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
      BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
      BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
    };

    iaqSensor.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP);
    checkIaqSensorStatus();
    // Print the header
    output = "Timestamp [ms], raw temperature [°C], pressure [hPa], raw relative humidity [%], gas [Ohm], IAQ, IAQ accuracy, temperature [°C], relative humidity [%], Static IAQ, CO2 equivalent, breath VOC equivalent";
    Serial.println(output);
}

uint32_t x = 0;

void loop() {

    display.setCursor(0, 0);
    display.clearDisplay();

    unsigned long time_trigger = millis();
    if (!iaqSensor.run()) { // If no data is available
        checkIaqSensorStatus();
        return;
    }

    output = String(time_trigger);
    output += ", " + String(iaqSensor.rawTemperature);
    output += ", " + String(iaqSensor.pressure);
    output += ", " + String(iaqSensor.rawHumidity);
    output += ", " + String(iaqSensor.gasResistance);
    output += ", " + String(iaqSensor.iaq);
    output += ", " + String(iaqSensor.iaqAccuracy);
    output += ", " + String(iaqSensor.temperature);
    output += ", " + String(iaqSensor.humidity);
    output += ", " + String(iaqSensor.staticIaq);
    output += ", " + String(iaqSensor.co2Equivalent);
    output += ", " + String(iaqSensor.breathVocEquivalent);
    Serial.println(output);

    Serial.print("Temperature = "); Serial.print(iaqSensor.temperature); Serial.println(" *C");
    display.print("Temperature: "); display.print(iaqSensor.temperature); display.println(" *C");

    Serial.print("Pressure = "); Serial.print(iaqSensor.pressure / 100.0); Serial.println(" hPa");
    display.print("Pressure: "); display.print(iaqSensor.pressure / 100); display.println(" hPa");

    Serial.print("Humidity = "); Serial.print(iaqSensor.humidity); Serial.println(" %");
    display.print("Humidity: "); display.print(iaqSensor.humidity); display.println(" %");

    Serial.print("IAQ = "); Serial.print(iaqSensor.staticIaq); Serial.println("");
    display.print("IAQ: "); display.print(iaqSensor.staticIaq); display.println("");

    Serial.print("CO2 equiv = "); Serial.print(iaqSensor.co2Equivalent); Serial.println("");
    display.print("CO2eq: "); display.print(iaqSensor.co2Equivalent); display.println("");

    Serial.print("Breath VOC = "); Serial.print(iaqSensor.breathVocEquivalent); Serial.println("");
    display.print("VOC: "); display.print(iaqSensor.breathVocEquivalent); display.println("");

    Serial.println();
    display.display();

    // Ensure the connection to the MQTT server is alive (this will make the first
    // connection and automatically reconnect when disconnected).  See the MQTT_connect
    // function definition further below.
    MQTT_connect();

    message_object["temperature"] = iaqSensor.temperature;
    message_object["humidity"] = iaqSensor.humidity;
    json_msg_string = JSON.stringify(message_object);
    json_msg_string.toCharArray(message_string_buf, json_msg_string.length() + 1);

	Serial.println(message_string_buf);
    
    if (!test.publish(message_string_buf)) {
        Serial.println(F("Failed"));
    }
    else {
        Serial.println(F("OK!"));
    }

    //if (!test.publish(iaqSensor.temperature)) {
    //    Serial.println(F("Failed"));
    //}
    //else {
    //    Serial.println(F("OK!"));
    //}

    // Now we can publish stuff!
    //Serial.print(F("\nSending val "));
    //Serial.print(x);
    //Serial.print(F(" to test feed..."));
    //if (!test.publish(x++)) {
    //    Serial.println(F("Failed"));
    //}
    //else {
    //    Serial.println(F("OK!"));
    //}

    // wait a couple seconds to avoid rate limit
    delay(2000);

}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
    int8_t ret;

    // Stop if already connected.
    if (mqtt.connected()) {
        return;
    }

    Serial.print("Connecting to MQTT... ");

    uint8_t retries = 3;
    while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
        Serial.println(mqtt.connectErrorString(ret));
        Serial.println("Retrying MQTT connection in 5 seconds...");
        mqtt.disconnect();
        delay(5000);  // wait 5 seconds
        retries--;
        if (retries == 0) {
            // basically die and wait for WDT to reset me
            while (1);
        }
    }

    Serial.println("MQTT Connected!");
}

// Helper function definitions
void checkIaqSensorStatus(void)
{
    if (iaqSensor.status != BSEC_OK) {
        if (iaqSensor.status < BSEC_OK) {
            output = "BSEC error code : " + String(iaqSensor.status);
            Serial.println(output);
            display.setCursor(0, 0);
            display.println(output);
            display.display();
            for (;;)  delay(10);
        }
        else {
            output = "BSEC warning code : " + String(iaqSensor.status);
            Serial.println(output);
        }
    }

    if (iaqSensor.bme680Status != BME680_OK) {
        if (iaqSensor.bme680Status < BME680_OK) {
            output = "BME680 error code : " + String(iaqSensor.bme680Status);
            Serial.println(output);
            display.setCursor(0, 0);
            display.println(output);
            display.display();
            for (;;)  delay(10);
        }
        else {
            output = "BME680 warning code : " + String(iaqSensor.bme680Status);
            Serial.println(output);
        }
    }
}
