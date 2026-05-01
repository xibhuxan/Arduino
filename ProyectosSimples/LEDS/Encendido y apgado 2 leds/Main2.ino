const byte ledVerde = 2;
const byte ledRojo = 3;

void setup()
{
	pinMode(ledVerde, OUTPUT);
    pinMode(ledRojo, OUTPUT);
}

void loop()
{
	digitalWrite(ledRojo, 1);
    digitalWrite(ledVerde, 1);
    delay(1000);
    digitalWrite(ledRojo, 0);
    delay(500);
}
