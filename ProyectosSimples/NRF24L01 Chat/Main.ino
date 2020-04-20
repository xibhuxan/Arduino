#include <nRF24L01.h>
#include <printf.h>
#include <RF24_config.h>
#include <RF24.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

RF24 radio(7, 8);

const byte direccion[][6] = {"00003","00004"}; //canal de comunicación

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte stickButton = 2;
int stickButtonValue = 0;
bool allowedButton = true;

const byte stickX = A0;
int stickXvalue = 0;
bool allowedHMove = true;

const byte stickY = A1;
int stickYvalue = 0;
bool allowedVMove = true;

byte cursor = 0;
bool allowedSquare = true;
unsigned long startTime = 0;
unsigned long currentTime = 0;
const unsigned long period = 500;

const char abc[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ','!'};
const byte abcTam = 27;
char frase[16] = "a";
byte numLetra[16] = "";



void setup()
{
    pinMode(stickButton, INPUT_PULLUP);

    radio.begin();
    radio.openReadingPipe(0, direccion[1]); 
    radio.openWritingPipe(direccion[0]);    

    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_250KBPS);
    radio.setChannel(110); //de 0 a 124

    lcd.init();
    lcd.backlight();

    startTime = millis();

    Serial.begin(9600);
}

void loop()
{

    stickButtonValue = !digitalRead(stickButton);
    stickXvalue = analogRead(stickX);
    stickYvalue = analogRead(stickY);


    //Mover stick en horizontal
    if(allowedHMove && stickXvalue > 800){
        allowedHMove = false;
        if(cursor < 15)cursor++;
        lcd.setCursor(cursor-1, 1);
        lcd.print(frase[cursor-1]);
    }
    if(allowedHMove && stickXvalue < 100){
        allowedHMove = false;
        if(cursor > 0)cursor--;
        lcd.setCursor(cursor+1, 1);
        lcd.print(frase[cursor+1]);
    }
    if(!allowedHMove && stickXvalue < 800 && stickXvalue > 100){
        allowedHMove = true;
    }

    //Mover stick en vertical
    if(allowedVMove && stickYvalue < 100){
        allowedVMove = false;
        if(numLetra[cursor] < abcTam)numLetra[cursor]++;
    }
    if(allowedVMove && stickYvalue > 800){
        allowedVMove = false;
        if(numLetra[cursor] > 0)numLetra[cursor]--;
    }
    if(!allowedVMove && stickYvalue < 800 && stickYvalue > 100){
        allowedVMove = true;
        frase[cursor] = abc[numLetra[cursor]];
    }
    

    //Cursor de la pantalla
    currentTime = millis();
    if(currentTime - startTime >= period){
        lcd.setCursor(cursor, 1);

        if(allowedSquare){
            lcd.print("!");
            allowedSquare = false;
        }else{
            lcd.print(abc[numLetra[cursor]]);
            allowedSquare = true;
        }
        //lcd.setCursor(0,1);
        //lcd.print(frase);
        startTime = currentTime;
        Serial.println(frase);
    }



    //Enviar mensaje
    if(allowedButton && stickButtonValue){
        radio.stopListening();
        radio.write(&frase, sizeof(frase));
        allowedButton = false;
    }
    if(!allowedButton && !stickButtonValue){
        allowedButton = true;
    }


    //Escuchar señales que vienen
    radio.startListening();
    if (radio.available())
    {
        char texto[32] = "";
        radio.read(&texto, sizeof(texto));

        lcd.setCursor(0,0);
        lcd.print(texto);
    }
}
