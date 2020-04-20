#include <avr/wdt.h>
const byte led = 2;

const byte button = 8;

int buttonState = 0;

bool block = false;
int contador = 0;

void setup()
{
	pinMode(led, OUTPUT);
    pinMode(button, INPUT);
    Serial.begin(9600);
}

void loop()
{
	
    buttonState = digitalRead(button);

    if(buttonState == HIGH && !block){
        Serial.println(++contador);
        if(contador%4 == 0)
            digitalWrite(led,1);
        if(contador == 10) //cuando llega a 10 se reinicia el arduino
            reboot();
        block = true;
    }
    if(buttonState == LOW){
        block = false;
        digitalWrite(led,0);
    }

}

//Funcion de reinicio
void reboot() {
  wdt_disable();
  wdt_enable(WDTO_500MS);
  while (1) {}
}
