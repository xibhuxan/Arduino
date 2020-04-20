
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

const byte ledR = 9;
const byte ledG = 10;
const byte ledB = 11;

int tiempoCambioLeds = 10;

void setup()
{
    pinMode(ledR, OUTPUT);
    pinMode(ledG, OUTPUT);
    pinMode(ledB, OUTPUT);

    lcd.init();
    lcd.backlight();
    escribirLCD(0, 0, 0);
}

/*Este código tiene dos modos de funcionamiento, el modo manual de modo predefinido, 
es la función variarLedsManual() en el que se le modifican los valores que se quiere que tenga el led rgb, 
hay que subirlo cada vez que se modifica.
Si se quiere utilizar la otra forma automática, se debe comentar la función de manual poniéndole dos barras delante,
y se quitan las dos barras de la función variarLedsAuto(), en este caso no hay que hacer ninguna modificación más. */

void loop()
{
    variarLedsManual(50, 175, 236);//Cambiar los valores y subir al arduino
    //variarLedsAuto();
}

void encenderLed(byte led, byte iluminado)
{
    analogWrite(led, iluminado);
}

void escribirLCD(byte valorLedR, byte valorLedG, byte valorLedB)
{
    lcd.setCursor(0, 0);
    lcd.print(" R: ");
    lcd.print(valorLedR);

    lcd.setCursor(9, 0);
    lcd.print("G: ");
    lcd.print(valorLedG);

    lcd.setCursor(5, 1);
    lcd.print("B: ");
    lcd.print(valorLedB);
}

void escribirLCD(byte led, byte valorLed)
{

    switch (led)
    {
    case ledR:
        lcd.setCursor(0, 0);
        lcd.print(" R: ");
        lcd.print(valorLed);
        lcd.print(" ");
        break;
    case ledG:
        lcd.setCursor(9, 0);
        lcd.print("G: ");
        lcd.print(valorLed);
        lcd.print(" ");
        break;
    case ledB:
        lcd.setCursor(5, 1);
        lcd.print("B: ");
        lcd.print(valorLed);
        lcd.print(" ");
        break;
    }
}

void variarLedsManual(byte valorLedR, byte valorLedG, byte valorLedB)
{
    encenderLed(ledR, valorLedR);
    encenderLed(ledG, valorLedG);
    encenderLed(ledB, valorLedB);
    escribirLCD(valorLedR, valorLedG, valorLedB);
}

void variarLedsAuto()
{
    movAutoSubida(ledR);
    movAutoSubida(ledG);
    movAutoSubida(ledB);
    movAutoBajada(ledR);
    movAutoBajada(ledG);
    movAutoBajada(ledB);
}

void movAutoSubida(byte led)
{
    for (int i = 0; i <= 255; i++)
    {
        encenderLed(led, i);
        escribirLCD(led, i);
        delay(tiempoCambioLeds);
    }
}

void movAutoBajada(byte led)
{
    for (int i = 255; i >= 0; i--)
    {
        encenderLed(led, i);
        escribirLCD(led, i);
        delay(tiempoCambioLeds);
    }
}