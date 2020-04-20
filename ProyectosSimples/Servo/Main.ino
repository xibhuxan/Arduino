#include <Servo.h>

Servo servoUno;
int tiempo = 1000;

void setup()
{
    servoUno.attach(2); //Pin al que va el cable de señal del servo
}

void loop()
{
    servoUno.write(0); //Grados
    delay(tiempo);     //Lo que tarda en ir al siguiente
    servoUno.write(180);
    delay(tiempo);
}
