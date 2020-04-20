#include <SoftwareSerial.h>

SoftwareSerial bt(2,3); 
/*Se crea el objeto para utilizar los pines 2 y 3 como RX y TX de forma respectiva,
esto no es necesario pero para añadir la posibilidad. En caso de no usarlo, se utilizaria
Serial.begin(9600) normal.
*/

const byte led = 13; //pin para el led integrado
 
char option =' '; //caracter que va a recibir el arduino, porque sabemos que solo recibirá caracteres. 
 
void setup(){
  Serial.begin(19200);//puerto serie de ejemplo para utilizar con el usb del pc si fuera necesario
  bt.begin(9600);//puerto serie que utiliza el modulo bluetooth para transmitir informacion
  pinMode(led, OUTPUT); 
}
 
void loop(){
  //si existe información para leer
  if (bt.available()){

    option = bt.read(); //lee un solo caracter, si se deseara leer un string completo, se debe hacer un bucle

    if (option == 'i' )//compara el valor recibido, con 'i'
    {
         digitalWrite(led, 1);
    }
    
    if(option == 'l'){//compara el valor recibido, con 'i'
          digitalWrite(led, 0);
    }
  }
}
