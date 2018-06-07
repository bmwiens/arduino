

/******************************************
	PURPOSE:	Running a stepper motor with the Arduino
	Created by      Rudy Schlaf after a sketch by Sam Leong
	DATE:		1/2014
        modified 5/2016 by Nathan Richardson
        added homing cycle
*******************************************/
#include <Arduino.h>

#define pin1  8//these are the Arduino pins that we use to activate coils 1-4 of the stepper motor
#define pin2  9
#define pin3  10
#define pin4  11
const byte homeButton = 2;
byte hBval;   // new variable

// Stepper
#define delaytime 3
int steptemp;
int numberOfSteps = 400;
const long FloodInterval = 25000;
long lastFloodTime = 0;
static bool Flood;
const long FloodTime = 5000;
long OpenTime = 0;

void setup() {
  // initialize the 8 pin as an output:
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(homeButton, INPUT_PULLUP);
  Serial.begin(9600);

  Serial.println("Homing......");
  stepperHome();
  Serial.println("Homed to Open (Drain) position");
  Serial.println(" ");
}

void loop(){


 if (Flood)
{
      if (millis() >= OpenTime )
  {
    Serial.print(millis());
    Serial.println(" Opening Drain.... ");
    OpenDrain();
     //Serial.print("Drain Opening ");
     Serial.print(millis());
     Serial.println(" Drain Open ");
     Serial.println(" ");
      Flood = false;
    //OpenTime = millis();
digitalWrite(13, LOW);

  }
}

 if (millis() - lastFloodTime >= FloodInterval)
  {
   Serial.print(millis());
   Serial.println(" Closing Drain.... ");
   lastFloodTime = millis();
    CloseDrain(numberOfSteps);
   // Serial.print("Drain Closing ");
    Serial.print(millis());
    Serial.println(" Drain Closed ");
    Serial.println(" ");
    Flood = true;

    OpenTime = millis() + FloodTime;
digitalWrite(13, HIGH);
  }

  delay(100);
}

void OpenDrain(){

  step_OFF();         //turning all coils off
  steptemp = numberOfSteps;
  while(steptemp>0){
    forward();        //going forward
    steptemp -- ;//counting down the number of steps
  }
   step_OFF();

}

void CloseDrain(int steptemp){

step_OFF();         //turning all coils off
  // steptemp = numberOfSteps;
    while(steptemp>0){
    backward();       //going backward
    steptemp -- ;//counting down the number of steps
  }
   step_OFF();

}

void stepperHome()
{
  hBval = digitalRead(homeButton);
  int hm = 0;
   while (hBval == HIGH )
   //while ( hm < 200 )
  {
    //backwards slowly till it hits the switch and stops
    forward();
    digitalWrite(13, LOW);
    hBval = digitalRead(homeButton);
    hm ++;
    Serial.println(hm);
    if ( hm > 600){   //Timed exit if switch malfunctions
      break;
    }
  }
  digitalWrite(13, HIGH); //
  Flood = false;
  delay(400);
  CloseDrain(50);
digitalWrite(13, LOW);
  //
}


//these functions set the pin settings for each of the four steps per rotation of the motor (keep in mind that the motor in the kit is geared down,
//i.e. there are many steps necessary per rotation

void Step_A(){
  digitalWrite(pin1, HIGH);//turn on coil 1
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}
void Step_B(){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);//turn on coil 2
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}
void Step_C(){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, HIGH); //turn on coil 3
  digitalWrite(pin4, LOW);
}
void Step_D(){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, HIGH); //turn on coil 4
}
void step_OFF(){
  digitalWrite(pin1, LOW); //power all coils down
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}

//these functions run the above configurations in forward and reverse order
//the direction of a stepper motor depends on the order in which the coils are turned on.
void forward(){//one tooth forward
  Step_A();
  delay(delaytime);
  Step_B();
  delay(delaytime);
  Step_C();
  delay(delaytime);
  Step_D();
  delay(delaytime);
}

void backward(){//one tooth backward
  Step_D();
  delay(delaytime);
  Step_C();
  delay(delaytime);
  Step_B();
  delay(delaytime);
  Step_A();
  delay(delaytime);
}
