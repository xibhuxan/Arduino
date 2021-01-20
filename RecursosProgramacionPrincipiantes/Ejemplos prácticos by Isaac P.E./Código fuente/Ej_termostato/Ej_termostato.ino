//Un simple termostado que activa un ventilador/resistencia para crear un sistema de climatización
//Así regulamos la temperatura. Esto se consigue gracias a que conectamos un ventilador al pin 9 y 
//una resistencia a modo de calentador en el pin 11

int lectura;              //Variable para la lectura del canal analógico A4
int tempmax=30;           //Temperatura máxima
int tempmin=26;           //Temperatura mínima

void setup()
{
  pinMode(9,OUTPUT);  //Ponemos los pines en modo salida y ajustamos la velocidad en baudios
  pinMode(11,OUTPUT);  
  Serial.begin(9600);  
}

void loop()
{
   lectura=analogRead(A4);    //Realiza la conversión del sensor de temperatura conectado al A4
   lectura=(lectura*500.0)/1024.0;    //Calcula la temperatura en ºC
   Serial.println(lectura);   //Transmite la temperatura en valores decimales

   if(lectura > tempmax)      //Si la temperatura supera la máxima se activa el ventilador y desactiva el calentador
     {
       digitalWrite(9,HIGH);  
       digitalWrite(11,LOW);  
     }
   else
   if(lectura < tempmin)      //Si la temperatura es inferior hace lo contrario
     {
       digitalWrite(9,LOW);  
       digitalWrite(11,HIGH);  
     }
    else               //En cualquier otro caso desactiva ambos pines
     {
       digitalWrite(9,LOW);  
       digitalWrite(11,LOW);  
     } 
   delay(800);            //Temporiza las mediciones de temperatura cada 800 ms
}

