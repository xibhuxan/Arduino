/**
 * @brief Library to use the board TM1638 with 8 leds, 8 displays and 8 buttons.
 * @author Xibhu - Carlos MR - https://github.com/xibhu
 * @note Made in Canary islands, Spain
 * @date 7-7-2021
 * @version 0.1
 * 
 */

#include "XibTM1638.h"

XibTM1638::XibTM1638(uint8_t strobePin, uint8_t dataPin, uint8_t clockPin)
{
    STROBE = strobePin;
    DATA = dataPin;
    CLOCK = clockPin;
    
    pinMode(STROBE, OUTPUT);
    pinMode(CLOCK, OUTPUT);
    pinMode(DATA, OUTPUT);
    digitalWrite(STROBE, HIGH);

    indexShift = 0;
    timerShiftChars = XibTimer(1000);
}

void XibTM1638::setBright(uint8_t brightValue)
{

    if (brightValue < 0 || brightValue > 7)
    {
        brightValue = 7;
    }
    //TURN_ON_DISPLAY in bits are 10001000, and bright value is from 0 to 7, in bits from 000 to 111
    //So doing a "logic or" you get a var that turn on the display with a specific bright
    uint8_t finalBrightCommand = TURN_ON_DISPLAY | brightValue;
    sendCommand(finalBrightCommand);
}

void XibTM1638::turnOnBoard()
{
    sendCommand(TURN_ON_DISPLAY);
}

void XibTM1638::turnOffBoard()
{
    sendCommand(TURN_OFF_DISPLAY);
}

void XibTM1638::sendCommand(uint8_t command)
{
    digitalWrite(STROBE, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, command);
    digitalWrite(STROBE, HIGH);
}

void XibTM1638::sendFixedAddressMode(uint8_t address, uint8_t value)
{
    sendCommand(FIXED_ADDRESS_MODE);

    digitalWrite(STROBE, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, address);
    shiftOut(DATA, CLOCK, LSBFIRST, value);
    digitalWrite(STROBE, HIGH);
}

void XibTM1638::sendIncreasingAddressMode(uint8_t firstAddress, uint8_t arrayValues[], uint8_t arraySize)
{
    sendCommand(ADDRESS_INCREASING_MODE);

    digitalWrite(STROBE, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, firstAddress);
    for (uint8_t i = 0; i < arraySize; i++)
    {
        shiftOut(DATA, CLOCK, LSBFIRST, arrayValues[i]);
    }
    digitalWrite(STROBE, HIGH);
}

void XibTM1638::resetBoard()
{
    uint8_t values[LEDS_DISPLAY_MAX];
    for (uint8_t i = 0; i < LEDS_DISPLAY_MAX; i++)
    {
        values[i] = 0;
    }

    sendIncreasingAddressMode(FIRST_ADDRESS_COMMAND, values, LEDS_DISPLAY_MAX);
}

uint8_t XibTM1638::readButtons()
{
    uint8_t buttons = 0;
    digitalWrite(STROBE, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, READ_BUTTONS);

    pinMode(DATA, INPUT);

    for (uint8_t i = 0; i < 4; i++)
    {
        //Shift each bit one position every iteration an put together in one byte var. Explained in README.md
        uint8_t v = shiftIn(DATA, CLOCK, LSBFIRST) << i;
        buttons |= v;
    }

    pinMode(DATA, OUTPUT);
    digitalWrite(STROBE, HIGH);
    return buttons;
}

void XibTM1638::readButtons(uint8_t arrayButtonsBuffer[])
{
    digitalWrite(STROBE, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, READ_BUTTONS);

    pinMode(DATA, INPUT);

    for (uint8_t i = 0; i < BYTES_FROM_BUTTON_MAX; i++)
    {
        //Read bytes and save in a var
        uint8_t v = shiftIn(DATA, CLOCK, LSBFIRST);

        //Using AND logic operator we can take that bit from the source and isolate it.
        //Every bit operated with 0 remains always 0, but any bit operated with 1, takes the original value
        arrayButtonsBuffer[i] = v & 0b00000001;
        //Because of the bit is in other place than first bit, after get the bit, we shift that bit to the first position.
        arrayButtonsBuffer[i + 4] = (v & 0b00010000) >> 4;
    }

    pinMode(DATA, OUTPUT);
    digitalWrite(STROBE, HIGH);
}

void XibTM1638::turnOnLed(uint8_t ledNumber)
{
    sendFixedAddressMode(ledAddress(ledNumber), 1);
}
void XibTM1638::turnOffLed(uint8_t ledNumber)
{
    sendFixedAddressMode(ledAddress(ledNumber), 0);
}

void XibTM1638::setLedState(uint8_t ledNumber, uint8_t state){
    sendFixedAddressMode(ledAddress(ledNumber), state);
}

uint8_t XibTM1638::ledAddress(uint8_t ledNumber)
{
    // Leds and displays addresses are ordered like this. DISPLAY | LED | DISPLAY | LED..... until 16 in total
    // Leds are the odds number, so, you have 8 leds, from 0 to 7
    // with ((ledNumber * 2) + 1) you get the odds numbers from 0 to 15

    return FIRST_ADDRESS_COMMAND | ((ledNumber * 2) + 1);
}
uint8_t XibTM1638::displayAddress(uint8_t disNumber)
{
    // with (ledNumber * 2) you get the even numbers from 0 to 15

    return FIRST_ADDRESS_COMMAND | (disNumber * 2);
}

void XibTM1638::displayError()
{
    for (uint8_t i = 0; i < sizeof(ERROR_DATA); i++)
    {
        sendFixedAddressMode(displayAddress(i), ERROR_DATA[i]);
    }
}

void XibTM1638::writeDisplay(uint8_t disNumber, char sentenceArrayChar[], uint8_t arraySize)
{
    if (disNumber + arraySize <= DISPLAY_MAX)
    {
        for (uint8_t i = 0; i < arraySize; i++)
        {
            uint8_t selectChar = sentenceArrayChar[i] - 32;
            sendFixedAddressMode(displayAddress(disNumber + i), FONT_DEFAULT[selectChar]);
        }
    }
}

void XibTM1638::writeDisplayInt(uint8_t disNumber, uint32_t numberToDisplay)
{

    String numbers = String(numberToDisplay);
    uint8_t numSize = numbers.length() + 1;

    char buf[numSize];
    numbers.toCharArray(buf, numSize);
    writeDisplay(disNumber, buf, numSize - 1);
}

void XibTM1638::writeDisplayDouble(uint8_t disNumber, double numberToDisplay)
{
    String numbers = String(numberToDisplay);
    uint8_t numSize = numbers.length() + 1;

    char buf[numSize];
    numbers.toCharArray(buf, numSize);
    writeDisplay(disNumber, buf, numSize - 1);
}

// This uses a "window" strategy. First it expand and duplicate the original array 7 spaces more, one less than number of displays.
// Example: "my array is awesome " as original. (Final space, important to represent correctly the string)
// You first get "my array is awesome my arra"
// You also have a index from 0 to arraySize (the original array, 20 in this case)
// To show you use a "windowArray" of size 8, the number of displays.
// Then you use the index as a start point in each iteration to get 8 chars from the extended array and put in the windowArray. Increment index by 1.
// This works until index reaches arraySize (the original)
// When index has a value of arraySize, windowArray have " my arra"
// Finally, when index has again a value of 0, the windowArray start from the beggining and makes the illusion, having "my array" again.

void XibTM1638::writeDisplayFromRightToLeft(char sentenceArrayChar[], uint8_t arraySize)
{

    if (timerShiftChars.cycleCompleted())
    {
        if (indexShift >= arraySize)
        {
            indexShift = 0;
        }

        char arrayExtraSize[arraySize + DISPLAY_MAX - 1];
        for (uint8_t i = 0; i < arraySize; i++)
        {
            arrayExtraSize[i] = sentenceArrayChar[i];
        }

        for (uint8_t i = 0; i < DISPLAY_MAX - 1; i++)
        {
            arrayExtraSize[arraySize + i] = sentenceArrayChar[i];
        }

        char windowArrayToShow[DISPLAY_MAX];
        for (uint8_t i = 0; i < DISPLAY_MAX; i++)
        {
            windowArrayToShow[i] = arrayExtraSize[indexShift + i];
        }

        writeDisplay(0, windowArrayToShow, DISPLAY_MAX);
        indexShift++;
    }
}

void XibTM1638::writeDisplayFromRightToLeftInt(uint32_t sentenceNumber)
{
    String numbers = String(sentenceNumber);
    uint8_t numSize = numbers.length() + 1;

    char buf[numSize];
    numbers.toCharArray(buf, numSize);

    writeDisplayFromRightToLeft(buf, sizeof(buf));
}

void XibTM1638::writeDisplayFromRightToLeftDouble(double sentenceNumber)
{
    String numbers = String(sentenceNumber);
    uint8_t numSize = numbers.length() + 1;

    char buf[numSize];
    numbers.toCharArray(buf, numSize);

    writeDisplayFromRightToLeft(buf, sizeof(buf));
}

//Same strategt as FromRightToLeft, but index decrements
void XibTM1638::writeDisplayFromLeftToRight(char sentenceArrayChar[], uint8_t arraySize)
{

    if (timerShiftChars.cycleCompleted())
    {
        //as a uint8_t var, with a allowed values 0-255, when it subtract on the last line being 0, 
        //it becomes 255, with that high value, returns to the desired value
        if (indexShift >= arraySize)
        {
            indexShift = arraySize - 1;
        }

        char arrayExtraSize[arraySize + DISPLAY_MAX - 1];
        for (uint8_t i = 0; i < arraySize; i++)
        {
            arrayExtraSize[i] = sentenceArrayChar[i];
        }

        for (uint8_t i = 0; i < DISPLAY_MAX - 1; i++)
        {
            arrayExtraSize[arraySize + i] = sentenceArrayChar[i];
        }

        char windowArrayToShow[DISPLAY_MAX];
        for (uint8_t i = 0; i < DISPLAY_MAX; i++)
        {
            windowArrayToShow[i] = arrayExtraSize[indexShift + i];
        }

        writeDisplay(0, windowArrayToShow, DISPLAY_MAX);

        indexShift--;

        
    }
}
void XibTM1638::writeDisplayFromLeftToRightInt(uint32_t sentenceNumber)
{
    String numbers = String(sentenceNumber);
    uint8_t numSize = numbers.length() + 1;

    char buf[numSize];
    numbers.toCharArray(buf, numSize);

    writeDisplayFromRightToLeft(buf, sizeof(buf));
}
void XibTM1638::writeDisplayFromLeftToRightDouble(double sentenceNumber)
{
    String numbers = String(sentenceNumber);
    uint8_t numSize = numbers.length() + 1;

    char buf[numSize];
    numbers.toCharArray(buf, numSize);

    writeDisplayFromRightToLeft(buf, sizeof(buf));
}

void XibTM1638::setShiftTime(uint32_t time)
{
    timerShiftChars.setTime(time);
}