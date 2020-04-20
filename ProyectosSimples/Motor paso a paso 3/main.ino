//control del motor paso a paso con un boton, y con un stick

const byte pin8 = 8;
const byte pin9 = 9;
const byte pin10 = 10;
const byte pin11 = 11;

int direction = 0;
int speed = 0;
int speedUsable = 0;

const byte stickSpeed = A0;
const byte stickDirection = A1;

int boton = 5;
byte estadoBoton = 0;

void setup()
{

  pinMode(pin8, OUTPUT);
  pinMode(pin9, OUTPUT);
  pinMode(pin10, OUTPUT);
  pinMode(pin11, OUTPUT);

  Serial.begin(9600);
}

void loop()
{

  estadoBoton = digitalRead(boton);
  if (estadoBoton == 1)
  {
    rotarMotorIzquierda();
  }

  direction = analogRead(stickDirection);
  speed = analogRead(stickSpeed);
  speedUsable = map(speed, 1023, 0, 3, 100);

  if (direction < 450)
  {
    rotarMotorIzquierda();
  }

  if (direction > 550)
  {
    rotarMotorDerecha();
  }
}

//con esta forma de dar 2 bits se consigue más fuerza
void rotarMotorIzquierda()
{
  controlMotor(1, 1, 0, 0);
  delay(speedUsable);
  controlMotor(0, 1, 1, 0);
  delay(speedUsable);
  controlMotor(0, 0, 1, 1);
  delay(speedUsable);
  controlMotor(1, 0, 0, 1);
  delay(speedUsable);
}

void rotarMotorDerecha()
{
  controlMotor(0, 0, 1, 1);
  delay(speedUsable);
  controlMotor(0, 1, 1, 0);
  delay(speedUsable);
  controlMotor(1, 1, 0, 0);
  delay(speedUsable);
  controlMotor(1, 0, 0, 1);
  delay(speedUsable);
}
/*
void rotarMotorIzquierda(){
  controlMotor(1,0,0,0);
  delay(speedUsable);
  controlMotor(0,1,0,0);
  delay(speedUsable);
  controlMotor(0,0,1,0);
  delay(speedUsable);
  controlMotor(0,0,0,1);
  delay(speedUsable);
}

void rotarMotorDerecha(){
  controlMotor(0,0,0,1);
  delay(speedUsable);
  controlMotor(0,0,1,0);
  delay(speedUsable);
  controlMotor(0,1,0,0);
  delay(speedUsable);
  controlMotor(1,0,0,0);
  delay(speedUsable);
}
*/
void controlMotor(int a, int b, int c, int d)
{
  digitalWrite(pin8, a);
  digitalWrite(pin9, b);
  digitalWrite(pin10, c);
  digitalWrite(pin11, d);
}
