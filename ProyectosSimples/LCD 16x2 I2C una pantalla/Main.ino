#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); //Pantalla con direccion normal
String frase1 = String("una cosa");

void setup()
{
    lcd.init();                //Inicia la pantalla
    lcd.backlight();           //Enciende la retroiluminacion
    lcd.createChar(0, hearth); //introduce un caracter especial que no tiene de serie a traves del otro archivo de la carpeta
    lcd.home();                //borra la pantalla y se queda en la coordenada 0,0

    lcd.setCursor(4, 0); //se situa en la coordenada 4,0 (horizontal, vertical)
    lcd.write(byte(0));  //escribe el caracter especial situado en el byte 0

    delay(500);

    for (int i = 0; i < frase1.length(); i++) //Escribe de uno en uno los caracteres de la frase con un tiempo entre letras de medio segundo
    {
        lcd.print(frase1.charAt(i));
        delay(500);
    }

    lcd.write(byte(0)); //escribe el caracter especial
    delay(500);

    lcd.setCursor(5, 1);
    lcd.write(byte(0));
    delay(500);

    for (int i = 0; i < frase2.length(); i++)
    {
        lcd.print(frase2.charAt(i));
        delay(500);
    }

    lcd.write(byte(0));
}

void loop()
{
}
