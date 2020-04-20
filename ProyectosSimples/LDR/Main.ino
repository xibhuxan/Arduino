const byte led = 13;
const byte ldr = A0;

int valorLdr = 0;

void setup()
{
	pinMode(led, OUTPUT);
}

void loop()
{
	valorLdr = analogRead(ldr);
    digitalWrite(led, 1);
    delay(valorLdr);
    digitalWrite(led, 0);
    delay(valorLdr);
}
