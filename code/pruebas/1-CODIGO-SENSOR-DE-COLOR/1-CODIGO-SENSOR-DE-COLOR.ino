#define s0 8
#define s1 9
#define s2 12
#define s3 11
#define sensorSalida 10

int Rojo_Frec = 0;
int Verde_Frec = 0; //variables
int Azul_Frec = 0;

void setup(){
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sensorSalida, INPUT);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);

  Serial.begin(9600);
}

void loop(){

  digitalWrite(s2, LOW);         //lectura de color rojo 
  digitalWrite(s3, LOW);
  delay(100);
  Rojo_Frec = pulseIn(sensorSalida, LOW);
  Serial.print(" R= "); Serial.print(Rojo_Frec);
  delay(100);


  digitalWrite(s2, HIGH);      //lectura color verde
  digitalWrite(s3, HIGH);
  delay(100);
  Verde_Frec = pulseIn(sensorSalida, LOW);
  Serial.print(" V= "); Serial.print(Verde_Frec);
  delay(100);


  digitalWrite(s2,LOW);
  digitalWrite(s3,HIGH);
  delay(100);
  Azul_Frec = pulseIn(sensorSalida, LOW);
  Serial.print(" A= "); Serial.print(Azul_Frec);  
  delay(100);


//valores de la calibracion 
if (Rojo_Frec < 130 && Verde_Frec < 120 && Azul_Frec < 95) Serial.print(" . ***BLANCO**");
if (Rojo_Frec < 110 && Verde_Frec < 130 && Azul_Frec < 120  ) Serial.print(" . ***Naranja**");
if (Rojo_Frec < 165 && Verde_Frec < 160 && Azul_Frec < 130 ) Serial.print(" . ***Azul**");

}