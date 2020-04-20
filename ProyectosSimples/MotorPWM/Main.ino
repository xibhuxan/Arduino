const byte motorDirección = 2; //cable a los reles
const byte motorPin = 3;       //cable de alimentacion al motor

const byte buttonDireccion = 4; //boton que cambia la direccion
byte buttonDireccionState = 0;

const byte buttonVelocidad = 5; //boton que cambia la velocidad
byte buttonVelocidadState = 0;

void setup()
{
    pinMode(motorDirección, OUTPUT);
    pinMode(motorPin, OUTPUT);
    pinMode(buttonDireccion, INPUT_PULLUP);
    pinMode(buttonVelocidad, INPUT_PULLUP);
}

void loop()
{
    buttonDireccionState = digitalRead(buttonDireccion);
    buttonVelocidadState = digitalRead(buttonVelocidad);

    if (buttonDireccionState == 0)
    {
        digitalWrite(motorDirección, 0);
    }
    else
    {
        digitalWrite(motorDirección, 1);
    }

    if (buttonVelocidadState == 0)
    {
        analogWrite(motorPin, 250);
    }
    else
    {
        analogWrite(motorPin, 50);
    }
}
