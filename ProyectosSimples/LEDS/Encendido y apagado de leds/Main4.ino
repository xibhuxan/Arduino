const byte ledRojo = 6;
int onTime = 1000;
int offTime = 3000;

void setup()
{
	pinMode(ledRojo, OUTPUT);
    
}

void loop()
{
	digitalWrite(ledRojo, 1);
    delay(onTime);
    digitalWrite(ledRojo, 0);
    delay(offTime);
}
