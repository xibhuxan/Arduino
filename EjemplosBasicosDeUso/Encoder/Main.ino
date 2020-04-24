
const byte CLKpin = 2; //Pin donde se conecta el CLK
const byte DTpin = 3;  //Pin donde se conecta el DT
const byte SWpin = 4;  //Pin donde se coloca el SW

int CLKactual = 0;   //Donde se guarda el estado actual del pin CLK
int CLKanterior = 0; //Donde se guarda el último estado del pin CLK
int SWactual = 0;    //Donde se guarda el estado actual del botón
int SWanterior = 0;  //Donde se guarda el último estado del botón

int contador = 0; //Variable para hacer uso del encoder

String sentido = ""; //Donde se escribirá el estido del giro

void setup()
{
    //Configuración de pines como entradas
    pinMode(CLKpin, INPUT);
    pinMode(DTpin, INPUT);
    pinMode(SWpin, INPUT_PULLUP);
    //Lectura anticipada para tener un valor guardado
    CLKanterior = digitalRead(CLKpin);

    Serial.begin(9600);
}

void loop()
{
    CLKactual = digitalRead(CLKpin); //Leer el valor actual

    //Si el valor actual es distinto al anterior significa que ha habido un movimiento.
    //Y si el actual es 1, es para reaccionar a un solo cambio de estado y envitar contajes dobles
    if (CLKactual != CLKanterior && CLKactual == 1)
    {
        //Para determinar el sentido, se compara el DT con el CLK.
        //Si son distintos, el sentido es antihorario
        //Si es igual, el sentido es horario
        if (digitalRead(DTpin) != CLKactual)
        {
            contador--;
            sentido = "negativo";
        }
        else
        {
            contador++;
            sentido = "positivo";
        }

        Serial.print(sentido);
        Serial.print(" ");
        Serial.println(contador);
    }

    CLKanterior = CLKactual;


    //Lectura del botón
    SWactual = digitalRead(SWpin);
    //Si el botón es igual a 1, significa que se ha pisado.
    //Se hace un bloqueo para que solo detecte una pulsación, como un flanco, a través de la variable SWanterior
    if (SWactual == 1 && SWactual != SWanterior)
    {
        Serial.println("pisado");
    }
    SWanterior = SWactual;

    delay(1); //Para evitar que sucedan cosas feas
}
