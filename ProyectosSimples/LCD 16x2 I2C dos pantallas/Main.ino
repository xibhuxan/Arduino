#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*Este código tiene un archivo adjunto que hay que tener en la misma carpeta 
o bien copiar su contenido debajo del todo en este código.
Este código está hecho para funcionar con dos pantallas, si solo se tiene una, se puede borrar todo lo relacionado con la variable"lcd2" */

LiquidCrystal_I2C lcd1(0x27, 16, 2); //pantalla con direccion normal, la que hay que utilizar de forma comun
LiquidCrystal_I2C lcd2(0x26, 16, 2); //pantalla con direccion modificada
String frase1 = String("una cosa");
String frase2 = String("dos cosa");

void setup()
{
    lcd1.init();                //Inicializar pantalla
    lcd1.backlight();           //Encender luz
    lcd1.createChar(0, hearth); //Añadir el caracter personalizado que viene del otro archivo
    lcd1.home();

    lcd1.setCursor(4, 0);
    lcd1.write(byte(0)); //Escribir el char personalizado que está ubicado en la memoria en la posición 0

    delay(500);

    for (int i = 0; i < frase1.length(); i++) //Escribir letra a letra de forma lenta
    {
        lcd1.print(frase1.charAt(i));
        delay(500);
    }

    lcd1.write(byte(0));

    delay(500);

    lcd1.setCursor(5, 1);
    lcd1.write(byte(0));

    delay(500);

    for (int i = 0; i < frase2.length(); i++)
    {
        lcd1.print(frase2.charAt(i));
        delay(500);
    }

    lcd1.write(byte(0));

    lcd2.init();
    lcd2.backlight();
    lcd2.print("Hola");
}

void loop()
{
}
