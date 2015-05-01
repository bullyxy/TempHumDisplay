// Temperature and Humidity Display v1.0
// Uses 16x2 LCD Display with YwRobot Arduino LCM1602 IIC V1 I2C backpack
// Library for the display can be found here: https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/I2CIO
//
// DHT11 Humidity/Temperature Sensor on 3 Pin breakout board
// is used
// Library can be found here: http://playground.arduino.cc/Main/DHT11Lib

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <dht11.h>

// Setup DHT11
dht11 DHT11;
#define DHT11_PIN 2 // Connect sensor data pin to Arduino UNO pin 2

// Setup the LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Button attached to pin 4
#define BUTTON_PIN 4

void setup() {
  lcd.begin(16, 2); // Init LCD as 16 chars 2 lines display
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button down is 0, button up is 1

  // Start with LCD off
  lcd.noBacklight();
  lcd.off();
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  // Remember that the pushed button pulls to ground
  // through the internal pulldown resistor
  if (buttonState == 0)
  {
    int chk = DHT11.read(DHT11_PIN);

    if (chk == DHTLIB_OK)
    {
      // Read temperature and humidity as
      // floats
      float temp = (float)DHT11.temperature;
      float hum  = (float)DHT11.humidity;

      // Print temperature on first line
      lcd.setCursor(0, 0);
      lcd.print("Temp  ");
      lcd.print(temp);

      // Print humidity on second line
      lcd.setCursor(0, 1);
      lcd.print("Hum   ");
      lcd.print(hum);

      // LCD on for 5 seconds
      lcd.on();
      lcd.backlight();
      delay(5000);
      lcd.off();
      lcd.noBacklight();
    }
  }
}
