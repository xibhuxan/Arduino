
//Designar los pines de salida que van a la placa
const byte bobina1 = 2;
const byte bobina2 = 3;
const byte bobina3 = 4;
const byte bobina4 = 5;

//Configurar todos los pines como salida
void setup()
{
    pinMode(bobina1, OUTPUT);
    pinMode(bobina2, OUTPUT);
    pinMode(bobina3, OUTPUT);
    pinMode(bobina4, OUTPUT);
}


void loop()
{
    girar(10); //Utilizar la función que hace mover el motor, dándole como parámetro el tiempo entre cada activación de bobina
}

//Función auxiliar para ahorrar líneas de código, escribe en las salidas
void configurarSalidas(int a, int b, int c, int d)
{
    digitalWrite(bobina1, a);
    digitalWrite(bobina2, b);
    digitalWrite(bobina3, c);
    digitalWrite(bobina4, d);
}

//Utiliza la función auxiliar dándole una combinación de activación de bobinas a pares, esto mejora la fuerza del motor
void girar(int tiempo)
{
    configurarSalidas(1, 1, 0, 0);
    delay(tiempo);
    configurarSalidas(0, 1, 1, 0);
    delay(tiempo);
    configurarSalidas(0, 0, 1, 1);
    delay(tiempo);
    configurarSalidas(1, 0, 0, 1);
    delay(tiempo);
}