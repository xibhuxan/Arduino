
/*
 V0.6
 Created By Xibhu
 Este código está pensado para controlar un brazo robótico de cuatro servomotores con arduino.
 Es necesario realizar ajustes si se va a utilizar un número distinto de servos.
 */

#include <Key.h>               //Viene con la librería de Keypad
#include <Keypad.h>            //Descargada de la librería de arduino
#include <Servo.h>             //Viene de serie con arduino
#include <Wire.h>              //Viene de serie con arduino
#include <LiquidCrystal_I2C.h> //Descargada de la librería de arduino

LiquidCrystal_I2C lcd(0x27, 16, 2); //Cambiar 0x27 por la dirección de su pantalla

//Teclado - Variables para utilizar una matriz de botones, en este caso de 4x2
//
//
const byte ROWS = 2; //Cantidad de filas de la botonera
const byte COLS = 4; //Cantidad de columnas de la botonera

//Colocar los dígitos o símbolos que corresponden a cada tecla de la botonera
char teclas[ROWS][COLS] = {
    {'1', '2', '3', '4'},
    {'5', '6', '7', '8'}};

byte rowPins[ROWS] = {6, 7};       //Pines que utilizan las filas
byte colPins[COLS] = {2, 3, 4, 5}; //Pines que utilizan las columnas

//Creación del objeto que utiliza el teclado
Keypad teclado = Keypad(makeKeymap(teclas), rowPins, colPins, ROWS, COLS);

unsigned char teclaPisada = ' '; //Para guardar el valor leído del botón
bool teclaFuePisada = false;     //Bloqueo al pisar un botón
unsigned long teclaTiempo = 0;   //Para saber la diferencia de tiempo y actuar de una manera u otra

//Servos - En este caso se utilizan 4 servomotores, ajustar para otra cantidad
//
//
#define numServos 4 //Cambiar por el número de servos, a parte hacer ajustes en el código para una cantidad distinta de 4

Servo servos[numServos];
int ejes[numServos] = {A0, A1, A2, A3}; //Poner los pines correspondientes a los sticks o potenciometros utilizados
int valEjes[numServos];
int valMaps[numServos];
int gradosAnterior[numServos];
int grados[numServos] = {90, 90, 90, 90}; //Posición actual de los servos, con inicialización en 90 grados
int gradosGuardados[ROWS * COLS][4];      //Memoria temporal en ejecución para guardar los grados con los botones
//Posición en pantalla de los servos
int posServoLCD[numServos][2] = {
    {0, 0}, {9, 0}, {0, 1}, {9, 1}};

unsigned long tiempoSaveLCD;

void setup()
{
  //Inicializar los servos en los pines a partir del 8
  for (int i = 0; i < numServos; i++)
  {
    servos[i].attach(i + 8);
  }

  //Inicializar pantalla con valores XXX (90 grados)
  lcd.init();
  lcd.backlight();

  for (int i = 0; i < numServos; i++)
  {
    lcd.setCursor(posServoLCD[i][0], posServoLCD[i][1]);
    lcd.print("SV");
    lcd.print(i);
    lcd.print(":XXX");
  }

  //Valores iniciales preestablecidos para la botonera. Hasta el botón 6 para que de exacto las sumas de 30. De 0 a 180.
  int valores = 0;
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < numServos; j++)
    {
      gradosGuardados[i][j] = valores;
    }
    valores += 30;
  }
}

void loop()
{

  //Función principal que se repite para todos los servos
  for (int i = 0; i < numServos; i++)
  {
    servos[i].write(movimientoServo(i, ejes[i], valEjes[i], valMaps[i], grados[i], gradosAnterior[i]));
  }

  botonera(); //Comprueba los botones, guarda valores, y aplica valores

  delay(50);
}

//PARTE FUNCIONES

int movimientoServo(int numServo, int eje, int valEje, int valMap, int &grados, int &gradosAnterior)
{
  valEje = analogRead(eje); //Recoge el valor del eje concreto
  gradosAnterior = grados;  //Guarda el grado en el que esta en ese momento

  if (valEje < 480)
  { //Si el potenciometro está en menos de 480, pasa ese valor de -5 a 0
    valMap = map(valEje, 0, 500, -5, 0);
  }
  else if (valEje > 510)
  { //Si el potenciometro está en menos de 480, pasa ese valor de 0 a 5
    valMap = map(valEje, 520, 1023, 0, 5);
  }
  else
  { //Si no se cumple ninguna de las anteriores, se queda en 0
    valMap = 0;
  }

  if (grados + valMap >= 0 && grados + valMap <= 180 && grados + valMap != gradosAnterior)
  {
    grados += valMap;                   //El valor de valMap se le incrementará a grados para hacer un movimiento suave
    escribirServoLCD(numServo, grados); //Escribe el valor en pantalla
  }

  return grados;
}

//Escribir los grados en la pantalla en las posiciones correctas
void escribirServoLCD(int numServo, int grados)
{

  lcd.setCursor(posServoLCD[numServo][0], posServoLCD[numServo][1]);
  lcd.print("SV");
  lcd.print(numServo);
  lcd.print(":   ");
  lcd.setCursor(posServoLCD[numServo][0] + 4, posServoLCD[numServo][1]);
  lcd.print(grados);
}

void botonera()
{
  teclaPisada = teclado.getKey(); //Guarda el botón pisado
  int valorBoton;

  if (teclado.getState() == 1 && !teclaFuePisada)
  {
    teclaFuePisada = true;
    teclaTiempo = millis();
    //Sacar el valor numerico del char
    valorBoton = (int)teclaPisada - 48; //Es necesario operar con "teclaPisada" en este if, en el siguiente if no funciona correctamente. IMPORTANTE
  }

  if (teclado.getState() == 0 && teclaFuePisada)
  {
    if (millis() - teclaTiempo < 3000)
    {

      for (int i = 0; i < numServos; i++)
      {
        grados[i] = gradosGuardados[valorBoton - 1][i]; //Aplica los valores guardados a los actuales
        escribirServoLCD(i, grados[i]);                 //Escribe de nuevo en la pantalla los valores nuevos
      }
    }
    else
    {
      for (int i = 0; i < numServos; i++)
      {
        gradosGuardados[valorBoton - 1][i] = grados[i]; //Guarda los valores actuales en la "memoria"
      }

      //Indica en pantalla que se ha grabado los valores
      lcd.setCursor(7, 0);
      lcd.print("SA");
      lcd.setCursor(7, 1);
      lcd.print("VE");

      tiempoSaveLCD = millis();
    }
    teclaFuePisada = false;
  }
  //Borra de la pantalla el indicador de grabado a los dos segundos
  if (millis() - tiempoSaveLCD > 2000)
  {
    lcd.setCursor(7, 0);
    lcd.print("  ");
    lcd.setCursor(7, 1);
    lcd.print("  ");
  }
}