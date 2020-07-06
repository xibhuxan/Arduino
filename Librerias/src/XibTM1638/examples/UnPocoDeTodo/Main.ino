
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
    byte botones = placa.readButtons();
    //el byte entero corresponde a los ocho botones, cada bit es un botón.
    //00000001 -> esto significa que se ha pisado el botón S1
    //00100000 -> esto significa que se ha pisado el botón S6
    //01010101 -> esto significa que se han pisado los botones S1, S3, S5, S7 a la vez
    //Se puede utilizar binario para comparar 0B00001000 -> comprobar si se ha pisado el S4
    //Se puede utilizar hexadecimal para comparar 0x11 -> comprobar si se han pisado S1 y S5

    switch (botones)
    {
    case 0x01:
        placa.onRed(0);
        break;
    
    case 0x02:
        placa.offLed(0);
        break;
    }

    if(botones == 0x04){
        placa.onRed(1);
    }else{
        placa.offLed(1);
    }



    placa.writeDisplayShift("hola que tal", 1000);
}
