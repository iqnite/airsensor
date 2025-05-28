#define VERSION "0.1.0-dev"

#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <U8g2lib.h>

#define SEA_LEVEL_PRESSURE_HPA 1013.25

void spinner();
void toggle(int pin);

Adafruit_BME280 bme;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  static bool bmeConnected = false;

  delay(500);

  toggle(LED_BUILTIN);

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
  Serial.print(VERSION);
  Serial.print(" | Connecting to sensor ");
  Serial.print(spinnerChars[i++ % 4]);
}

void toggle(int pin)
{
  static bool state = false;
  state = !state;
  digitalWrite(pin, state ? HIGH : LOW);
}
