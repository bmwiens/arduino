#include <Arduino.h>
// DualMotorShield.pde
// -*- mode: C++ -*-
//
// Shows how to run 2 simultaneous steppers
// using the Itead Studio Arduino Dual Stepper Motor Driver Shield
// model IM120417015
// This shield is capable of driving 2 steppers at 
// currents of up to 750mA
// and voltages up to 30V
// Runs both steppers forwards and backwards, accelerating and decelerating
// at the limits.
//
// Copyright (C) 2014 Mike McCauley
// $Id:  $

#include <AccelStepper.h>
#include <U8x8lib.h>

U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

#define EN        8 
// The X Stepper pins
#define STEPPER1_DIR_PIN 5
#define STEPPER1_STEP_PIN 2
// The Y stepper pins
#define STEPPER2_DIR_PIN 6
#define STEPPER2_STEP_PIN 3

int homingcomplete = 0;
int homingDrumcomplete = 0;
int homingHoppercomplete = 0;

int sensorDrum = 9; //sensor pin
int sensorHopper = 10; //sensor pin
int drumStatus=0;
int hopperStatus=0;
//int sensorZ = 11; //sensor pin
byte val1; //numeric variable
byte val2; //numeric variable
//byte val3; //numeric variable
int countdrum=0;
int counthopper=0;
// Define some steppers and the pins the will use
AccelStepper Drum(1, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);
AccelStepper Hopper(1, STEPPER2_STEP_PIN, STEPPER2_DIR_PIN);


void homemotors()
{
while(!homingcomplete)
    {
          u8x8.setCursor(0, 5);
          u8x8.print(homingDrumcomplete);
          u8x8.setCursor(0, 6);
          u8x8.print(homingHoppercomplete);
        u8x8.drawString(0,1,"Homing drum...");
        Drum.setMaxSpeed(2000.0);
        Drum.moveTo(6400);
        Drum.run();
        while(!homingDrumcomplete)
        {
            drumStatus = digitalRead(sensorDrum);
            if(drumStatus == LOW)
            {
                Drum.setSpeed(0);
                Hopper.setMaxSpeed(2000.0);
        Hopper.setSpeed(1500);
        Hopper.runSpeed();
                u8x8.drawString(0,1,"Homing drum: Done");
                homingDrumcomplete=1;
                u8x8.drawString(0,2,"Homing hopper...");
            }
        }
        while(!homingHoppercomplete)
        {
            hopperStatus = digitalRead(sensorHopper);
            if(hopperStatus == LOW)
            {
                Drum.setSpeed(0);
                u8x8.drawString(0,2,"Homing hopper: Done");
                homingHoppercomplete=1;
            }
        }
        if (homingHoppercomplete && homingDrumcomplete)
        {
            u8x8.drawString(0,0,"Homing Complete");
            homingcomplete = 1;
        }
    }
}


void setup()
{  
    Serial.begin(115200);
    u8x8.begin();
    u8x8.setPowerSave(0);
    u8x8.setFont(u8x8_font_pxplusibmcga_f);
    //u8x8.drawString(0,0,"Hello World!");
    
    pinMode(EN, OUTPUT);
    digitalWrite(EN, LOW);

    
	pinMode(sensorDrum, INPUT_PULLUP); //set sensor pin as input
    pinMode(sensorHopper, INPUT_PULLUP); //set sensor pin as input
    //pinMode(sensorZ, INPUT_PULLUP);//set sensor pin as input
    
    u8x8.drawString(0,0,"Homing Motors...");
    

    Drum.setMaxSpeed(2000.0);
    Drum.setSpeed(2000);
    //stepper1.setAcceleration(200.0);
    //stepper1.moveTo(6400);
    
    Hopper.setMaxSpeed(2000.0);
    Hopper.setSpeed(2000);
    //stepper2.setAcceleration(100.0);
    //stepper2.moveTo(6400);
    
    u8x8.drawString(0,0,"sensorDrum: ");
    u8x8.drawString(0,1,"sensorHopper: ");
   // u8x8.drawString(0,2,"sensorZ: ");

}

void loop()
{
  Drum.runSpeed();
  Hopper.runSpeed();
    homemotors();
    val1 = digitalRead(sensorDrum); //Read the sensor
    val2 = digitalRead(sensorHopper); //Read the sensor
    //val3 = digitalRead(sensorZ); //Read the sensor


    
    if(val1==LOW)
    {
    //     countdrum ++;
    //      u8x8.drawString(0,0,"D Count:");
    //      u8x8.setCursor(8, 0);
    //      u8x8.print(countdrum);
         
        u8x8.drawString(12,0,"L");
        // Drum.setSpeed(0);
        // Hopper.setSpeed(1500);
        
    }
    else 
    {
        u8x8.drawString(12,0,"H");
    }
    if(val2==LOW)
    {
        //  counthopper ++;
        //  u8x8.drawString(0,1,"H Count:");
        //  u8x8.setCursor(8, 1);
        //  u8x8.print(counthopper);
         u8x8.drawString(14,1,"L");
        // Drum.setSpeed(1500);
        // Hopper.setSpeed(0);
    }
    else
    {
        u8x8.drawString(14,1,"H");
    }
    // if(val3==LOW)
    // {
    //     u8x8.drawString(9,2,"L");
    // }
    // else
    // {
    //     u8x8.drawString(9,2,"L");
    // }
    
	
}