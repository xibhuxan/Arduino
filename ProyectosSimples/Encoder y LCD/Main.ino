
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define outputA 2 //DT - 6 del esquema
#define outputB 3 //CLK - 7 del esquema
#define boton 4 //SW - 8 del esquema

LiquidCrystal_I2C lcd(0x27, 16, 2);

int counter = 0;
byte aState;
byte aLastState;

void setup()
{
    lcd.init();
    lcd.backlight();

	pinMode (outputA,INPUT);
    pinMode (outputB,INPUT);
    pinMode (boton, INPUT_PULLUP);
    aLastState = digitalRead(outputA);   //Leemos el valor incial
}

void loop()
{
	aState = digitalRead(outputA);
    if (aState != aLastState){
      if (digitalRead(outputB) != aState)
          counter ++;
      else
          counter --;

    escribir(counter);

   }

aLastState = aState; // Guardamos el ultimo valor


bool B = digitalRead(boton);
    if ( !B ){ 
        counter = 0 ;
        delay(200);
        escribir(counter);
    }

}
     

//Funciones    
void escribir(int num){
    lcd.setCursor(0,0);
    lcd.print("    ");
    lcd.setCursor(0,0);
    lcd.print(num);
}