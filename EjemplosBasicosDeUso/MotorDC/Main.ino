
//Para más información https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/

//Variables motor A
const byte enA = 10; //Pin para control de velocidad, tiene que ser un pin PWM
const byte in1 = 9; //Pin para control de dirección
const byte in2 = 8; //Pin para control de dirección

//Variables motor B
const byte in3 = 7; //Pin para control de dirección
const byte in4 = 6; //Pin para control de dirección
const byte enB = 5; //Pin para control de velocidad, tiene que ser un pin PWM

void setup()
{
    //Configurar todos los pines como salida
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enB, OUTPUT);
}

void loop()
{
    motorA(255,1);
    motorB(255,1);
}

//Funciones para mejor control de los motores, indicándoles velocidad y sentido
//Velocidad 0-255
//Sentido 0-parado, 1-Frente, 2-Atrás
void motorA(int vel, int sentido){
    velocidadMotor(enA, vel);
    direccionMotor(in1, in2, sentido);
}

void motorB(int vel, int sentido){
    velocidadMotor(enB, vel);
    direccionMotor(in3, in4, sentido);
}




//Control de velocidad del motor
void velocidadMotor(int pinPWM, int vel){
    analogWrite(pinPWM, vel);
}

//Control de dirección del motor
void direccionMotor(int pin1, int pin2, int sentido){
    switch (sentido)
    {
    case 0:
        digitalWrite(pin1, 0);
        digitalWrite(pin2, 0);
        break;
    
    case 1:
        digitalWrite(pin1, 1);
        digitalWrite(pin2, 0);
        break;

    case 2:
        digitalWrite(pin1, 0);
        digitalWrite(pin2, 1);
        break;
    }
}