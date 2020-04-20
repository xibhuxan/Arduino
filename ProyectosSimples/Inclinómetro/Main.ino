#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte sensorInclinacion = 2;

boolean sensorDetecta = false;
boolean bloqueoDetecta = true;

void setup()
{
    lcd.init();
    lcd.backlight();

	pinMode(sensorInclinacion, INPUT);
}

void loop()
{
	sensorDetecta = digitalRead(sensorInclinacion);

    if(sensorDetecta && !bloqueoDetecta){
        escribirInclinado();
        bloqueoDetecta = true;
    }
    if(!sensorDetecta && bloqueoDetecta){
        escribirNoInclinado();
        bloqueoDetecta = false;
    }
}


void escribirInclinado(){
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(3,1);
    lcd.print("INCLINADO");
}

void escribirNoInclinado(){
    lcd.setCursor(6,0);
    lcd.print("NO");
    lcd.setCursor(3,1);
    lcd.print("INCLINADO");
}