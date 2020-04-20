#include <Wire.h>
 
void setup()
{
    Wire.begin();
    
    Serial.begin(9600);
    while (!Serial); // Espera por la señal serie
    Serial.println("\nI2C Scanner");
}
 
void loop()
{
    byte error, address;
    int nDevices = 0;
    
    Serial.println("Scanning...");

    for(address = 1; address < 127; address++ )
    {
        /*
        El escaner I2C usa el valor devuelto de
        Write.endTransmission para ver si un dispositivo
        reconoció la direccion
        */

        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        
        if (error == 0)
        {
            Serial.print("Dispositivo I2C encontrado en esta dirección 0x");
            if (address<16)
            Serial.print("0");
            Serial.print(address,HEX);
            Serial.println(" !");
            
            nDevices++;
        }
        else if (error==4)
        {
            Serial.print("Error desconocido en esta dirección 0x");
            if (address<16)
            Serial.print("0");
            Serial.println(address,HEX);
        }

    }

    if (nDevices == 0)
        Serial.println("No se encontró ningún dispositivo I2C\n");
    else
        Serial.println("Fin\n");
    
    delay(5000); // wait 5 seconds for next scan
}