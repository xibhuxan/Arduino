

byte ledPin = 2;

void setup()
{
    pinMode(ledPin, OUTPUT);
}

void loop()
{
    intermitencia(300);
    intermitencia(200);
    intermitencia(100);
    intermitencia(50);
    intermitencia(25);
    intermitencia(10);
    intermitencia(5);
}

void intermitencia(int tiempo)
{
    for (int i = 0; i < 20; i++)
    {
        digitalWrite(ledPin, 1);
        delay(tiempo);
        digitalWrite(ledPin, 0);
        delay(tiempo);
    }
}