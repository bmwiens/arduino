/*
  LCD Display with I2C Interface Demo
  lcd-i2c-demo.ino
  Use NewLiquidCrystal Library
  DroneBot Workshop 2018
  https://dronebotworkshop.com
*/
#include <arduino.h>
// Include Wire Library for I2C
#include <Wire.h>
// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            9

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS     2
// Define LCD pinout
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500; // delay for half a second

const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// Define I2C Address - change if reqiuired
const int i2c_addr = 0x3F;

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

void setup()
{

  // Set display type as 16 char, 2 rows
  lcd.begin(20,4);
  pixels.begin();


}


void loop()
{

  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,150,150)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
  // Print on first row
  lcd.setCursor(0,0);
  lcd.print("Hello world!");



  // Print on second row
  lcd.setCursor(0,1);
  lcd.print("abcdefghijklmnopqrst");

    // Print on Third row
  lcd.setCursor(0,2);
  lcd.print("uvwxyz0123456789!@#$");

     // Print on Fourth row
  lcd.setCursor(0,3);
  lcd.print("**************");

  // Wait 8 seconds
  delay(2000);

  // Clear the display
  lcd.clear();

}
