#define ENA 5
#define IN1 6
#define IN2 7

#define IN3 8
#define IN4 9
#define ENB 10

void setup(){

    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

}

void loop()
{
    delay(3000);
    frente(150);
    delay(2000);

    parada();
    delay(2000);
    
    motorAFrente(150);
    motorBRetroceso(150);
    delay(1000);
    
    atras(150);
    delay(2000);
    
    parada();
    delay(2000);

}

void frente(int vel){
    motorAFrente(vel);
    motorBFrente(vel);
}

void atras(int vel){
    motorARetroceso(vel);
    motorBRetroceso(vel);
}

void parada(){
    motorAParar();
    motorBParar();
}

void motorAFrente(int vel){
    analogWrite(ENA, vel);
    digitalWrite(IN1,1);
    digitalWrite(IN2, 0);
}

void motorARetroceso(int vel){
    analogWrite(ENA, vel);
    digitalWrite(IN1,0);
    digitalWrite(IN2,1);
}

void motorAParar(){
    analogWrite(ENA, 0);
    digitalWrite(IN1,0);
    digitalWrite(IN2, 0);
}

void motorBFrente(int vel){
    analogWrite(ENB, vel);
    digitalWrite(IN3,1);
    digitalWrite(IN4, 0);
}

void motorBRetroceso(int vel){
    analogWrite(ENB, vel);
    digitalWrite(IN3,0);
    digitalWrite(IN4, 1);
}

void motorBParar(){
    analogWrite(ENB, 0);
    digitalWrite(IN3,0);
    digitalWrite(IN4, 0);
}
