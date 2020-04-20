#include "IRLremote.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Código sacado de tercera persona.

const int interruptIR = 0; // Arduino interrupcion 0: Pin 2

uint8_t IRProtocol = 0; // Variables para recibir los datos
uint16_t IRAddress = 0;
uint32_t IRCommand = 0;
bool detecta = false;

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup()
{
   lcd.init();
   lcd.backlight();
   Serial.begin(115200); // Fijate en la velocidad
   Serial.println("Startup");
   IRLbegin<IR_ALL>(interruptIR);
}
void loop()
{
   uint8_t oldSREG = SREG; // Parar las interrupciones
   cli();
   if (IRProtocol) // Si reconoce el protocolo
   {
      Serial.print("Protocol:");
      Serial.println(IRProtocol);
      Serial.print("Address:");
      Serial.println(IRAddress, HEX);
      Serial.print("Command:");
      Serial.println(IRCommand, HEX);
      IRProtocol = 0;
      detecta = true;
   }
   SREG = oldSREG;

   if(detecta){
      lcd.setCursor(0,0);
      lcd.print("               ");
      lcd.setCursor(0,0);
      lcd.print(IRCommand, HEX);
      detecta = false;
   }
   


}

void IREvent(uint8_t protocol, uint16_t address, uint32_t command)
{
   IRProtocol = protocol; // Recogemos los valores y nos volvemos
   IRAddress = address;
   IRCommand = command;
}