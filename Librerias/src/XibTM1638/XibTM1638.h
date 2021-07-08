/**
 * @brief Library to use the board TM1638 with 8 leds, 8 displays and 8 buttons.
 * @author Xibhu - Carlos MR - https://github.com/xibhu
 * @note Made in Canary islands, Spain
 * @date 7-7-2021
 * @version 0.1
 * 
 */

#ifndef XibTM1638_h
#define XibTM1638_h

#include <Arduino.h>
#include "XibCommands.h"
#include "TM16XXFonts.h"
#include <XibTimer.h>

class XibTM1638
{
private:
    uint8_t STROBE;
    uint8_t DATA;
    uint8_t CLOCK;
    /**
     * @brief Timer that execute the shift displays animation
     * 
     */
    XibTimer timerShiftChars;
    uint8_t indexShift;

public:
    /**
     * @brief Construct a new Xib T M 1 6 3 8 object
     * 
     * @param strobePin pin that tells to the board, microcontroler is ready to send or receive info
     * @param dataPin   pin that send and receive info
     * @param clockPin  synchronize the communication
     */
    XibTM1638(uint8_t strobePin, uint8_t dataPin, uint8_t clockPin);



    /**
     * @brief Set the Bright object
     * 
     * @param brightValue value from 0 to 7. Less brigth to max.
     */
    void setBright(uint8_t brightValue);
    /**
     * @brief Turn on the board with the minimun bright.
     * 
     */
    void turnOnBoard();
    /**
     * @brief Turn off the board, you can't see anything from the board.
     * 
     */
    void turnOffBoard();



    /**
     * @brief Open the communication with the board, send ONE command and close the communication.
     * 
     * @param command Byte you want to send
     * @see XibCommands.h
     */
    void sendCommand(uint8_t command);
    /**
     * @brief Send a value to a specific address. On or off for leds. 7 segment codification for displays.
     * 
     * @param address led or display to use
     * @param value value give to that address
     * @see ledAddress() and displayAddress() for insert 0-7 and get the specific address
     */
    void sendFixedAddressMode(uint8_t address, uint8_t value);
    /**
     * @brief Send an array of values and a start address to apply each value to each consecutive led/display 
     * 
     * @param firstAddress start address
     * @param arrayValues values to apply to each address
     * @param arraySize 
     */
    void sendIncreasingAddressMode(uint8_t firstAddress, uint8_t arrayValues[], uint8_t arraySize);
    /**
     * @brief Set turn off all displays and leds
     * 
     */
    void resetBoard();



    /**
     * @brief Read buttons from the board
     * 
     * @return uint8_t give you a byte, where each bit is a button. First button from the board (start from left side) is the less significant bit from that byte.
     */
    uint8_t readButtons();
    /**
     * @brief Read buttons from the board, not needed arraySize var because this board have only 8 buttons and this library was design for this board.
     * 
     * @param arrayButtonsBuffer array of size 8, each byte will be filled with the info of each button
     */
    void readButtons(uint8_t arrayButtonsBuffer[]);



    /**
     * @brief turn on one led
     * 
     * @param ledNumber led to turn on, number from 0 to 7
     */
    void turnOnLed(uint8_t ledNumber);
    /**
     * @brief turn off one led
     * 
     * @param ledNumber led to turn off, number from 0 to 7
     */
    void turnOffLed(uint8_t ledNumber);
    /**
     * @brief Put the value (0 off and 1 on) to the specific led
     * 
     * @param ledNumber led to change its state
     * @param state 0 to turn off, 1 to turn on
     */
    void setLedState(uint8_t ledNumber, uint8_t state);


    /**
     * @brief function to calculate the address of a led, giving a number from 0 to 7
     * 
     * @param ledNumber led to get its address, number from 0 to 7
     * @return uint8_t address of the led
     */
    uint8_t ledAddress(uint8_t ledNumber);
    /**
     * @brief function to calculate the address of a display, giving a number from 0 to 7
     * 
     * @param disNumber display to get its address, number from 0 to 7
     * @return uint8_t address of the display
     */
    uint8_t displayAddress(uint8_t disNumber);



    /**
     * @brief write array of char ( 8 chars or less ) on the display starting from a determined display
     * 
     * @param disNumber display where to start the sentence
     * @param sentenceArrayChar array that contains the chars
     * @param arraySize size
     */
    void writeDisplay(uint8_t disNumber, char sentenceArrayChar[], uint8_t arraySize);
    /**
     * @brief write a number ( 8 chars or less ) on the display starting from a determined display
     * 
     * @param disNumber display where to start the number
     * @param sentenceNumber number to display
     */
    void writeDisplayInt(uint8_t disNumber, uint32_t sentenceNumber);
    /**
     * @brief write a double number (decimal, 8 chars or less ) on the display starting from a determined display
     * 
     * @param disNumber display where to start the number
     * @param sentenceNumber number in decimal to display
     */
    void writeDisplayDouble(uint8_t disNumber, double sentenceNumber);



    /**
     * @brief write an array of char of size 8 or larger. And it does an animation, moving the sentence to the left.
     * 
     * @param sentenceArrayChar sentence to display
     * @param arraySize 
     */
    void writeDisplayFromRightToLeft(char sentenceArrayChar[], uint8_t arraySize);
    /**
     * @brief write a number of 8 char size or larger. And it does an animation, moving the sentence to the left.
     * 
     * @param sentenceNumber number to display
     */
    void writeDisplayFromRightToLeftInt(uint32_t sentenceNumber);
    /**
     * @brief write a number with decimal of 8 char size or larger. And it does an animation, moving the sentence to the left.
     * 
     * @param sentenceNumber double to display
     */
    void writeDisplayFromRightToLeftDouble(double sentenceNumber);



    /**
     * @brief write an array of char of size 8 or larger. And it does an animation, moving the sentence to the right.
     * 
     * @param sentenceArrayChar sentence to display
     * @param arraySize 
     */
    void writeDisplayFromLeftToRight(char sentenceArrayChar[], uint8_t arraySize);
    /**
     * @brief write a number of 8 char size or larger. And it does an animation, moving the sentence to the right.
     * 
     * @param sentenceNumber number to display
     */
    void writeDisplayFromLeftToRightInt(uint32_t sentenceNumber);
    /**
     * @brief write a number with decimal of 8 char size or larger. And it does an animation, moving the sentence to the right.
     * 
     * @param sentenceNumber double to display
     */
    void writeDisplayFromLeftToRightDouble(double sentenceNumber);



    /**
     * @brief Set a new time to the animation
     * 
     * @param time new time in milliseconds
     */
    void setShiftTime(uint32_t time);



    /**
     * @brief Display on the displays the sentence "Error"
     * 
     */
    void displayError();
};

#endif
