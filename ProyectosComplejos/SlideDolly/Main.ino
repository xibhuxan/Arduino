/*
 Dolly lapse
 by XavierGP
https://xaviergp.blogspot.com/2013/11/slide-dolly-electronica-y-arduino.html
 */

// define the pins used
#include <Wire.h>    // Comes with Arduino IDE
#include <Stepper.h> // incluimos la Stepper library
#include <LiquidCrystal_I2C.h>
#define motorStepsX 200 // Pasos motor X 360º/1.8º
int left = 7;
int right = 5;
int enter = 6;
int espacio = 500;     // recorrido dolly
int minutos_secuencia; // Variable pre definida
int minimo_minutos_secuencia;
float segundos_secuencia = minutos_secuencia * 60;
int paso;
float posicion_actual;
int foto = 12;  // salida remoto camara
int shot = 100; //variable pre definida
float tiempo_reloj;
int a = 0; // bucles
float porcentaje;

Stepper myStepperX(motorStepsX, 8, 9, 10, 11); // libreria motor X   3,13,12,11
LiquidCrystal_I2C lcd(0x27, 16, 2);            // Set the LCD I2C address
void setup()
{
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  pinMode(enter, INPUT);
  pinMode(foto, OUTPUT);

  lcd.init();
  myStepperX.setSpeed(12); // definimos velocidad impulsos motor
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello, XavierGP!");
  delay(1000);
  lcd.clear();
  logo0();
  logo1();
  lcd.setCursor(2, 0);
  lcd.print("Slide");
  delay(700);
  logo2();
  lcd.setCursor(0, 1);
  lcd.print("dolly v2.0");
  delay(700);
  logo1();
  delay(2000);
  lcd.clear();

  define_espacio();
  define_fotos();
  minutos_secuencia = (espacio / 125) + 1 + (0.02 * shot); // original minutos_secuencia=(espacio/410)+1+(0.02*shot)
  minimo_minutos_secuencia = minutos_secuencia;
  segundos_secuencia = minutos_secuencia * 60;

  define_tiempo();

  lcd.clear();
  segundos_secuencia = (minutos_secuencia * 60) / (shot + 1);
  paso = (12800 / 2000) * (espacio) / (shot); //originalment /2100

  segundos_secuencia = (segundos_secuencia - 1 - (paso * 0.075)); //original *0.024

  lcd.print("[ENTER] = Start");
  lcd.setCursor(0, 1);
  for (int k = 0; k < 16; k++)
  {
    lcd.print(".");
    delay(100);
  }

  a = 0; // provoquem pausa
  while (a == 0)
  {
    if (digitalRead(enter) == HIGH)
    {
      a = 1;
    }
  }
  lcd.clear();
  for (int i = 1; i < shot; i++)
  {

    logo0();
    logo1();
    lcd.setCursor(1, 0);
    if (i <= 99)
    {
      lcd.print(" ");
    }
    if (i <= 9)
    {
      lcd.print(" ");
    }

    lcd.print(i);
    lcd.print("s");
    lcd.setCursor(7, 0);
    lcd.print(i * 100 / shot);
    lcd.print("%");

    lcd.setCursor(0, 1);
    lcd.print("FOTO!");
    digitalWrite(foto, HIGH);
    logo2();
    delay(300);
    digitalWrite(foto, LOW);
    delay(300);
    logo1();
    lcd.setCursor(0, 1);
    lcd.print("MOVE!");
    myStepperX.step(paso);
    lcd.setCursor(0, 1);
    lcd.print("     ");
    posicion_actual = (posicion_actual + (paso * 0.165));

    for (int j = 0; j < (segundos_secuencia * 10); j++)
    {

      delay(100);
      lcd.setCursor(0, 1);
      tiempo_reloj = j * 0.1;
      if ((segundos_secuencia - tiempo_reloj) < 10)
      {
        lcd.print(" ");
      }
      lcd.print(segundos_secuencia - tiempo_reloj);
      lcd.setCursor(4, 1);
      lcd.print(char(34));
      lcd.print(" ");
      lcd.setCursor(6, 1);
      if (posicion_actual < 1000)
      {
        lcd.print(" ");
      }
      if (posicion_actual < 100)
      {
        lcd.print(" ");
      }
      lcd.print(posicion_actual, 0);
      lcd.setCursor(10, 1);
      lcd.print("mm");
    }
  }
  logo0();
  logo1();
  lcd.setCursor(0, 1);
  lcd.print("     ");
  digitalWrite(foto, HIGH);
  logo2();
  delay(500);
  digitalWrite(foto, LOW);
  delay(100);
  logo1();
  lcd.setCursor(0, 0);
  lcd.print("MotionLapse");
  lcd.setCursor(0, 1);
  lcd.print(" completo!  ");
}

void loop()
{ // ********************* loop ***********
}

void define_espacio()
{
  a = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Define  espacio");
  lcd.setCursor(3, 1);
  if (espacio < 1000)
  {
    lcd.print(" ");
  }
  lcd.print(espacio);
  lcd.setCursor(9, 1);
  lcd.print("mm.");
  delay(200);
  while (a == 0)
  {
    if (digitalRead(enter) == HIGH)
    {
      a = 1;
    }
    delay(150);
    if (digitalRead(right) == HIGH)
    {
      if (espacio < 2000)
      {
        espacio = espacio + 100;
        lcd.setCursor(3, 1);
        if (espacio < 1000)
        {
          lcd.print(" ");
        }
        lcd.print(espacio);
        lcd.setCursor(7, 1);
        lcd.print("  mm.  ");
      }
    }

    if (digitalRead(left) == HIGH)
    {
      if (espacio > 100)
      {
        espacio = espacio - 100;
        lcd.setCursor(3, 1);
        if (espacio < 1000)
        {
          lcd.print(" ");
        }
        lcd.print(espacio);
        lcd.setCursor(7, 1);
        lcd.print("  mm.  ");
      }
    }
  }
}

void define_tiempo()
{
  a = 0;
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Define  tiempo");
  lcd.setCursor(5, 1);
  lcd.print(minutos_secuencia);
  lcd.setCursor(8, 1);
  lcd.print("min.");
  delay(200);
  while (a == 0)
  {

    if (digitalRead(enter) == HIGH)
    {
      a = 1;
    }
    delay(150);
    if (digitalRead(right) == HIGH)
    {
      if (minutos_secuencia < 250)
      {
        minutos_secuencia = minutos_secuencia + 1;
        lcd.setCursor(4, 1);
        if (minutos_secuencia < 100)
        {
          lcd.print(" ");
        }
        lcd.print(minutos_secuencia);
        lcd.print(" min.  ");
      }
    }

    if (digitalRead(left) == HIGH)
    {
      if (minutos_secuencia > minimo_minutos_secuencia)
      {
        minutos_secuencia = minutos_secuencia - 1;
        lcd.setCursor(4, 1);
        if (minutos_secuencia < 100)
        {
          lcd.print(" ");
        }
        lcd.print(minutos_secuencia);
        lcd.print(" min.  ");
      }
    }
  }
}

void define_fotos()
{
  a = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Define num fotos");
  lcd.setCursor(4, 1);
  lcd.print(shot);
  lcd.setCursor(8, 1);
  lcd.print("fotos");
  delay(200);
  while (a == 0)
  {

    if (digitalRead(enter) == HIGH)
    {
      a = 1;
    }
    delay(150);
    if (digitalRead(right) == HIGH)
    {
      if (shot < 250)
      {
        shot = shot + 1;
        lcd.setCursor(4, 1);
        if (shot < 100)
        {
          lcd.print(" ");
        }
        lcd.print(shot);
        lcd.setCursor(8, 1);
        lcd.print("fotos");
      }
    }

    if (digitalRead(left) == HIGH)
    {
      if (shot > 10)
      {
        shot = shot - 1;
        lcd.setCursor(4, 1);
        if (shot < 100)
        {
          lcd.print(" ");
        }
        lcd.print(shot);
        lcd.setCursor(8, 1);
        lcd.print("fotos");
      }
    }
  }
}

void logo0()
{
  byte logo1a[8] = {B01111, B00110, B01111, B11111, B11111, B11111, B11110, B11110};
  byte logo1d[8] = {B00000, B00000, B11110, B11111, B11111, B11111, B11111, B11111};
  byte logo1e[8] = {B11110, B11110, B11110, B11111, B11111, B11111, B11111, B01111};
  byte logo1h[8] = {B01111, B01111, B01111, B11111, B11111, B11111, B11111, B11110};
  lcd.createChar(1, logo1a);
  lcd.createChar(4, logo1d);
  lcd.createChar(5, logo1e);
  lcd.createChar(8, logo1h);
}

void logo1()
{
  byte logo1b[8] = {B00000, B00111, B11100, B10001, B00110, B01100, B01000, B10000};
  byte logo1c[8] = {B00000, B11100, B00111, B10001, B01100, B00110, B00010, B00001};
  byte logo1f[8] = {B10000, B10000, B01000, B01100, B00110, B10001, B11100, B11111};
  byte logo1g[8] = {B00001, B00001, B00011, B00110, B01100, B10001, B00111, B11111};
  byte logo1d[8] = {B00000, B00000, B11110, B11111, B11111, B11111, B11111, B11111};
  lcd.createChar(2, logo1b);
  lcd.createChar(3, logo1c);
  lcd.createChar(6, logo1f);
  lcd.createChar(7, logo1g);
  lcd.createChar(4, logo1d);
  lcd.setCursor(12, 0);
  lcd.write(1);
  lcd.setCursor(13, 0);
  lcd.write(2);
  lcd.setCursor(14, 0);
  lcd.write(3);
  lcd.setCursor(15, 0);
  lcd.write(4);
  lcd.setCursor(12, 1);
  lcd.write(5);
  lcd.setCursor(13, 1);
  lcd.write(6);
  lcd.setCursor(14, 1);
  lcd.write(7);
  lcd.setCursor(15, 1);
  lcd.write(8);
}

void logo2()
{
  byte logo1b[8] = {B00000, B00111, B11100, B10001, B00111, B01111, B01111, B11111};
  byte logo1c[8] = {B00000, B11100, B00111, B10001, B11100, B11110, B11110, B11111};
  byte logo1f[8] = {B11110, B11111, B01111, B01111, B00111, B10001, B11100, B11111};
  byte logo1g[8] = {B01111, B11111, B11111, B11110, B11100, B10001, B00111, B11111};
  byte logo1d[8] = {B00000, B00000, B11110, B11111, B11111, B11111, B11111, B11111};
  lcd.createChar(2, logo1b);
  lcd.createChar(3, logo1c);
  lcd.createChar(6, logo1f);
  lcd.createChar(7, logo1g);
  lcd.createChar(4, logo1d);
  lcd.setCursor(12, 0);
  lcd.write(1);
  lcd.setCursor(13, 0);
  lcd.write(2);
  lcd.setCursor(14, 0);
  lcd.write(3);
  lcd.setCursor(15, 0);
  lcd.write(4);
  lcd.setCursor(12, 1);
  lcd.write(5);
  lcd.setCursor(13, 1);
  lcd.write(6);
  lcd.setCursor(14, 1);
  lcd.write(7);
  lcd.setCursor(15, 1);
  lcd.write(8);
}
