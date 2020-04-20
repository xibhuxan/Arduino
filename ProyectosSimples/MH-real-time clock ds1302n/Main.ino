/*
 Se debe añadir a mano la libreria en la carpeta de documentos/arduino/libraries , pegando la carpeta ds1302, o descomprimiendo el zip y pegando su contenido ahi.
 Pagina web:
 http://roboticadiy.com/how-to-make-12-hour-format-clock-ds1302-with-arduino/
 

 Si se quiere cambiar la fecha, es dentro del setup las tres líneas de rtc.setDOW, setTime y setDate. Cuidado que usa valores octales, se utiliza un 0 a la izquierda
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x3F for a 16 chars and 2 line display // note: it may be different for your LCD please find it.
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <DS1302.h>

// Init the DS1302
DS1302 rtc(2, 3, 4);

// Init a Time-data structure
Time t;

void setup()
{

    // Set the clock to run-mode, and disable the write protection
    rtc.halt(false);
    rtc.writeProtect(false);

    // The following lines can be commented out to use the values already stored in the DS1302
    rtc.setDOW(FRIDAY);        // Set Day-of-Week to TUESDAY
    rtc.setTime(8, 35, 00);    // Set the time to 24hr format it will automatically take time according to AM/PM
    rtc.setDate(010, 3, 2019); // Set the date to Febrauray 6th, 2018
    // initialize the LCD
    lcd.init();
    lcd.backlight();
}

void loop()
{
    // Get data from the DS1302
    t = rtc.getTime();

    lcd.setCursor(0, 0);
    if (t.date <= 9)
    {
        lcd.setCursor(0, 0);
        lcd.print("0");
        lcd.setCursor(1, 0);
        lcd.print(t.date, DEC);
    }
    else
    {
        lcd.print(t.date, DEC);
    }

    lcd.setCursor(3, 0);
    lcd.print(rtc.getMonthStr());
    lcd.setCursor(12, 0);
    lcd.print(t.year, DEC);
    lcd.setCursor(4, 1);

    {
        if (t.hour >= 12)
        {
            lcd.setCursor(13, 1);
            lcd.print("PM");
            lcd.setCursor(4, 1);
            t.hour = t.hour - 12;
            if (t.hour == 0)
            {
                t.hour = 12; // Day 12 PM
            }
            if (t.hour <= 9)
            {
                lcd.setCursor(4, 1);
                lcd.print("0");
                lcd.setCursor(5, 1);
                lcd.print(t.hour, DEC);
            }
            else
            {
                lcd.print(t.hour, DEC);
            }
        }
        else
        {
            if (t.hour == 0)
            {
                t.hour = 12; // Night 12 AM
            }
            lcd.setCursor(13, 1);
            lcd.print("AM");
            lcd.setCursor(4, 1);
            if (t.hour <= 9)
            {
                lcd.setCursor(4, 1);
                lcd.print("0");
                lcd.setCursor(5, 1);
                lcd.print(t.hour, DEC);
            }
            else
            {
                lcd.print(t.hour, DEC);
            }
        }
    }

    lcd.setCursor(6, 1);
    lcd.print(":");
    lcd.setCursor(7, 1);

    if (t.min <= 9)
    {
        lcd.setCursor(7, 1);
        lcd.print("0");
        lcd.setCursor(8, 1);
        lcd.print(t.min, DEC);
    }
    else
    {
        lcd.print(t.min, DEC);
    }

    lcd.setCursor(9, 1);
    lcd.print(":");
    lcd.setCursor(10, 1);
    if (t.sec <= 9)
    {
        lcd.setCursor(10, 1);
        lcd.print("0");
        lcd.setCursor(11, 1);
        lcd.print(t.sec, DEC);
    }
    else
    {
        lcd.print(t.sec, DEC);
    }

    delay(1000);
    lcd.clear();
}
