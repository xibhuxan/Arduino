const byte led=13; 
const byte ntc=A0; 

int medida=0; 
int nivel=500;

void monitoriza(){
    Serial.println(medida);
    delay(10);
} 

void setup()
{
	pinMode(led,OUTPUT);
    pinMode(ntc, INPUT);
    Serial.begin(9600); 
}

void loop()
{
    medida=analogRead(ntc); 
    monitoriza();

    if(medida>nivel){
        digitalWrite(led,HIGH);
    } else{
        digitalWrite(led,LOW); 
    } 
}
