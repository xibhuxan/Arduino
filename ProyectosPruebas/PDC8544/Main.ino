
#include <PCD8544.h>

PCD8544 lcd;

void setup()
{
	lcd.begin(84,48);
    lcd.setCursor(0, 0);
  lcd.print("HOLA QUE PASA");
  lcd.setCursor(0, 1);
  lcd.print("nada");
}

void loop()
{
	
}
