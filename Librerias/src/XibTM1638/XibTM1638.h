
#ifndef XibTM1638_h
#define XibTM1638_h

#include <Arduino.h>
#include "Letras.h"

class XibTM1638
{
private:
    byte STROBE;
    byte DATA;
    byte CLOCK;
    byte ledDir(byte ledNum);
    byte displayDir(byte disNum);
    byte selectNumber(byte number);
    byte selectLetter(char letter);
    byte indiceShift;
    long tiempoShift;
    byte indicePalabraShift;
    long tiempoPalabraShift;
public:
    XibTM1638(byte strobePin, byte dataPin, byte clockPin);
    void init();
    void setBright(byte value);
    void sendCommand(uint8_t value);
    void resetCommand();
    uint8_t readButtons();
    void sendData(byte component, byte value);
    void onRed(byte ledNum);
    void onGreen(byte ledNum);
    void onRedGreen(byte ledNum);
    void offLed(byte ledNum);
    void writeDisplay(byte disNum, byte disLed);
    void writeDisplay(byte disNum, char disLed);
    void writeDisplayShift(char myWords[], int tam, int time);
    void writeDisplayShift(long myNumber, int time);
    void writeDisplayShift(String sentence, int time);
    void writeDisplayShift(int myNumber, int time);
    void writeDisplayShift(double myNumber, int time);
    void cleanDisplay(byte disNum);

};

#endif
