#include <SoftwareSerial.h>

int motorPIN = 3; //Asignación del pin 3 para la velocidad del motor
int direccion = 4;  //Asignación del pin 4 para cambio de giro del motor

byte a1 = 0; //Primer byte que se recibe de la APP
byte a2 = 0; //Segundo byte que se recibe de la APP
unsigned int vel = 0; //Variable para unir los dos bytes anteriores en un solo número

int contBytesBluetooth = 7; //Despreciable

SoftwareSerial bt(10, 11); //RX,TX para los cables del módulo bluetooth

void setup()
{
	pinMode(motorPIN, OUTPUT); //Configurar como salida
    pinMode(direccion, OUTPUT); //Configurar como salida

    digitalWrite(2, HIGH); //Despreciable

    bt.begin(9600); //Iniciar comunicación con el módulo bluetooth en 9600 baudios, es la que utiliza
    Serial.begin(115200); //Iniciar comunicación con el pc a través de USB
    
    
    MiLogLN("Arduino iniciado y comunicaciones hechas."); //Escritura de mensaje

}

void loop()
{
    
    if (bt.available() && contBytesBluetooth == 0){ //Despreciable-Pruebas

        if(bt.available() == 2){ //Exclusivamente cuando hayan dos bytes para leer, 
            //se hace lo de dentro, en caso contrario se limpia el buffer de lectura.

            a1 = bt.read(); //Leer y guardar primer byte
            a2 = bt.read(); //Leer y guardar segundo byte
            vel = (a2 * 256) + a1; //Componer los dos bytes en una sola variable
            
            //Escritura de mensajes y variables a bluetooth y USB
            MiLog("a1: ");
            MiLogLN(a1);
            MiLog("a2: ");
            MiLogLN(a2);
            MiLog("TOTAL: ");
            MiLogLN(vel);
            MiLog("Ciclo de trabajo: ");
            MiLog(a1 * 100 / 255); //Ciclo de trabajo
            MiLogLN("%");
            
            MiLogLN("-------");

            //vel puede ser de 0 a 511, mitad en un sentido, la otra mitad en otro sentido
            if (vel <= 255 ) //menor de 255, un sentido
            {
                digitalWrite(direccion, 0);
            }

            if(vel >= 256){//mayor de 255, otro sentido
                digitalWrite(direccion, 1);
            }

            analogWrite(motorPIN, vel);// ponerle la velocidad
        }else{
            while(bt.available()){ //Vaciar el buffer
                bt.read();
            }
        }

    }else{
        contBytesBluetooth--; //Despreciable-Pruebas
    }
 
}

//Funciones para escribir a la vez en el bluetooth y al USB
void MiLog(String a){
    bt.print(a);
    Serial.print(a);
}

void MiLogLN(String a){
    bt.println(a);
    Serial.println(a);
}
void MiLog(int a){
    bt.print(String(a));
    Serial.print(a);
}

void MiLogLN(int a){
    bt.println(String(a));
    Serial.println(a);
}
