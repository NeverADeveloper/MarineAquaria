/*
    0002 - Initial LCD configuration
    by Andrew Westfold

    Requirements:
    * i2c LCD
*/

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27 //Use I2C Scanner to find display address
#define Rs_pin 0
#define Rw_pin 1
#define En_pin 2
#define Backlight_pin 3
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);


void setup()
{  // set lcd
  lcd.begin (16,2); // Define the LCD matrix (chars, rows)
  lcd.setBacklightPin(Backlight_pin,POSITIVE); // Switch on the backlight
  lcd.setBacklight(HIGH);
  lcd.home ();
}

void loop()
{  
  lcd.setCursor(0,0);
  lcd.print("Line 1");
  lcd.setCursor(0,1);
  lcd.print("Line 2");
}
