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

//boton y su estado
int buttonStick = 2;
bool buttonStickState = 0;

//tiempo que tarda en hacer un desplazamiento el personaje
int despTime = 250;

//cantidad de pasos que da el personaje
int pasos = 0;

//simbolo actual que representa el personaje
int symActual = 0;
//cantidad de simbolos disponibles
int symCantidad = 3;
//bloqueo para cuando se pise el boton, solo se cambie de personaje una vez
bool symBloqueo = false;

void setup()
{
    pinMode(buttonStick, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    
	lcd.init();//iniciar la pantalla
    lcd.backlight();//iniciar la retroiluminacion
    //grabar en la pantalla los simbolos a utilizar, máximo 8
    lcd.createChar(0, sym_bell);
    lcd.createChar(1, sym_hearth);
    lcd.createChar(2, sym_square);
    lcd.home();//dejar la pantalla en blanco y poner el cursor en 0,0
    lcd.write(byte(0));//escribir en el cursor el byte 0, que corresponde al primer personaje
    
    //lo mismo que la pantalla anterior
    lcdSec.init();
    lcdSec.backlight();
    lcdSec.print("Numero de pasos:");
    lcdSec.setCursor(0,1);
    lcdSec.print(0);

}

void loop()
{
	//recoger valores del stick y pulsador
    valStickX = analogRead(stickX);
    valStickY = analogRead(stickY);
    buttonStickState = !digitalRead(buttonStick);
    
    //cambiar el personaje si se ha pulsado el boton
    cambiarSym();

    //si se ha movido el stick en alguno de sus ejes, ejecutar el movimiento en dicha direccion
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


void cambiarSym(){
    if(buttonStickState == 1){
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