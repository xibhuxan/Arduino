
//Añadir las dos librerías necesarias
#include <Keypad.h>
#include <Key.h>

//Designar la cantidad de columnas y filas que hay
const byte COLS = 4;
const byte ROWS = 4;

//Representación del teclado que va a tener el físico, esto es lo que devolverá cuando se le pregunte qué tecla ha sido pisada
char tablero[COLS][ROWS] =
    {
        {'a', 'b', 'c', 'd'},
        {'e', 'f', 'g', 'h'},
        {'i', 'j', 'k', 'l'},
        {'m', 'n', 'o', 'p'}};

//Pines para las filas, pines para las columnas, en orden según el teclado físico
byte pinRow[ROWS] = {4, 5, 6, 7};
byte pinCol[COLS] = {8, 9, 10, 11};

//Para guardar la tecla que ha sido pisada
char teclaPisada;

//Creación del objeto al que se le introducirá todos los datos anteriores, y así trabajar sobre este objeto únicamente
Keypad teclado = Keypad(makeKeymap(tablero), pinRow, pinCol, ROWS, COLS);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    //Preguntar qué tecla ha sido pisada y guardarla
    teclaPisada = teclado.getKey();

    //Si se ha pisado una tecla, hacer algo
    if(teclaPisada){
        Serial.println(teclaPisada);
    }

}
