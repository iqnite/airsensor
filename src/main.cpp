#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <U8g2lib.h>

#define SEA_LEVEL_PRESSURE_HPA 1013.25

void spinner();

Adafruit_BME280 bme;

void setup()
{
  Serial.begin(9600);
  pinMode(8, OUTPUT);
}

void loop()
{
  static bool bmeConnected = false;

  delay(500);

  if (!bmeConnected)
  {
    bmeConnected = bme.begin(0x76);
    spinner();
    return;
  }

  const float temperature = bme.readTemperature();
  const float pressure = bme.readPressure();
  const float humidity = bme.readHumidity();
  const float altitude = bme.readAltitude(SEA_LEVEL_PRESSURE_HPA);

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Pressure = ");
  Serial.print(pressure / 100.0F);
  Serial.println(" hPa");
  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Approx. Altitude = ");
  Serial.print(altitude);
  Serial.println(" m");
}

void spinner()
{
  static int i = 0;
  static const char *spinnerChars = "|/-\\";
  Serial.print("\r");
  Serial.print("Connecting to BME280 ");
  Serial.print(spinnerChars[i++ % 4]);
}
