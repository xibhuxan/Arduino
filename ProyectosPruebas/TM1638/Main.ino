
#include <XibTM1638.h>

const byte STROBE = 11;
const byte DATA = 12;
const byte CLOCK = 13;

XibTM1638 placa(STROBE, DATA, CLOCK);

void setup()
{
}

void loop()
{
    char frase[] = "hola que tal";
    placa.writeDisplayShift(frase, sizeof(frase), 700);
}
