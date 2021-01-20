/*Mediante dos pulsadores, vamos a manejar un motor para demostrar como trabajar con estas señales*/

int clic=0;         //Variable con la anchura del ciclo útil

void setup()
{
  pinMode(3,OUTPUT);   //Vamos a conectar el pin digital 3 al terminal positivo del motor
  pinMode(5,OUTPUT);   //El negativo va al pin digital 5
  pinMode(4,INPUT);    //El pin 4 digital y el 7 serán las entradas para los pulsadores
  pinMode(7,INPUT);    
}

void loop()  
{ 

  if(digitalRead(4))        //Si se pulsa el puslador conectado al pin 4 se incrementará en 10 el ciclo del motor
    {
    clic=clic+10;        
    delay(20);              //Temporización anti rebotes, para evitar que se confunda con otros pulsados
    while(digitalRead(4));  //Esperar que se deje de presionar el pulsador
    delay(20);              //Temporización anti rebotes...
      if(clic > 300)
        clic=300;          //Evita que el ciclo sea más de 300
    analogWrite(3,clic);   
     }
  if(digitalRead(7))        //Si se pulsa el otro pulsador, de decrementa en 10...
    {
    clic=clic-10;         
    delay(20);              
    while(digitalRead(7));  
    delay(20);              
      if(clic < 0)
        clic =0;           //El Ciclo no puede ser menor de 0
    analogWrite(3,clic);   
     }  
} 



