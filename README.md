# Air Sensor

## Prerequisites

### Hardware

The following hardware is being used in this project:

- ESP32 C3 Super Mini ([Drivers](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads))
  ![Pinout](docs/image.png)
- BME280
- I2C Display

### Libraries

This project requires the following libraries:

- BME280 by Adafruit
- U8g2 by Oliver

> [!IMPORTANT]
> Besides the libraries, additional configuration steps are required in order to upload the program to the ESP32. The [`platformio.ini`](platformio.ini) file sets everything up automatically if the project is opened in **Visual Studio Code** with the **PlatformIO** extension installed.
