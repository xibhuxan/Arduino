/*Sketch para simular a un semaforo con tres LEDs de colores*/

int verde=13;           //Conexión del LED verde
int amarillo=12;          //Conexión del LED amarillo
int rojo=8;           //Conexión del LED rojo

void setup()
{
//Especificamos si un pin se comportará como una entrada o una salida
pinMode( verde , OUTPUT);      //Salida para el LED verde
pinMode( amarillo , OUTPUT);  // "     "    "   "  amarillo
pinMode( rojo , OUTPUT);      // "     "    "   "  rojo
pinMode( 7, INPUT);        //El pin 7 se queda como entrada
}

void loop()
{
  if(digitalRead(7))      //Si se pulsa el botón conectado al pin7
  {
    delay(3000);            //Esperar 3000ms
    digitalWrite(rojo,LOW);    //La luz roja se apaga
    digitalWrite(verde,HIGH);    //Y se activa la verde
    digitalWrite(verde,LOW);    //Verde se apaga
    digitalWrite(amarillo,HIGH);    //El amarillo se enciende
    delay(500);                     //Parpadeo en secuencias de 500ms
    digitalWrite(amarillo,LOW);
    delay(500);
    digitalWrite(amaraillo,HIGH);
    delay(500);
    digitalWrite(amarillo, LOW);
    delay(500);
    digitalWrite(amarillo,HIGH);
    delay(500);
    digitalWrite(amarillo,LOW);    //Se apaga el amarillo definitivamente
    digitalWrite(rojo,HIGH);     //El led rojo se enciende
    delay(2000);                 
  }
  else       //En caso de que el pulsador del pin7 no esté pulsado...
  {
    digitalWrite(cverde,0);    //El luz verde se apaga
    digitalWrite(amarillo,0);    //El luz amarilla se apaga
    digitalWrite(rojo,1);     //El luz roja parpadea 3 veces
    delay(300);
    digitalWrite(rojo,0);
    delay(300);
    digitalWrite(rojo,1);
    delay(300);
    digitalWrite(rojo,0);
    delay(300);
    digitalWrite(rojo,1);  //Y se mantiene encendida
   }
}

