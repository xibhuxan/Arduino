/**
 * @brief Library to use the board TM1638 with 8 leds, 8 displays and 8 buttons.
 * @author Xibhu - Carlos MR - https://github.com/xibhu
 * @note Made in Canary islands, Spain
 * @date 7-7-2021
 * @version 0.1
 * 
 */

/*
File that contains the needed commands used in the library and amount of leds and displays.
*/
#ifndef XibCommands_h
#define XibCommands_h

/**Base commands**/
//Not necessary, just to know the reference

const uint8_t DATA_COMMAND              = 0x40;
const uint8_t DISPLAY_CONTROL_COMMAND   = 0x80;
const uint8_t FIRST_ADDRESS_COMMAND     = 0xc0;

/**Data command**/

const uint8_t ADDRESS_INCREASING_MODE   = 0x40;
const uint8_t READ_BUTTONS              = 0x42;
const uint8_t FIXED_ADDRESS_MODE        = 0x44;

/**Display control**/

const uint8_t TURN_OFF_DISPLAY          = 0x80;
const uint8_t TURN_ON_DISPLAY           = 0x88;

/****/

const uint8_t LEDS_DISPLAY_MAX          = 16;
const uint8_t DISPLAY_MAX               = 8;
const uint8_t LEDS_MAX                  = 8;
const uint8_t BUTTONS_MAX               = 8;
const uint8_t BYTES_FROM_BUTTON_MAX     = 4;
const uint8_t BRIGHT_MODES              = 8;

#endif