#include <LiquidCrystal_I2C.h>
#include <Key.h>
#include <Keypad.h>

#define noButton 0
#define resetButton 1
#define testButton 3

LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte ROWS = 4; //Cantidad de filas de la botonera
const byte COLS = 4; //Cantidad de columnas de la botonera

//Colocar los dígitos o símbolos que corresponden a cada tecla de la botonera
char teclas[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {5, 4, 3, 2}; //Pines que utilizan las filas
byte colPins[COLS] = {6, 7, 8, 9}; //Pines que utilizan las columnas

//Creación del objeto que utiliza el teclado
Keypad teclado = Keypad(makeKeymap(teclas), rowPins, colPins, ROWS, COLS);

unsigned char teclaPisada = ' '; //Para guardar el valor leído del botón
bool teclaFuePisada = false;     //Bloqueo al pisar un botón
unsigned long teclaTiempo = 0;   //Para saber la diferencia de tiempo y actuar de una manera u otra

bool bloqueo = false;
char ultimoBoton = ' ';

void setup()
{
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
}

void loop()
{
    botonera();
}

void funcionBoton(char botonBotonera)
{
    if (botonBotonera != ultimoBoton)
    {

        if (!bloqueo)
        {
            bloqueo = true;
            
            
        }
    }
    else
    {
        bloqueo = false;
    }
ultimoBoton = botonBotonera;
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

        Serial.println(valorBoton);

        teclaFuePisada = false;
    }
}

int readButton()
{
    int pinA4Value = analogRead(A4);

    if (pinA4Value >= 0 && pinA4Value < 200)
    { // si leo cerca de 0 devuelvo botonDerecho
        return resetButton;
    }
    if (pinA4Value >= 500 && pinA4Value < 600)
    { // si leo cerca de 500, devuelvo botonIzquierdo
        return testButton;
    }
    return noButton; // sino leo nada, devuelvo 0
}
