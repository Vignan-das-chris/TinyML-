#include <Arduino_HTS221.h>

#define READ_TEMPERATURE() HTS.readTemperature()
#define READ_HUMIDITY() HTS.readHumidity()

void setup()
{
    Serial.begin(9600);

    while (!Serial)
        ;

    if (!HTS.begin())
    {

        Serial.println("failed initializing of HTS221!");
        while (1)
            ;
    }

    Serial.print("Test Temperature = ");
    Serial.print(READ_TEMPERATURE(), 2);
    Serial.println(" °C");
    Serial.print("Test Humidity = ");
    Serial.print(READ_HUMIDITY(), 2);
    Serial.println(" %");
}

void loop()
{
    delay(2000);
}