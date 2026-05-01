#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//tamaño de la pantalla
#define TAMX 16
#define TAMY 2

//inicializar las pantallas con direcciones distintas (fisicamente tienen que tener direcciones distintas)

LiquidCrystal_I2C lcd(0x27, 16, 2);
LiquidCrystal_I2C lcdSec(0x26, 16, 2);

//entradas analogicas de los ejes del stick
int stickX = A0;
int stickY = A1;

//valores de las entradas del stick
int valStickX = 0;
int valStickY = 0;

//coordenada actual del personaje
int coorX = 0;
int coorY = 0;

//coordenada anterior del personaje
int coorXOld = 0;
int coorYOld = 0;

//boton del sitck y su estado
int buttonStick = 2;
bool buttonStickState = 0;

//boton externo y su estado
int buttonExterno = 3;
int buttonExternoState = 0;

//tiempo que tarda en hacer un desplazamiento el personaje
int despTime = 250;

//cantidad de pasos que da el personaje
int pasos = 0;

//simbolo actual que representa el personaje
int symActual = 0;
//cantidad de simbolos disponibles
int symCantidad = 4;
//bloqueo para cuando se pise el boton, solo se cambie de personaje una vez
bool symBloqueo = false;

//cantidad de bombas
int bombas = 0;
//cantidad de intentos
int intentos = 0;
bool bomBloqueo = false;

//coordenadas de las bombas
int coorBombas[TAMX][TAMY];



void setup()
{
    randomSeed(analogRead(2));
    pinMode(buttonStick, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);

	lcd.init();
    lcd.backlight();
    lcd.createChar(0, sym_bell);
    lcd.createChar(1, sym_hearth);
    lcd.createChar(2, sym_square);
    lcd.createChar(3, sym_human);
    lcd.home();
    //lcd.write(byte(0));
    
    lcdSec.init();
    lcdSec.backlight();
    lcdSec.print("P:");
    lcdSec.setCursor(7,0);
    lcdSec.print("B:");
    lcdSec.setCursor(14,0);
    lcdSec.print("I:");

    bombas = random(5,10);
    intentos = random(15,25);

    posicionarBombas();

    lcdSec.setCursor(0,1);
    lcdSec.print(0);
    lcdSec.setCursor(7,1);
    lcdSec.print(bombas);
    lcdSec.setCursor(14,1);
    lcdSec.print(intentos);

    lcd.setCursor(0,0);
    symActual = 3;
    lcd.write(symboloActual());

}

void (* reiniciar)(void) = 0;

void loop()
{

    if(intentos >= bombas){
        miPrograma();
    }
    else{
        lcd.setCursor(0,0);
        lcd.print("  HAS  PERDIDO  ");
        delay(5000);
        reiniciar();
    }

    if(bombas == 0){
        lcd.setCursor(0,0);
        lcd.print("  HAS  GANADO  ");
        delay(5000);
        reiniciar();
    }
        

}

void miPrograma(){
    valStickX = analogRead(stickX);
    valStickY = analogRead(stickY);
    buttonStickState = !digitalRead(buttonStick);
    buttonExternoState = digitalRead(buttonExterno);
    
    cambiarSym(buttonExternoState);
    mirarMina(buttonStickState);

    if(valStickX < 450){
        moverIzquierda();
    }
    if(valStickX > 550){
        moverDerecha();
    }
    if(valStickY < 450){
        moverArriba();
    }
    if(valStickY > 550){
        moverAbajo();
    }
}

void posicionarBombas(){
    Serial.begin(19200);
    Serial.println("-----------------");
    int tempX = 0;
    int tempY = 0;
    int bombasInicial = bombas;
    for(int i = 0; i < bombasInicial; i++){
        tempX = random(16);
        tempY = random(2);


        if((tempX == 0 && tempY == 0) || coorBombas[tempX][tempY] == 1){
            bombas--;
        }else{
            coorBombas[tempX][tempY] = 1;
            lcd.setCursor(tempX, tempY);
            lcd.print("X");
        }
        
        
        Serial.print("X de la bomba: ");
        Serial.println(tempX);
        Serial.print("Y de la bomba: ");
        Serial.println(tempY);

    }
}

void mirarMina(int botonMirar){ 

    if(botonMirar == 1){

        if(!bomBloqueo){
            bomBloqueo = true;
            intentos--;
            lcdSec.setCursor(14,1);
            lcdSec.print("  ");
            lcdSec.setCursor(14,1);
            lcdSec.print(intentos);

            if(coorBombas[coorX][coorY] == 1){
                bombas--;
                lcdSec.setCursor(7,1);
                lcdSec.print(bombas);
                coorBombas[coorX][coorY] = 0;
            }

        }

    }else{
        bomBloqueo = false;
    }
    
}

void cambiarSym(int botonCambio){
    if(botonCambio == 1){
        digitalWrite(LED_BUILTIN, 1);
        if(!symBloqueo){
            symBloqueo = true;

            symActual = (symActual+1)%symCantidad;
            escribirChar();
        }
    }else{
        symBloqueo = false;
        digitalWrite(LED_BUILTIN, 0);
    }
}

byte symboloActual(){
    return byte(symActual);
}

void escribirChar(){
        borrarChar();
        lcd.setCursor(coorX,coorY);
        lcd.write(symboloActual());
        
        delay(despTime);
}

void borrarChar(){
    lcd.setCursor(coorXOld,coorYOld);
    lcd.print(" ");
}
void moverArriba(){
    if(puedeMoverArriba()){
        mover(0);
    }
}
void moverDerecha(){
    if(puedeMoverDerecha()){
        mover(1);
    }
}
void moverAbajo(){
    if(puedeMoverAbajo()){
        mover(2);
    }
}
void moverIzquierda(){
    if(puedeMoverIzquierda()){
        mover(3);
    }
}

void mover(int direccion){
    
    guardarCoorAnterior();

    switch(direccion){
        case 0:
        coorY -= 1;
            break;

        case 1:
        coorX += 1;
            break;

        case 2:
        coorY += 1;
            break;

        case 3:
        coorX -= 1;
            break;
    }
    escribirChar();
    darPaso();
}

void darPaso(){
    pasos++;
    lcdSec.setCursor(0,1);
    lcdSec.print(pasos);
}

bool puedeMoverIzquierda(){
    if(coorX - 1 >= 0){
        return true;
    }else{
        return false;
    }
}

bool puedeMoverDerecha(){
    if(coorX + 1 < TAMX){
        return true;
    }else{
        return false;
    }
}

bool puedeMoverArriba(){
    if(coorY - 1 >= 0){
        return true;
    }else{
        return false;
    }
}

bool puedeMoverAbajo(){
    if(coorY + 1 < TAMY){
        return true;
    }else{
        return false;
    }
}

void guardarCoorAnterior(){
    coorXOld = coorX;
    coorYOld = coorY;
}