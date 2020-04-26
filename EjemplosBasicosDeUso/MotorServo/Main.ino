
//Añadir la librería necesaria, ya está incluida en las básicas
#include <Servo.h>

Servo myServo; //Crear el objeto necesario

void setup()
{
    myServo.attach(3); //Decirle qué pin usar (pwm)
}

void loop()
{
    myServo.write(0); //Escribir los grados que se quieren en el motor
    delay(1000);      //Esperar
    myServo.write(60);
    delay(1000);
    myServo.write(90);
    delay(1000);
    myServo.write(120);
    delay(1000);
    myServo.write(180);
    delay(1000);
}
