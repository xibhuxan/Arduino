#include <Arduino.h>
#include <XibDebounceEdge.h>   //libreria botones,evita rebotes...para no usar delay
#include <MD_Parola.h>         //libreria matriz,identifica hardware define pines...y
                               //funciones para controlarle digitos,efectos,zonas...
#include <XibTimer.h>

#define NOTE_D5 587
#define NOTE_F5 698
#define NOTE_G5 784
#define NOTE_A5 880            //declaramos cual es el nombre y la frecuencia de los tonos
#define NOTE_B5 988
#define NOTE_CS6 1109
#define NOTE_DS6 1245



int melodiaNotas[] = { // array con las notas de la melodia
    NOTE_D5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_DS6};

int melodiaNotasDecrece[] = {  //melodia2 usada para turno jugador2,resta y falta
  NOTE_F5, NOTE_D5, NOTE_A5, NOTE_G5, NOTE_G5, NOTE_F5, NOTE_D5};

uint8_t melodiaDuraciones[] = {
    // array con la duracion de cada nota
    8,
    8,
    8,
    8,
    8,
    8,
    8,
};

//Valores totales de jugadores y botones de colores
const uint8_t JUGADORES_TOTALES = 2;
const uint8_t BOTONES_COLORES_TOTALES = 7;

//Variables de jugadores
uint8_t jugadorActual = 0;                                    // guarda turno de jugador 0 o 1
const uint8_t ledsJugadoresPin[JUGADORES_TOTALES] = {A4, A5}; //2 diodos leds para indicar turno de jugador
uint8_t puntosMaxJugadores[JUGADORES_TOTALES];                // RECORD de ronda del jugador 1 y 2
uint8_t puntosJugadores[JUGADORES_TOTALES];                   // guarda puntos de los jugadores
uint8_t valorRonda = 0;                                       // valor de la ronda activa

//Variables de botones
const uint8_t botonesColoresPin[BOTONES_COLORES_TOTALES] = {2, 3, 4, 5, 6, 7, 8}; //rojo, amarillo, verde, marron, azul, rosa, negro
const uint8_t botonesColoresValor[BOTONES_COLORES_TOTALES] = {0, 1, 2, 3, 4, 5, 6}; //valores a sumar (corregido en void incrementarPuntos con +1)
const uint8_t botonCambioJugadorPin = 9;     // pulsador cambia de jugador
const uint8_t botonRestarPin = A1;           // pulsador pin analog1 resta un punto al jugadoracual
const uint8_t botonFaltaPin = A2;            // pulsador pin analog2 suma 4 al contrario
uint8_t debounceTime = 20;
XibDebounceEdge cambioJugadorButtonXib(debounceTime);
XibDebounceEdge botonRojoXib(debounceTime);
XibDebounceEdge botonAmarilloXib(debounceTime);
XibDebounceEdge botonVerdeXib(debounceTime);
XibDebounceEdge botonMarronXib(debounceTime);
XibDebounceEdge botonAzulXib(debounceTime);
XibDebounceEdge botonRosaXib(debounceTime);
XibDebounceEdge botonNegroXib(debounceTime);
XibDebounceEdge botonRestaXib(debounceTime);
XibDebounceEdge botonFaltaXib(debounceTime);

XibTimer temporizadorZonaMedia(1500);
uint8_t contadorZonaMedio = 5; //Para que el primer valor del módulo sea 0 y se quede el string "break"
uint8_t elementosMaximosZonaMedio = 6;

//Buzzer
const uint8_t buzzerPin = A0; // buzzer

//Variables matrices led 8x8
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW   //Define la interfaz de hardware.
const uint8_t MAX_DEVICES = 9;              //la cantidad de dispositivos que tenemos en la cadena
const uint8_t NUM_ZONES = 3;                //nº de zonas en las que se divide matriz

const uint8_t CLK_PIN = 13;                 //pines conexion matriz
const uint8_t DATA_PIN = 11;
const uint8_t CS_PIN = 10;

MD_Parola pantalla = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES); //conexion SPI

uint8_t * stringComunes[] = {
    "Jug1",    
    "break",   
    "Jug2"}; 

uint8_t * valoresMostrarPantalla[NUM_ZONES] = {
    stringComunes[0],    //inicializa zona 1 imprimiendo el texto,luego actualiza cada vez que se pulsa un boton
    stringComunes[1],   //zona 2 usada para mostrar el valor maximo alcanzado en un turno
    stringComunes[2]};   //zona 3 muestra puntos jugador 2
 
void convertirPuntuacionAString()
{
  itoa(puntosJugadores[0], valoresMostrarPantalla[0], 10);                 // itoa, integer to array (de char). el primer parámetro es el valor(numero)
  //itoa(puntosMaxJugadores[jugadorActual], valoresMostrarPantalla[1], 10);  // que queremos mostrar asi que lo pasamos a array de char,el segundo parámetro
  itoa(puntosJugadores[1], valoresMostrarPantalla[2], 10);                 //  es el array donde quieres escribir, y el 10 significa la base, decimal,
}

void reproducirMelodia(uint8_t vueltas, uint16_t duracionMaxima, float multiplicadorDuracion)
{
  for (int i = 0; i-1 < vueltas; i++)
  {                                                            // bucle repite i veces
    uint16_t duracion = duracionMaxima / melodiaDuraciones[i]; // duracion de la nota en milisegundos
    tone(buzzerPin, melodiaNotas[i], duracion);                // ejecuta el tono con la duracion
    float pausa = duracion * multiplicadorDuracion;            // calcula pausa
    delay(pausa);                                              // demora con valor de pausa
    noTone(buzzerPin);                                         // detiene reproduccion de tono
  }
}

void reproducirMelodiaB(uint8_t vueltas, uint16_t duracionMaxima, float multiplicadorDuracion)
{
  for (int i = 0; i-1 < vueltas; i++)
  {                                                            // bucle repite i veces
    uint16_t duracion = duracionMaxima / melodiaDuraciones[i]; // duracion de la nota en milisegundos
    tone(buzzerPin, melodiaNotasDecrece[i], duracion);         // ejecuta el tono con la duracion
    float pausa = duracion * multiplicadorDuracion;            // calcula pausa
    delay(pausa);                                              // demora con valor de pausa
    noTone(buzzerPin);                                         // detiene reproduccion de tono
  }
}



void cambiarJugador()
{
  jugadorActual = (jugadorActual + 1) % JUGADORES_TOTALES;
  
if  (jugadorActual)
 {reproducirMelodia(1, 2000, 1.80); }

else
 {reproducirMelodiaB(1, 2000, 1.80); }

  digitalWrite(ledsJugadoresPin[0], jugadorActual);   //encendemos o apagamos led indicador
  digitalWrite(ledsJugadoresPin[1], !jugadorActual);  //de turno ambos jugadores

  valorRonda = 0;                         //ponemos a cero para comenzar un nuevo conteo
  convertirPuntuacionAString();
}

void incrementarPuntos(uint8_t posicionValor)
{

  puntosJugadores[jugadorActual] += botonesColoresValor[posicionValor] + 1;  //sumamos el boton presionado al jugador activo
  valorRonda += botonesColoresValor[posicionValor] + 1;                     //lo mismo con el valor de ronda
  reproducirMelodia(posicionValor, 1000, 1.15);                             //reproducimos tantos tonos como puntos suma

if (valorRonda > puntosMaxJugadores[jugadorActual])     //si estamos superando el Record
  {
    puntosMaxJugadores[jugadorActual] = valorRonda;     //igualamos para que muestre el nuevo Record
  // puntosMaxJugadores[!jugadorActual] = valorRonda; //igualamos tambien oponente para que solo exista un Record
   
  }
  convertirPuntuacionAString();
}

void restarPuntos()
{

  if  (puntosJugadores[jugadorActual] > 0)     //evitamos que la resta baje de cero
  {
   puntosJugadores[jugadorActual] -= 1;     // restamos 1 al jugador actual
  }
 if (valorRonda >= puntosMaxJugadores[jugadorActual] && valorRonda > 0 ) //si estamos marcando record y es superior a cero 
  {                               //primero comparamos y luego evitamos que puntosMaxJugadores[jugadorActual] baje de cero                                                      
     valorRonda -= 1; 
     puntosMaxJugadores[jugadorActual] = valorRonda;  //igualamos el valor maximo con el de la ronda
    // puntosMaxJugadores[!jugadorActual] = valorRonda; //igualamos tambien oponente para que solo exista un Record
  }
  reproducirMelodiaB(1, 1000, 1.30);    //numero de tonos,duracion de la nota,duracion de pausa
  convertirPuntuacionAString();    //imprimimos por pantalla
}

void hacerFalta()
{

  puntosJugadores[!jugadorActual] += 4;   //sumamos 4 puntos al oponente
  reproducirMelodiaB(3, 1000, 1.30);  
  convertirPuntuacionAString();
  
}

//Acciones de cada boton
void onRojoPressed()
{
  incrementarPuntos(botonesColoresValor[0]);  //suma valor del nº boton en este caso 0(+1 corregido en void incrementarPuntos)
}

void onAmarilloPressed()
{
  incrementarPuntos(botonesColoresValor[1]);
}

void onVerdePressed()
{
  incrementarPuntos(botonesColoresValor[2]);
}

void onMarronPressed()
{
  incrementarPuntos(botonesColoresValor[3]);
}

void onAzulPressed()
{
  incrementarPuntos(botonesColoresValor[4]);
}

void onRosaPressed()
{
  incrementarPuntos(botonesColoresValor[5]);
}

void onNegroPressed()
{
  incrementarPuntos(botonesColoresValor[6]);
}

void setup()
{
    Serial.begin(9600);

  for (uint8_t i = 0; i < BOTONES_COLORES_TOTALES; i++)
  {
    pinMode(botonesColoresPin[i], INPUT_PULLUP); //declaramos los pines botones colores como entradas
  }

  pinMode(botonCambioJugadorPin, INPUT_PULLUP);
  pinMode(botonRestarPin, INPUT_PULLUP);
  pinMode(botonFaltaPin, INPUT_PULLUP);

  for (uint8_t i = 0; i < JUGADORES_TOTALES; i++)
  {
    pinMode(ledsJugadoresPin[i], OUTPUT);       //declaramos los leds de estado como salidas
  }

  pinMode(buzzerPin, OUTPUT);    //el altavoz como salida

  digitalWrite(ledsJugadoresPin[0], LOW); // led de turno jugador 1 comienza activado
  digitalWrite(ledsJugadoresPin[1], HIGH); //jugador 2 comienza desactivado

  pantalla.begin(NUM_ZONES); //activamos la pantalla

  // dividimos en 3 zonas las 9 matrices
  pantalla.setZone(0, 0, 2); //zona 1,matrices 1,2 y 3
  pantalla.setZone(1, 3, 5); //zona 2,matrices 4,5 y 6
  pantalla.setZone(2, 6, 8); //zona 3,matrices 7,8 y 9
  pantalla.setIntensity(1);

  for (uint8_t i = 0; i < NUM_ZONES; i++)   //funcion de la libreria parola para mostrar datos en matriz
  {
    pantalla.displayZoneText(i, valoresMostrarPantalla[i], PA_CENTER, pantalla.getSpeed(), pantalla.getPause(), PA_PRINT, PA_NO_EFFECT);
  }                         //llamamos a las zonas de pantalla para mostrar valores obtenidos,
}                           //centrados,obtenemos la velocidad de animación, el tiempo de pausa e imprimir,sin efectos

void loop()   //si presionamos boton actua libreria botones y llama a la funcion void(___)
{       
 
  cambioJugadorButtonXib.whenRisingEdge(!digitalRead(botonCambioJugadorPin), cambiarJugador);
  botonRojoXib.whenRisingEdge(!digitalRead(botonesColoresPin[0]), onRojoPressed);
  botonAmarilloXib.whenRisingEdge(!digitalRead(botonesColoresPin[1]), onAmarilloPressed);
  botonVerdeXib.whenRisingEdge(!digitalRead(botonesColoresPin[2]), onVerdePressed);
  botonMarronXib.whenRisingEdge(!digitalRead(botonesColoresPin[3]), onMarronPressed);
  botonAzulXib.whenRisingEdge(!digitalRead(botonesColoresPin[4]), onAzulPressed);
  botonRosaXib.whenRisingEdge(!digitalRead(botonesColoresPin[5]), onRosaPressed);
  botonNegroXib.whenRisingEdge(!digitalRead(botonesColoresPin[6]), onNegroPressed);
  botonRestaXib.whenRisingEdge(!digitalRead(botonRestarPin), restarPuntos);
  botonFaltaXib.whenRisingEdge(!digitalRead(botonFaltaPin), hacerFalta);

  if (pantalla.displayAnimate()) // Anima y devuelve verdadera cuando se completa una animación
  {
    for (uint8_t i = 0; i < NUM_ZONES; i++)
    {
      if (pantalla.getZoneStatus(i))    //Métodos para el control de objetos centrales.
      {
        pantalla.setTextEffect(i, PA_PRINT, PA_NO_EFFECT);  //Configura los efectos de texto de entrada y salida para todas las zonas.

        // llama a Parola si hay nueva animacion
        pantalla.displayReset(i);
      }
    }
  }

    temporizadorZonaMedia.cycleCompleted([](){

        contadorZonaMedio = (contadorZonaMedio + 1) % elementosMaximosZonaMedio;
        switch (contadorZonaMedio)
        {
        case 0:
             valoresMostrarPantalla[1] = stringComunes[0];
            break;
        case 1:
            valoresMostrarPantalla[1] = stringComunes[1];
            break;
        case 2:
            itoa(puntosMaxJugadores[jugadorActual], valoresMostrarPantalla[1], 10);
            break;
        case 3:
            valoresMostrarPantalla[1] = stringComunes[0];
            break;
        case 4:
            valoresMostrarPantalla[1] = stringComunes[2];
            break;
        case 5:
            itoa(puntosMaxJugadores[!jugadorActual], valoresMostrarPantalla[1], 10);
            break;
        
        default:
            break;
        }

        Serial.println(contadorZonaMedio);
    
    });

}
