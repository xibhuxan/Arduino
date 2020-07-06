
//=======================================================================================================//|
//                                                                                                       //|
//                                        Program Description Begin                                      //|
//                                                                                                       //|
//=======================================================================================================//|
//                                                                                                       //|
//  This header file contains the class declarations for the employment of a DS1302 Real Time Clock      //|
//  library.  This file is written for compatibility for Arduino Boards, as well as Versilino boards.    //|
//  These functions will work on any pin type available on the boards (PWM, COMMUNICATION, DIGITAL, or   //|
//  ANALOG).                                                                                             //|
//                                                                                                       //|
//=======================================================================================================//|

//                                                                                                       //|
//                                          Acknowledgements End                                         //|
//                                                                                                       //|

                                                                                                         //|
#include "stdio.h" 
                                                                                             //|
#ifndef MyRealTimeClock_H                                                                                 //|
#define MyRealTimeClock_H                                                                                 //|
                                                                                                         //|
#include <stddef.h>                                                                                      //|
  #include <string.h>                                                                                    //|
                                                                                                         //|
#if defined(ARDUINO) && ARDUINO >= 100                                                                   //|
  #include "Arduino.h"                                                                                   //|
  #else                                                                                                  //|
    #include "WProgram.h"                                                                                //|
    #include <pins_arduino.h>                                                                            //|
#endif                                                                                                   //|
                                                                                                         //|
#define DS1302_ENABLE            0x8E                                                                    //|
#define DS1302_TRICKLE           0x90                                                                    //|
                                                                                                         //|
//=======================================================================================================//|
//                                                                                                       //|
//                                     Defines Required for Library End                                  //|
//                                                                                                       //|
class MyRealTimeClock  {                                                                                  //|
  public:                                                                                                //|
//+++++++++++++++++++++++++++++++++++++++++++++ Class Constructor +++++++++++++++++++++++++++++++++++++++//|  
    MyRealTimeClock(uint8_t inSCLK, uint8_t inIO, uint8_t inC_E);                                                     //|
                                                                                                         //|
//++++++++++++++++++++++++++++++++++++++++++++++ Class Functions ++++++++++++++++++++++++++++++++++++++++//|  
    void initRTC(uint8_t CLK, uint8_t IO, uint8_t ENABLE);     // Sets the pins and enable them          //|
    void DS1302_clock_burst_read( uint8_t *p);                 // Reads clock data, and sets pinmode     //|
    void DS1302_clock_burst_write( uint8_t *p);                // Writes clcok data, and sets pinmode    //|
    uint8_t DS1302_read(int address);                          // Reads a byte from DS1302, sets pinmode //|
    void DS1302_write( int address, uint8_t data);             // Writes a byte to DS1302, sets pinmode  //|
    void _DS1302_start( void);                                 // Function to help setup start condition //|
    void _DS1302_stop(void);                                   // Function to help stop the communication//|
    uint8_t _DS1302_toggleread( void);                         // Function to help read byte with bit    //|
    void _DS1302_togglewrite( uint8_t data, uint8_t release);  // Function to help wrtie byte with bit   //|
    void setDS1302Time(uint8_t seconds, uint8_t minutes,       // This function sets the time on the     //|
                       uint8_t hours, uint8_t dayofweek,       // DS1302                                 //|
                       uint8_t dayofmonth, uint8_t month,                                                //|
                       int year);                                                                        //|
    void updateTime();                                         // This function simply updates the time  //|
                                                                                                         //|
//++++++++++++++++++++++++++++++++++++++++++++++ Class variables ++++++++++++++++++++++++++++++++++++++++//|
    uint8_t SCLK;                                                                                        //|
    uint8_t IO;                                                                                          //|
    uint8_t C_E;                                                                                         //|
    uint8_t seconds;                                                                                     //|
    uint8_t minutes;                                                                                     //|
    uint8_t hours;                                                                                       //|
    uint8_t dayofweek;                                                                                   //|
    uint8_t dayofmonth;                                                                                  //|
    uint8_t month;                                                                                       //|
    int year;                                                                                            //|
};                                                                                                       //|

                                                                                                         //|
#endif                                                                          //|
