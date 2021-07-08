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

//To test animation
//Last char as a space, important
char sentenceShift[] = {
    'H', 'E', 'L', 'L', 'O', ' ', 'F', 'r', 'I', 'E', 'n', 'd', ' '};

void setup()
{
    board.turnOnBoard();
    board.setBright(7);
    board.resetBoard();
    board.setShiftTime(500);
}

void loop()
{
    //IMPORTANT
    //ANIMATION WORKS WITH A MINIMUN OF 8 CHARS
    //Use only one function at a time


    //Test text animation right to left
    board.writeDisplayFromRightToLeft(sentenceShift, sizeof(sentenceShift));

    //Test number animation right to left
    //board.writeDisplayFromRightToLeftInt(1234567890);

    //Test double animation right to left
    //board.writeDisplayFromRightToLeftDouble(1234567.89);

    //Test text animation left to right
    //board.writeDisplayFromLeftToRight(sentenceShift, sizeof(sentenceShift));

    //Test number animation left to right
    //board.writeDisplayFromLeftToRightInt(1234567890);

    //Test double animation left to right
    //board.writeDisplayFromLeftToRightDouble(1234567.89);
}