#include <Ethernet.h>
#include <SPI.h>
#include <SD.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 20);

EthernetServer server(80);

String miIp = "";

const byte pinUsar[7] = {2,3,5,6,7,8,9};
bool val[7] = {false,false,false,false,false,false,false};

File fichero;

void setup()
{
    Serial.begin(9600);

    for(int i = 0; i <= 6; i++){
        pinMode(pinUsar[i], OUTPUT);
    }
    

	Ethernet.init(10);
    //SD.begin(4);
    
    if (!SD.begin(4)) {
    Serial.println("Error con la SD!");
    while (1);
    }else{
        Serial.println("Funciona SD");
    }

    
    Serial.println("Shield conectado.");

    Ethernet.begin(mac, ip);

    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
        Serial.println("Tienes el shield de Ethernet mal conectado.");
        while (true) {
        delay(1);
        }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
        Serial.println("El cable de red no está conectado.");
    }

    
    server.begin();
    Serial.print("Servidor en IP: ");
    
    miIp = String(Ethernet.localIP()[0]) + "." + 
    String(Ethernet.localIP()[1]) + "." + 
    String(Ethernet.localIP()[2]) + "." + 
    String(Ethernet.localIP()[3]);

    Serial.println(miIp);
    
    
}

void loop()
{
	EthernetClient client = server.available();

    if (client) {
        
        String s = client.readStringUntil('\r');
        
        for(int i = 0; i <= 6; i++){

            if(s.indexOf("/pin" + String(pinUsar[i])) != -1){
                val[i] = !val[i];
            }
            digitalWrite(pinUsar[i], val[i]);
            
        }
        
        client.println("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");

        
        fichero = SD.open("index.txt");

        if(fichero.available()){
            while(fichero.available())
                client.write(fichero.read());
        }
        fichero.close();
        
        client.stop();

    }
}


 