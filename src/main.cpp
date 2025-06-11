#define VERSION "0.1.0-development.3"

#define SEA_LEVEL_PRESSURE_HPA 1013.25
#define STATUS_LED 8
#define DEGREE "" // 0xB0
#define START_ROW 30
#define NAME_COL 0
#define VALUE_COL 50
#define UNIT_COL 95

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

  pinMode(STATUS_LED, OUTPUT);
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setFontMode(1); // Enable font mode for text rendering
}

void loop()
{
  static bool bmeConnected = false;

  toggle(STATUS_LED);

  delay(2000);

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

  Serial.println();

  Serial.print("Temperature \t");
  Serial.print(temperature);
  Serial.print("\t ");
  Serial.print(DEGREE);
  Serial.println("C");

  Serial.print("Humidity \t");
  Serial.print(humidity);
  Serial.println("\t %");

  Serial.print("Pressure \t");
  Serial.print(pressure / 100.0F);
  Serial.println("\t hPa");

  Serial.print("Altitude \t");
  Serial.print(altitude);
  Serial.println("\t m");

  // Display the data on the display
  u8g2.clearBuffer();

  u8g2.setCursor(0, 10);
  u8g2.print("HTL AirSensor ");
  u8g2.print(VERSION);

  u8g2.setCursor(NAME_COL, START_ROW);
  u8g2.print("TEMP:");
  u8g2.setCursor(VALUE_COL, START_ROW);
  u8g2.print(temperature);
  u8g2.setCursor(UNIT_COL, START_ROW);
  u8g2.print(DEGREE);
  u8g2.print("C");

  u8g2.setCursor(NAME_COL, START_ROW + 10);
  u8g2.print("HUM:");
  u8g2.setCursor(VALUE_COL, START_ROW + 10);
  u8g2.print(humidity);
  u8g2.setCursor(UNIT_COL, START_ROW + 10);
  u8g2.print("%");

  u8g2.setCursor(NAME_COL, START_ROW + 20);
  u8g2.print("PRES:");
  u8g2.setCursor(VALUE_COL, START_ROW + 20);
  u8g2.print(pressure / 100.0F);
  u8g2.setCursor(UNIT_COL, START_ROW + 20);
  u8g2.print("hPa");

  u8g2.setCursor(NAME_COL, START_ROW + 30);
  u8g2.print("ALT:");
  u8g2.setCursor(VALUE_COL, START_ROW + 30);
  u8g2.print(altitude);
  u8g2.setCursor(UNIT_COL, START_ROW + 30);
  u8g2.print("m");

  u8g2.sendBuffer();
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
