
//https://www.14core.com/the-ds1302-real-time-clock-on-arduino/
#include <MyRealTimeClock.h>

MyRealTimeClock myRTC(6, 7, 8); // Asignar los pines. CLK, DAT, RST

void setup() {
Serial.begin(9600);


/* Para configurar fecha y hora usar el siguiente formato 
| segundos 00 | minutos 05 | hora 21 | dia semana 5 |  dia mes 01 | mes 05 | año 2020 |
*/

myRTC.setDS1302Time(00, 05, 21, 5 , 01, 05, 2020);
}

void loop() {

// Permite actualizar las variables del tiempo, para acceder luego a cada una 
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