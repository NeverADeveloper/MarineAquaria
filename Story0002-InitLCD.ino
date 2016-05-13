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
int chars = 20; //Define the number of characters per row of the chosen display
int rows = 4; //Define the number of rows of the chosen display 

void setup()
{  // set lcd
  lcd.begin (chars, rows); // Define the LCD matrix (chars, rows)
  lcd.setBacklightPin(Backlight_pin,POSITIVE); // Switch on the backlight
  lcd.setBacklight(HIGH);
  lcd.home ();
}

void loop()
{ //test code to ensure all lines display text 
  lcd.setCursor(0,0);
  lcd.print("Row 1");
  lcd.setCursor(0,1);
  lcd.print("Row 2");
  if rows == 4 //For 4-row displays
  {
     lcd.setCursor(0,2);
     lcd.print("Row 3");
     lcd.setCursor(0,3);
     lcd.print("Row 4"); 
  }
}
