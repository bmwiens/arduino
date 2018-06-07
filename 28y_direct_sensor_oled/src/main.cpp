//Include Arduino Library
#include <Arduino.h>
//Include the Arduino Stepper Library
#include <Stepper.h>
//Libraries for serial display
#include <U8x8lib.h>

// Define Constants

// Number of steps per internal motor revolution
const float STEPS_PER_REV = 32;

//  Amount of Gear Reduction
const float GEAR_RED = 64;

// Number of steps per geared output rotation
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);
//U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);
// Define Variables

// Number of Steps Required
int StepsRequired;
int HomepinStatus;
int HomepinLastStatus;
int Homepin=2;
// Create Instance of Stepper Class
// Specify Pins used for motor coils
// The pins used are 8,9,10,11
// Connected to ULN2003 Motor Driver In1, In2, In3, In4
// Pins entered in sequence 1-3-2-4 for proper step sequencing

Stepper steppermotor(STEPS_PER_REV, 8, 10, 9, 11);

void setup()
{
  Serial.begin(115200);
  pinMode(Homepin, INPUT_PULLUP);
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,0,"Hello World!");
  HomepinStatus = digitalRead(Homepin);
  HomepinLastStatus = HomepinStatus;
  //u8x8.clear();
  //u8x8.setCursor(0,0);
  //u8x8.print(HomepinStatus);

// Nothing  (Stepper Library sets pins as outputs)
}

void loop()
{
  HomepinStatus = digitalRead(Homepin);
  if(HomepinStatus == LOW)
  {
    //u8x8.clear();
    u8x8.setCursor(0,0);
    u8x8.print("Pin Status: ");
    u8x8.setCursor(12,0);
    u8x8.print(HomepinStatus);
    HomepinLastStatus=HomepinStatus;
  }
  else
  {
    //u8x8.clear();
    u8x8.setCursor(0,0);
    u8x8.print("Pin Status: ");
    u8x8.setCursor(12,0);
    u8x8.print(HomepinStatus);
  }
  // Slow - 4-step CW sequence to observe lights on driver board
  // steppermotor.setSpeed(1);
  // StepsRequired  =  4;
  // steppermotor.step(StepsRequired);
  // delay(2000);

   // Rotate CW 1/2 turn slowly
   StepsRequired  =  STEPS_PER_OUT_REV ;
  // steppermotor.step(StepsRequired);
  // delay(1000);

  // Rotate CCW 1/2 turn quickly
  // StepsRequired  =  - STEPS_PER_OUT_REV / 2;
  // steppermotor.setSpeed(700);
  // steppermotor.step(StepsRequired);
  // delay(5000);

}
