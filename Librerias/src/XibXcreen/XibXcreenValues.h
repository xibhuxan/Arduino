#ifndef XibXcreenValues_h
#define XibXcreenValues_h
//Calibraje de la pantalla
#define TS_MINX 200
#define TS_MINY 180
#define TS_MAXX 945
#define TS_MAXY 905

//Pines
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

//Más pines
#define YP A1
#define XM A2
#define YM 7
#define XP 6

//Algunos colores
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

//Presión mínima y máxima del táctil, solo para cuestiones de condiciones
#define MINPRESSURE 10
#define MAXPRESSURE 1000

//Resolución de la pantalla
#define LONG_SIDE 320
#define SHORT_SIDE 240

#define MODEL 0x9341
/*
Possible MODEL values
0x9325
0x9328
0x7575
0x9341
0x8357
*/

#endif
