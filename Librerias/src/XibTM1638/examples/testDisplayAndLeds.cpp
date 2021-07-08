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

void setup()
{
    board.turnOnBoard();
    board.setBright(7);
    board.resetBoard();
    board.setShiftTime(500);

    uint8_t SEGMENTS = 8;

    //Test all the displays
    for (uint8_t i = 0; i < DISPLAY_MAX; i++)
    {

        for (uint8_t j = 0; j < SEGMENTS; j++)
        {
            //Each bit is a segment, so shift "j" positions uses all segments to test 1 by 1
            board.sendFixedAddressMode(board.displayAddress(i), 1 << j);
            delay(50);
        }
        //Turn on all segments in the last display
        board.sendFixedAddressMode(board.displayAddress(i), 0xff);
    }

    //Test all leds
    for (uint8_t i = 0; i < LEDS_MAX; i++)
    {
        board.turnOnLed(i);
        delay(100);
    }

    for (uint8_t i = LEDS_MAX; i > 0; i--)
    {
        board.turnOffLed(i - 1);
        delay(100);
    }

    for (uint8_t i = 0; i < LEDS_MAX; i++)
    {
        board.turnOnLed(i);
        delay(100);
    }

    //Test all bright levels
    for (uint8_t i = 0; i < BRIGHT_MODES; i++)
    {
        board.setBright(i);
        delay(200);
    }

    board.setBright(7);

    board.resetBoard();

    //Test simple number writing
    board.writeDisplayInt(0, 123456);

    delay(1000);

    //Test simple double writing
    board.writeDisplayDouble(0, 6543.14);

    delay(1000);

    char sentence[] = {
        'r', 'E', 'A', 'd', 'y'};
    //Test simple text writing. 8 CHAR OR LESS
    board.writeDisplay(0, sentence, sizeof(sentence));
}

void loop()
{
}