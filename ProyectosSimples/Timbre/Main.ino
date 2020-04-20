int notas[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
const byte puls = 5;
const byte zumb = 10;
int tnota = 10;
int n = 0;
int m = 0;

void setup()
{
  for (n = 0; n < 4; n++)
  {
    pinMode(zumb, OUTPUT);
    pinMode(puls, INPUT);
  }
}

void nota()
{
  for (m = 0; m <= tnota; m++)
  {
    digitalWrite(zumb, HIGH);
    delayMicroseconds(notas[n]);
    digitalWrite(zumb, LOW);
    delayMicroseconds(notas[n]);
  }
}
void loop()
{
  if (digitalRead(puls) == HIGH)
  {
    n = random(7);
    nota();
    delay(200);
  }
}
