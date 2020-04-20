#define ENA 5
#define IN1 6
#define IN2 7

#define IN3 8
#define IN4 9
#define ENB 10

char dato = ' ';

int velProg = 0;

void setup()
{

    Serial.begin(9600);

    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

void loop()
{

    if (Serial.available())
    {
        dato = Serial.read();

        switch (dato)
        {
        case '1':
            parada();
            break;

        case '2':

            break;

        case '3':

            break;

        case '4':

            break;

        case '5':

            break;

        case 'a':
            giroUno(255);
            break;

        case 'w':
            frente(255);
            break;

        case 's':
            atras(255);
            break;

        case 'd':
            giroDos(255);
            break;

        case 'v':

            break;

        case 'b':

            break;

        case 'j':

            break;

        case 'i':

            break;

        case 'k':

            break;

        case 'l':

            break;

        case '_':

            break;

        case '0':
            //parada();
            break;

        default:
            //parada();
            break;
        }
    }
}

void giroUno(int vel)
{
    motorAFrente(vel);
    motorBRetroceso(vel);
}

void giroDos(int vel)
{
    motorBFrente(vel);
    motorARetroceso(vel);
}

void frente(int vel)
{
    motorAFrente(vel);
    motorBFrente(vel);
}

void atras(int vel)
{
    motorARetroceso(vel);
    motorBRetroceso(vel);
}

void parada()
{
    motorAParar();
    motorBParar();
}

//motor A

void motorAFrente(int vel)
{
    analogWrite(ENA, vel);
    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
}

void motorARetroceso(int vel)
{
    analogWrite(ENA, vel);
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
}

void motorAParar()
{
    analogWrite(ENA, 0);
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 0);
}

//motor B

void motorBFrente(int vel)
{
    analogWrite(ENB, vel);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
}

void motorBRetroceso(int vel)
{
    analogWrite(ENB, vel);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
}

void motorBParar()
{
    analogWrite(ENB, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 0);
}
