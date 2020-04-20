//Incluir las librerias necesarias
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);//Añadir la pantalla 16x2 con la dirección 0x27, verificar la dirección para su pantalla

void setup()
{
	lcd.init();//Inicializar la pantalla
    lcd.backlight();//Activar la iluminación de la pantalla
    lcd.setCursor(0,0);//Poner el cursor en la coordenada 0,0
    lcd.print("Hola");//Escribir texto
    lcd.setCursor(0,1);
    lcd.print("Adios");
}

void loop()
{
	
}
