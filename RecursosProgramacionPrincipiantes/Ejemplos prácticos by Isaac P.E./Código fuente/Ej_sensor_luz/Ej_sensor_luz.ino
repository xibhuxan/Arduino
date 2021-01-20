//Sencillo programa para medir un sensor de luz y retransmitir los datos obtenidos por el puerto serie

int lectura;              //Variable para la lectura del pin analógico

void setup()
{
  Serial.begin(9600);  //Velocidad del canal 9600 baudios
}

void loop()
{
   lectura=analogRead(A2);    //Realiza una conversión del valor analógico de voltaje obtenido
   Serial.println(lectura);   //Retransmite los datos en valores decimales
}

