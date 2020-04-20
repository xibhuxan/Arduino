#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TAMX 16
#define TAMY 2

LiquidCrystal_I2C lcd(0x27, 16, 2);


bool pos[TAMX][TAMY];


void setup()
{
	lcd.init();
    lcd.backlight();
    lcd.createChar(0, sym_square);
    lcd.home();

    for(int i = 0; i < TAMX; i++){
        borrarChar(i);
        lcd.setCursor(i,0);
        lcd.write(byte(0));
        
        delay(300);
    }

}

void loop()
{
	
}

void borrarChar(int i){
    lcd.setCursor(i-1,0);
    lcd.print(" ");
}
