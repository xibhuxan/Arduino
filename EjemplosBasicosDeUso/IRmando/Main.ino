
//Utilizando el ejemplo de la librería del respectivo creador
//da el siguiente código para recibir las señales del mando, y visualizar qué identificador tiene el botón
//Usaré su código íntegramente, cambiando los baudios del Serial, traduciré como me interese
#include "IRLremote.h"

// Elegir un pin válido para PinInterrupt o PinChangeInterrupt* compatible con tu arduino
#define pinIR 2

// Elige el protocolo de tu mando
CNec IRLremote;
//CPanasonic IRLremote;
//CHashIR IRLremote;
//#define IRLremote Sony12

#define pinLed LED_BUILTIN

void setup()
{
    while (!Serial)
        ;
    Serial.begin(9600);
    Serial.println(F("Startup"));

    pinMode(pinLed, OUTPUT);

    // Empieza a leer el mando, los pines de interrupción se elegirán automáticamente
    if (!IRLremote.begin(pinIR))
        Serial.println(F("You did not choose a valid pin."));
}

void loop()
{

    // Comprueba si hay información disponible
    if (IRLremote.available())
    {
        digitalWrite(pinLed, HIGH);

        // Guarda la información
        auto data = IRLremote.read();

        // Envía los datos recibidos
        Serial.print(F("Address: 0x"));
        Serial.println(data.address, HEX);
        Serial.print(F("Command: 0x"));
        Serial.println(data.command, HEX);
        Serial.println();

        digitalWrite(pinLed, LOW);
    }
}
