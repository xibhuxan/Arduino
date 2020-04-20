const byte ledRojo = 2;
int ledTime = 1000;
void setup()
{
	pinMode(ledRojo, OUTPUT);
    
}

void loop()
{
	digitalWrite(ledRojo, 1);
    delay(ledTime);
    digitalWrite(ledRojo, 0);
    delay(ledTime);
}
