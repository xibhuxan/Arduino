#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x26, 16, 2);

long timeAntMensaje1 = 0;
long timeAntMensaje2 = 0;

char nombre[] = "nombre";
int nombreLenght = 5;
char fr1[] = "Frase Uno";
const int fr1l = 9;
char fr2[] = "Frase Dos";
const int fr2l = 9;
char fr3[] = "Frase Tres";
const int fr3l = 10;

bool sentido = false;

int posNombre = 0;

int estado = 0;

void setup()
{
    
	lcd.init();
    lcd.backlight();
}

void loop()
{
	if(millis() - timeAntMensaje1 > 300){
        
        timeAntMensaje1 = millis();
        
        if(!sentido){
            limpiar1();

            lcd.setCursor(posNombre,0);
            lcd.print(nombre);

            posNombre += 1;
            if(posNombre == 16-nombreLenght){
                sentido = true;
            }
        }else{
            limpiar1();

            lcd.setCursor(posNombre,0);
            lcd.print(nombre);

            posNombre -= 1;
            if(posNombre == 0){
                sentido = false;
            }
        }
    }


    if(millis() - timeAntMensaje2 > 2000){
        timeAntMensaje2 = millis();
        estado += 1;
        estado = estado % 3;
        limpiar2();
    }

    switch (estado)
    {
    case 0:
        lcd.setCursor(medio(fr1l),1);
        lcd.print(fr1);
        break;

    case 1:
        lcd.setCursor(medio(fr2l),1);
        lcd.print(fr2);
        break;

    case 2:
        lcd.setCursor(medio(fr3l),1);
        lcd.print(fr3);
        break;
    
    }




}

void limpiar1(){
    lcd.setCursor(0,0);
    lcd.print("                ");
}
void limpiar2(){
    lcd.setCursor(0,1);
    lcd.print("                ");
}

int medio(int longitud){
    return (16 - longitud)/2; 
}