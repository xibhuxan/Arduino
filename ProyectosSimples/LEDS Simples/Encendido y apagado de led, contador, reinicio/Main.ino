const byte led = 2; //Pin para led

const byte button = 8; //Pin para boton

int buttonState = 0; //Variable que almacena estado del boton

bool block = false; //Para bloquear el contaje cuando se está pisando
int contador = 0;

void setup()
{
    pinMode(led, OUTPUT);
    pinMode(button, INPUT);
    Serial.begin(9600);
}

void loop()
{

    buttonState = digitalRead(button); //Lee la entrada y guarda el estado en la variable

    if (buttonState == HIGH && !block) //Si buttonState está en 1, y block está en 0
    {
        digitalWrite(led, 1);
        Serial.println(contador++);
        block = true; //Pone el bloqueo a 1
    }
    if (buttonState == LOW) //Si el botón está en 0
    {
        block = false; //Pone el bloqueo a 0
        digitalWrite(led, 0);
    }
}
