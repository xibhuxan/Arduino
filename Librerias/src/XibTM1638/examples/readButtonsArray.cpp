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

//Initialize every byte because if not, it would contain "random" values
uint8_t buttonsInfo[BUTTONS_MAX] = {
    0,0,0,0,0,0,0,0
};

void setup()
{
    board.turnOnBoard();
    board.setBright(7);
    board.resetBoard();
    
}

void loop()
{
    //Save the states in a array
    board.readButtons(buttonsInfo);


    for (uint8_t i = 0; i < BUTTONS_MAX; i++)
    {
        //See what have this array in each position and put it to the desired led in order
        board.setLedState(i, buttonsInfo[i]);
    }
    
}