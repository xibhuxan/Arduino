#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int pinOpto = 2;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    lcd.init();
    lcd.backlight();
    pinMode(pinOpto, INPUT);
}

void loop()
{

    if (digitalRead(pinOpto))
    {
        lcd.setCursor(0, 0);
        lcd.print("si detecta");
    }
    else
    {
        lcd.setCursor(0, 0);
        lcd.print("no detecta");
    }
    delay(500);
}
