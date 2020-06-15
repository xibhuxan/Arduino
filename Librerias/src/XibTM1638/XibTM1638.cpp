
/*
 Created by xibhu
 https://github.com/xibhu/arduino
 */

#include "XibTM1638.h"

XibTM1638::XibTM1638(byte strobePin, byte dataPin, byte clockPin)
{
    STROBE = strobePin;
    DATA = dataPin;
    CLOCK = clockPin;
    pinMode(STROBE, OUTPUT);
    pinMode(CLOCK, OUTPUT);
    pinMode(DATA, OUTPUT);
    init();
}

void XibTM1638::init()
{
    sendCommand(0x8f);
    resetCommand();
}

void XibTM1638::setBright(byte value)
{

    if (value < 0 || value > 8)
    {
        value = 8;
    }

    byte valor = 0x88;
    valor = valor | value;
    sendCommand(valor);
}

void XibTM1638::sendCommand(uint8_t value)
{
    digitalWrite(STROBE, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, value);
    digitalWrite(STROBE, HIGH);
}

void XibTM1638::resetCommand()
{
    sendCommand(0x40);
    digitalWrite(STROBE, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, 0xc0);
    for (uint8_t i = 0; i < 16; i++)
    {
        shiftOut(DATA, CLOCK, LSBFIRST, 0x00);
    }
    digitalWrite(STROBE, HIGH);
}

uint8_t XibTM1638::readButtons()
{
    uint8_t buttons = 0;
    digitalWrite(STROBE, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, 0x42);

    pinMode(DATA, INPUT);

    for (uint8_t i = 0; i < 4; i++)
    {
        uint8_t v = shiftIn(DATA, CLOCK, LSBFIRST) << i;
        buttons |= v;
    }

    pinMode(DATA, OUTPUT);
    digitalWrite(STROBE, HIGH);
    return buttons;
}

void XibTM1638::sendData(byte component, byte value)
{
    sendCommand(0x44);
    digitalWrite(STROBE, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, component);
    shiftOut(DATA, CLOCK, LSBFIRST, value);
    digitalWrite(STROBE, HIGH);
}

byte XibTM1638::ledDir(byte ledNum)
{
    return 0xc0 | ledNum * 2 + 1;
}

void XibTM1638::onRed(byte ledNum)
{
    sendData(ledDir(ledNum), 0x01);
}
void XibTM1638::onGreen(byte ledNum)
{
    sendData(ledDir(ledNum), 0x02);
}
void XibTM1638::onRedGreen(byte ledNum)
{
    sendData(ledDir(ledNum), 0x03);
}
void XibTM1638::offLed(byte ledNum)
{
    sendData(ledDir(ledNum), 0x00);
}
byte XibTM1638::displayDir(byte disNum)
{
    return 0xc0 | disNum * 2;
}
void XibTM1638::writeDisplay(byte disNum, byte disLed)
{
    sendData(displayDir(disNum), selectNumber(disLed));
}
void XibTM1638::writeDisplay(byte disNum, char letter)
{
    sendData(displayDir(disNum), selectLetter(letter));
}

byte XibTM1638::selectNumber(byte number)
{
    byte n;
    switch (number)
    {
    case 0:
        n = N0;
        break;
    case 1:
        n = N1;
        break;
    case 2:
        n = N2;
        break;
    case 3:
        n = N3;
        break;
    case 4:
        n = N4;
        break;
    case 5:
        n = N5;
        break;
    case 6:
        n = N6;
        break;
    case 7:
        n = N7;
        break;
    case 8:
        n = N8;
        break;
    case 9:
        n = N9;
        break;
    }
    return n;
}

byte XibTM1638::selectLetter(char letter)
{
    letter = toLowerCase(letter);
    byte l;
    switch (letter)
    {
    case 'a':
        l = LA;
        break;
    case 'b':
        l = LB;
        break;
    case 'c':
        l = LC;
        break;
    case 'd':
        l = LD;
        break;
    case 'e':
        l = LE;
        break;
    case 'f':
        l = LF;
        break;
    case 'g':
        l = LG;
        break;
    case 'h':
        l = LH;
        break;
    case 'i':
        l = LI;
        break;
    case 'j':
        l = LJ;
        break;
    case 'k':
        l = LK;
        break;
    case 'l':
        l = LL;
        break;
    case 'm':
        l = LM;
        break;
    case 'n':
        l = LN;
        break;
    case 'o':
        l = LO;
        break;
    case 'p':
        l = LP;
        break;
    case 'q':
        l = LQ;
        break;
    case 'r':
        l = LR;
        break;
    case 's':
        l = LS;
        break;
    case 't':
        l = LT;
        break;
    case 'u':
        l = LU;
        break;
    case 'v':
        l = LV;
        break;
    case 'w':
        l = LW;
        break;
    case 'x':
        l = LX;
        break;
    case 'y':
        l = LY;
        break;
    case 'z':
        l = LZ;
        break;
    case ' ':
        l = Lespa;
        break;
    case '0':
        l = N0;
        break;
    case '1':
        l = N1;
        break;
    case '2':
        l = N2;
        break;
    case '3':
        l = N3;
        break;
    case '4':
        l = N4;
        break;
    case '5':
        l = N5;
        break;
    case '6':
        l = N6;
        break;
    case '7':
        l = N7;
        break;
    case '8':
        l = N8;
        break;
    case '9':
        l = N9;
        break;
    case '.':
        l = NP;
        break;
    }
    return l;
}

void XibTM1638::writeDisplayShift(char myWords[], int tam, int time)
{
    tam -= 1;
    if (indicePalabraShift <= 0)
    {
        indicePalabraShift = 8 + tam;
    }

    if (millis() - tiempoPalabraShift > time)
    {
        indicePalabraShift--;
        tiempoPalabraShift = millis();

        for (int i = 0; i < tam; i++)
        {

            if (indicePalabraShift <= 7)
            {
                cleanDisplay(indicePalabraShift);
            }

            if (indicePalabraShift + i < tam || indicePalabraShift - tam + i >= 8)
            {
                continue;
            }

            writeDisplay(indicePalabraShift - tam + i, myWords[i]);
        }
    }
}

void XibTM1638::writeDisplayShift(long myNumber, int time)
{
    String numeros = String(myNumber);
    int numerosTam = numeros.length() + 1;

    char misNumeros[numerosTam];
    numeros.toCharArray(misNumeros, numerosTam);

    writeDisplayShift(misNumeros, sizeof(misNumeros), time);
}

void XibTM1638::writeDisplayShift(String sentence, int time)
{
    String numeros = String(sentence);
    int numerosTam = numeros.length() + 1;

    char misNumeros[numerosTam];
    numeros.toCharArray(misNumeros, numerosTam);

    writeDisplayShift(misNumeros, sizeof(misNumeros), time);
}

void XibTM1638::writeDisplayShift(int myNumber, int time)
{
    String numeros = String(myNumber);
    int numerosTam = numeros.length() + 1;

    char misNumeros[numerosTam];
    numeros.toCharArray(misNumeros, numerosTam);

    writeDisplayShift(misNumeros, sizeof(misNumeros), time);
}

void XibTM1638::writeDisplayShift(double myNumber, int time)
{
    String numeros = String(myNumber);
    int numerosTam = numeros.length() + 1;

    char misNumeros[numerosTam];
    numeros.toCharArray(misNumeros, numerosTam);

    writeDisplayShift(misNumeros, sizeof(misNumeros), time);
}

void XibTM1638::cleanDisplay(byte disNum)
{
    sendData(displayDir(disNum), 0x00);
}
