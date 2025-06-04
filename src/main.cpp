#define VERSION "0.1.0-development.1l"

#define SEA_LEVEL_PRESSURE_HPA 1013.25
#define STATUS_LED 8

#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <U8g2lib.h>

void spinner();
void toggle(int pin);

// Sensor
Adafruit_BME280 bme;

// Display
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;
  pinMode(STATUS_LED, OUTPUT);
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setFontMode(1); // Enable font mode for text rendering
  u8g2.setCursor(0, 10);
  u8g2.print("HTL AirSensor ");
  u8g2.print(VERSION);
  u8g2.sendBuffer();
}

void loop()
{
  static bool bmeConnected = false;

  delay(100);

  toggle(STATUS_LED);

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
