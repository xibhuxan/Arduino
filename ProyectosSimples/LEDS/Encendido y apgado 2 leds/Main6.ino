const byte ledVerde = 2;
const byte ledRojo = 3;
const byte ledAmarillo = 4;

void setup()
{
	pinMode(ledVerde, OUTPUT);
    pinMode(ledRojo, OUTPUT);
    pinMode(ledAmarillo, OUTPUT);
}

void loop()
{
    onLed(true, false, false);
    delay(1000);
    onLed(false, true, false);
    delay(1000);
    onLed(false, false, true);
    delay(1000);

    onLed(false, false, false);
    delay(2000);

    onLed(false, false, true);
    delay(1000);
    onLed(false, true, false);
    delay(1000);
    onLed(true, false, false);
    delay(1000);

    onLed(true, true, true);
    delay(2000);

}

void onLed(bool v, bool a, bool r){
    digitalWrite(ledVerde, v);
    digitalWrite(ledRojo, r);
    digitalWrite(ledAmarillo, a);
}