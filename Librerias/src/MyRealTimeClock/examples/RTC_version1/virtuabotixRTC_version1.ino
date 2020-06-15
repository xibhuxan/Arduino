
#include <MyRealTimeClock.h>

MyRealTimeClock myRTC(6, 7, 8); // Assign Digital Pins 

void setup() {
Serial.begin(9600);


/* To set the current time and date in specific format 
| Second 00 | Minute 59 | Hour 10 | Day 12 |  Month 07 | Year 2015 |
*/

myRTC.setDS1302Time(00, 59, 10, 12 , 10, 07, 2015);
}

void loop() {

// Allow the update of variables for time / accessing the individual element. 
myRTC.updateTime();

Serial.print("Current Date / Time: "); 
Serial.print(myRTC.dayofmonth); // Element 1
Serial.print("/"); 
Serial.print(myRTC.month); // Element 2
Serial.print("/");
Serial.print(myRTC.year); // Element 3
Serial.print(" ");
Serial.print(myRTC.hours); // Element 4
Serial.print(":");
Serial.print(myRTC.minutes); // Element 5
Serial.print(":");
Serial.println(myRTC.seconds); // Element 6
delay( 5000);
}

Download The Code Library Here | 

Download The Data Sheet  Here |

Useful Link from the Official Site | http://playground.arduino.cc/Main/DS1302


