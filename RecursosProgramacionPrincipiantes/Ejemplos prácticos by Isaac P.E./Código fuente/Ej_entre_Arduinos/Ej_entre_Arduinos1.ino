//Comunicación entre placas de Arduino. Puedes ver el esquema llamado Entre-Arduinos de la carpeta "Conexiones eléctricas"
/*Con este ejemplo se pretende que un Arduino comunique a otro su estado y el otro haga otra función con luces mediante 
los datos que lleguen por la comunicación serie de las placas. Para ello hay que escribir dos códigos, uno para la placa1 
y otro para la placa2 de Arduino.*/

int boton = 0;
int contador = 0;

void setup() {
  pinMode(13, OUTPUT);  //Ponemos el pin 13 como salida y el 2 como entrada
  pinMode(2, INPUT); 
  Serial.begin(9600);  //Especificamos los baudios o bps a los que transmitirá el puerto serie
}
void loop() {
  boton = digitalRead(2); //Comprobamos el estado del botón
  if (boton == HIGH) {          //Hace que la luz se encienda y el contador avance 1, luego envía el estado al puerto serie
    digitalWrite(13, HIGH);
    contador = contador + 1; 
    Serial.println(contador); 
  }
  else {
    digitalWrite(13, LOW);
  }
}
