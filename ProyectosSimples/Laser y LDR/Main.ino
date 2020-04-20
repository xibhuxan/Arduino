const byte ldr = A0;
const byte laser = 5;
int contador = 0;
int valorLdr = 0;

void setup()
{
  pinMode(ldr, INPUT);
  pinMode(laser, OUTPUT);
  digitalWrite(laser, HIGH);
  Serial.begin(9600);
}

void loop()
{
  valorLdr = analogRead(ldr);

  if (valorLdr > 100)
  {
    contador++;
    Serial.println(contador);
    delay(300);
  }
}
