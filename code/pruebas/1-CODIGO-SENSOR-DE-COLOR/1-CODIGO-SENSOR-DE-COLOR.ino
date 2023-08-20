#define s0 24
#define s1 22
#define s2 48
#define s3 44
#define sensorSalida 52

int Rojo_Frec = 0;
int Verde_Frec = 0;  //variables
int Azul_Frec = 0;

void setup() {
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sensorSalida, INPUT);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);

  Serial.begin(9600);
}

void loop() {

  digitalWrite(s2, LOW);  //lectura de color rojo
  digitalWrite(s3, LOW);
  //delay(100);
  Rojo_Frec = pulseIn(sensorSalida, LOW);
  Serial.println();
  Serial.print(" R= ");
  Serial.print(Rojo_Frec);
  //delay(100);


  digitalWrite(s2, HIGH);  //lectura color verde
  digitalWrite(s3, HIGH);
  //delay(100);
  Verde_Frec = pulseIn(sensorSalida, LOW);
  Serial.println();
  Serial.print(" V= ");
  Serial.print(Verde_Frec);
  //delay(100);


  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  //delay(100);
  Azul_Frec = pulseIn(sensorSalida, LOW);
  Serial.println();
  Serial.print(" A= ");
  Serial.print(Azul_Frec);
  //delay(100);

  delay(1000);
  int rgbValue = Rojo_Frec + Verde_Frec + Azul_Frec;
  //valores de la calibracion
  if (rgbValue > 720) {
    Serial.print(" . ***Azul**");
  } else if (rgbValue > 470 && rgbValue < 700) {
    Serial.print(" . ***Naranja**");
  }
  else {
  Serial.print(" . ***BLANCO**");
  }
}