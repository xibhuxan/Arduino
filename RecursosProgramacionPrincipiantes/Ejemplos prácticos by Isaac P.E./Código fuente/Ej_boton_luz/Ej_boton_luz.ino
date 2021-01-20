//Gobernador de una luz por botón. Puedes ver el conexionado electronico en los dibujos de ejemplo incluidos en la carpeta "Conexionado eléctrico"

int boton = 0;

void setup() {
  pinMode(13, OUTPUT);  //Ponemos como salida el pin digital 13 para el LED
  pinMode(2, INPUT);    //Como entrada irá el pin 2, para recibir la señal del botón
}
void loop(){
  boton = digitalRead(2),   //Leemos el estado del botón
  if (boton == HIGH) {        //Condición de si el botón está pulsado el LED se enciende y si no permanece apagado
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13,LOW);
  }
}

