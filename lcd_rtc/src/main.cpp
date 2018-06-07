#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS1307RTC.h>



LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

byte verticalLine[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte char2[8] = {
  B00000,
  B00000,
  B00000,
  B11100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte char1[8] = {
  B00000,
  B00000,
  B00000,
  B00111,
  B00100,
  B00100,
  B00100,
  B00100
};

byte char3[8] = {
  B00100,
  B00100,
  B00100,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000
};

byte char4[8] = {
  B00100,
  B00100,
  B00100,
  B11100,
  B00000,
  B00000,
  B00000,
  B00000
};

void createCustomCharacters()
{
  lcd.createChar(0, verticalLine);
  lcd.createChar(1, char1);
  lcd.createChar(2, char2);
  lcd.createChar(3, char3);
  lcd.createChar(4, char4);
}


void printFrame()
{
  lcd.setCursor(1,0);
  lcd.print("------------------");
  lcd.setCursor(1,3);
  lcd.print("------------------");
  lcd.setCursor(0,1);
  lcd.write(byte(0));
  lcd.setCursor(0,2);
  lcd.write(byte(0));
  lcd.setCursor(19,1);
  lcd.write(byte(0));
  lcd.setCursor(19,2);
  lcd.write(byte(0));
  lcd.setCursor(0,0);
  lcd.write(byte(1));
  lcd.setCursor(19,0);
  lcd.write(byte(2));
  lcd.setCursor(0,3);
  lcd.write(byte(3));
  lcd.setCursor(19,3);
  lcd.write(byte(4));
}
void printTime(int character,int line, tmElements_t tm)
{
  String seconds,minutes;
  lcd.setCursor(character,line);
  lcd.print(tm.Hour);
  lcd.print(":");
  if(tm.Minute<10)
  {
    minutes = "0"+String(tm.Minute);
    lcd.print(minutes);
  }else
  {
    lcd.print(tm.Minute);
  }
  lcd.print(":");
  if(tm.Second<10)
  {
    seconds = "0"+String(tm.Second);
    lcd.print(seconds);
  }else
  {
    lcd.print(tm.Second);
  }
}

void printDate(int character,int line, tmElements_t tm)
{
  lcd.setCursor(character,line);
  lcd.print(tm.Month);
  lcd.print("/");
  lcd.print(tm.Day);
  lcd.print("/");
  lcd.print(tmYearToCalendar(tm.Year));
}
void setup()
{
  lcd.begin(20,4);

  createCustomCharacters();

  printFrame();
}

void loop()
{
   tmElements_t tm;

  if (RTC.read(tm)) {
    printDate(5,1,tm);
    printTime(6,2,tm);

  } else {
    if (RTC.chipPresent()) {
      //The DS1307 is stopped. Please run the SetTime
    } else {
      //DS1307 read error! Please check the circuitry
    }
    delay(9000);
  }
  delay(1000);
}
