//el motor va a un lado, y luego al otro

const byte pin8 = 8;
const byte pin9 = 9;
const byte pin10 = 10;
const byte pin11 = 11;
int velocidad = 10;

void setup()
{

  pinMode(pin8, OUTPUT);
  pinMode(pin9, OUTPUT);
  pinMode(pin10, OUTPUT);
  pinMode(pin11, OUTPUT);
}

void loop() //El movimiento a un lado y otro es automático, se puede seguir modificando la velocidad con la variable de arriba.
{

  for (int i = 0; i < 200; i++)
  {
    rotarMotorIzquierda();
  }
  delay(1000);
  for (int i = 0; i < 200; i++)
  {
    rotarMotorDerecha();
  }
}
//con esta forma de dar 2 bits se consigue más fuerza
void rotarMotorIzquierda()
{
  controlMotor(1, 1, 0, 0);
  delay(velocidad);
  controlMotor(0, 1, 1, 0);
  delay(velocidad);
  controlMotor(0, 0, 1, 1);
  delay(velocidad);
  controlMotor(1, 0, 0, 1);
  delay(velocidad);
}

void rotarMotorDerecha()
{
  controlMotor(0, 0, 1, 1);
  delay(velocidad);
  controlMotor(0, 1, 1, 0);
  delay(velocidad);
  controlMotor(1, 1, 0, 0);
  delay(velocidad);
  controlMotor(1, 0, 0, 1);
  delay(velocidad);
}
/*
void rotarMotorIzquierda(){
  controlMotor(1,0,0,0);
  delay(velocidad);
  controlMotor(0,1,0,0);
  delay(velocidad);
  controlMotor(0,0,1,0);
  delay(velocidad);
  controlMotor(0,0,0,1);
  delay(velocidad);
}

void rotarMotorDerecha(){
  controlMotor(0,0,0,1);
  delay(velocidad);
  controlMotor(0,0,1,0);
  delay(velocidad);
  controlMotor(0,1,0,0);
  delay(velocidad);
  controlMotor(1,0,0,0);
  delay(velocidad);
}
*/
void controlMotor(int a, int b, int c, int d)
{
  digitalWrite(pin8, a);
  digitalWrite(pin9, b);
  digitalWrite(pin10, c);
  digitalWrite(pin11, d);
}
