const byte relayPin = 8;

void setup()
{
  pinMode(relayPin, OUTPUT);
}

void loop()
{
  digitalWrite(relayPin, HIGH);
  delay(500);
  digitalWrite(relayPin, LOW);
  delay(500);
}
