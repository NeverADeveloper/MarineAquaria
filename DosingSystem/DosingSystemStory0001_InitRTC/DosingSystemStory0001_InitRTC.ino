/*  
*   Dosing System Story 0001 - Initial Real time Clock (RTC) Configuration
 *  by Andrew Westfold. (c) April 2016
 *  
 *  Requirements:
 *      Arduino Nano
 *      i2c RTC
 *  
 *  Connections
 *      i2c     Nano
 *      VCC     5v
 *      GND     GND
 *      SDA     A4
 *      SCL     A5
*/

#include <Wire.h>
#define rtc_I2C_Addr 0x68 //check with i2c_Scanner.ino

byte decToBcd(byte val)// Convert decimal numbers to binary coded decimal
{
     return((val/10*16) + (val%10));
}

byte bcdToDec(byte val)// Convert binary coded decimal to decimal
{
     return((val/16*10) + (val%16));
}

void setup()
{
     Wire.begin();
     Serial.begin(9600);
     //set time here - then comment out before next running the sketch:
     setRTCtime(30,21,11,7,02,01,16); //ss,mm,hh,dow,dd,mm,yy
}

void setRTCtime
(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
{  // sets time and date data to DS3231
     Wire.beginTransmission(rtc_I2C_Addr);
     Wire.write(0); // set next input to start at the seconds register
     Wire.write(decToBcd(second)); // set seconds
     Wire.write(decToBcd(minute)); // set minutes
     Wire.write(decToBcd(hour)); // set hours
     Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
     Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
     Wire.write(decToBcd(month)); // set month
     Wire.write(decToBcd(year)); // set year (0 to 99)
     Wire.endTransmission();
}

void readRTCtime
(byte *second,byte *minute,byte *hour,byte *dayOfWeek,byte *dayOfMonth,byte *month,byte *year)
{
     Wire.beginTransmission(rtc_I2C_Addr);
     Wire.write(0); //set DS3231 register pointer to 00h
     Wire.endTransmission();
     Wire.requestFrom(rtc_I2C_Addr, 7);//request 7 bytes of RTC data starting loc 00h
          *second = bcdToDec(Wire.read() & 0x7f);
          *minute = bcdToDec(Wire.read());
          *hour = bcdToDec(Wire.read() & 0x3f);
          *dayOfWeek = bcdToDec(Wire.read());
          *dayOfMonth = bcdToDec(Wire.read());
          *month = bcdToDec(Wire.read());
          *year = bcdToDec(Wire.read());
}

void displayTimeSerial()
{//for testing only
     byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
     readRTCtime(&second,&minute,&hour,&dayOfWeek,&dayOfMonth,&month,&year);
     // send it to the serial monitor
     switch(dayOfWeek)
     {
          case 1:
               Serial.print("Sun ");
          break;
          case 2:
               Serial.print("Mon ");
          break;
          case 3:
               Serial.print("Tue ");
          break;
          case 4:
               Serial.print("Wed ");
          break;
          case 5:
               Serial.print("Thu ");
          break;
          case 6:
               Serial.print("Fri ");
          break;
          case 7:
               Serial.print("Sat ");
          break;
     } 
     Serial.print(dayOfMonth, DEC);
     Serial.print("/");
     Serial.print(month, DEC);
     Serial.print("/");
     Serial.print(year, DEC);
     Serial.print (" ");  
     Serial.print(hour, DEC);// convert the byte variable to a decimal number when displayed
     Serial.print(":");
     if (minute<10)
     {
          Serial.print("0");
     }
     Serial.print(minute, DEC);
     Serial.print(":");
     if (second<10)
     {
          Serial.print("0");
     }
     Serial.println(second, DEC);
}

void loop()
{
     displayTimeSerial(); // display time via serial monitor
     delay(1000); // every second
}
