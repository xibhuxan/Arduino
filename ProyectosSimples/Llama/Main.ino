#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LibSimbolos.cpp>
/*El otro archivo se tiene que poner en la misma carpeta en donde está este, si no funciona copiar el código de allí justo encima de este comentario. */

const byte sensorPin = 2;

boolean sensorDetecta = false;
boolean bloqueoDetecta = true;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    pinMode(sensorPin, INPUT);

    lcd.init();
    lcd.backlight();
    lcd.createChar(0, fire0);
    lcd.createChar(1, fire1);
    lcd.createChar(2, fire2);
    lcd.createChar(3, fire3);

    //lcd.write(byte(0));
}

void loop()
{
    sensorDetecta = digitalRead(sensorPin);

    if (sensorDetecta && !bloqueoDetecta)
    {
        escribirFuego();
        bloqueoDetecta = true;
    }
    if (!sensorDetecta && bloqueoDetecta)
    {
        escribirNoFuego();
        bloqueoDetecta = false;
    }
}

void escribirFuego()
{
    limpiarPantalla();
    //parte izquierda
    lcd.setCursor(0, 0);
    lcd.write(byte(0));
    lcd.write(byte(1));
    lcd.setCursor(0, 1);
    lcd.write(byte(2));
    lcd.write(byte(3));
    //parte derecha
    lcd.setCursor(14, 0);
    lcd.write(byte(0));
    lcd.write(byte(1));
    lcd.setCursor(14, 1);
    lcd.write(byte(2));
    lcd.write(byte(3));

    lcd.setCursor(6, 0);
    lcd.print("HAY");
    lcd.setCursor(5, 1);
    lcd.print("FUEGO");
}

void escribirNoFuego()
{
    limpiarPantalla();
    lcd.setCursor(4, 0);
    lcd.print("NO HAY");
    lcd.setCursor(5, 1);
    lcd.print("FUEGO");
}

void limpiarPantalla()
{
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
}
