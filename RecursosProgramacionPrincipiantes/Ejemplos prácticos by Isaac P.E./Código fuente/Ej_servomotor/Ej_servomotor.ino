// Controlar un servomotor mediante un simple potenciometro
// En este ejemplo se usa la biblioteca Servo, así que aprenderemos a llamar a las bibliotecas por primera vez

#include <Servo.h>    //Se inicia la biblioteca Servo mediante su archivo de cabecera
 
Servo miservo;  // Creamos un objeto para el control del servomotor
 
int potenciometro = 0;  //El pin del potenciometro se inicia desde el valor 0
int lectura;    //Variable para la lectura del pin analógico donde se conecta el potenciometro
 
void setup() 
{ 
  miservo.attach(9);  //Iniciamos el objeto Servo creado y ligado al pin 9 del servomotor
} 
 
void loop() 
{ 
  lectura = analogRead(potenciometro);            // Lee los valores del potenciometro entre 0 y 1023 
  lectura = map(lectura, 0, 1023, 0, 179);     //Escala nueva de la lectura para adaptarla
  miservo.write(lectura);                  // Posiciona el eje del servo según la lectura
  delay(13);                           // Espera a que el servo esté listo
} 
