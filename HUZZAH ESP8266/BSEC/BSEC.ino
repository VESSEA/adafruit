#include "bsec.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_I2CDevice.h>

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

Bsec iaqSensor;
String output;


void setup() {
    Serial.begin(115200);
    //while (!Serial);

    Serial.println(F("BME680 test"));

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
    delay(2000);
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
