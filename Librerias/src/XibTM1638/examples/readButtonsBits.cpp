/**
 * @brief Library to use the board TM1638 with 8 leds, 8 displays and 8 buttons.
 * @author Xibhu - Carlos MR - https://github.com/xibhu
 * @note Made in Canary islands, Spain
 * @date 7-7-2021
 * @version 0.1
 * 
 */

#include <Arduino.h>
#include <XibTM1638.h>

const uint8_t STROBE = 11;
const uint8_t DATA = 12;
const uint8_t CLOCK = 13;

XibTM1638 board(STROBE, DATA, CLOCK);

uint8_t buttonsInfo = 0;

void setup()
{
    board.turnOnBoard();
    board.setBright(7);
    board.resetBoard();
}

void loop()
{
    //In bytes, we start counting bit usually in the less significant bit, from the right

    buttonsInfo = board.readButtons();

    for (uint8_t i = 0; i < BUTTONS_MAX; i++)
    {
        //First parameter get the "i" value as a index to change the value of the leds 0-7
        //Second parameter get the info from the buttons, and as explained in README.md
        //it have 8 bits, each one is the info of a button. It shift "i" positions to right to get
        //the correct value to use

        //if button 6 is on, in binary would be 00100000
        //when "i" have a value of 6, it shift that 1 to the less significant bit
        //getting 00000001 as a result (the same if it was a 0) and using it turn on or off the led
        uint8_t state = buttonsInfo >> i;
        board.setLedState(i, state);
    }

    //ALTERNATIVE
    /*
    for (uint8_t i = 0; i < BUTTONS_MAX; i++)
    {
        //Using function bitRead could be better for begginers
        //Use the variable you want to "watch" and finally get the bit in "i" position 
        board.setLedState(i, bitRead(buttonsInfo, i));
    }
    */
}