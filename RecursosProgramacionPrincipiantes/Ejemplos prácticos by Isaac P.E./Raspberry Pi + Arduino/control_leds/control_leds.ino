/*Sketch para control de LEDs de tres colores mediante un script 
en Python creado en nuestra Raspberry Pi*/

int verde = 13;  //Preparamos las variables para los pines de leds
int amarillo = 12;
int rojo = 8;
char c;

void setup(){
  pinMode(verde, OUTPUT); //El pin 13 es una salida
  pinMode(amarillo, OUTPUT); //El pin 12 es una salida
  pinMode(rojo, OUTPUT); //El pin 8 es una salida
  Serial.begin(9600);  //El puerto serie se inicia a 9600 baudios
}

void loop() {
  if (Serial.available()) {   //Si está disponible
    char c = Serial.read(); //Guardamos la lectura en una variable char llamada c
  }
    switch (c) {  //Evalua el valor del caracter ASCII recibido
      case 'V':  //Si es una V se enciende el verde
        digitalWrite(verde, HIGH);
        break;
      case 'A': //Si es una A se enciende el amarillo
        digitalWrite(amarillo, HIGH);
        break;
      case 'R': //Si es una R se enciende el rojo
         digitalWrite(rojo, HIGH);
          break;
    }
      
}
