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
  Rojo_Frec = pulseIn(sensorSalida, LOW);
  
  digitalWrite(s2, HIGH);  //lectura color verde
  digitalWrite(s3, HIGH);
  Verde_Frec = pulseIn(sensorSalida, LOW);

  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  Azul_Frec = pulseIn(sensorSalida, LOW);
  
  int rgbValue = Rojo_Frec + Verde_Frec + Azul_Frec;
  Serial.print(rgbValue);
  //valores de la calibracion
  Serial.println();
  if (rgbValue > 420) {
    Serial.print(" . ***color**");
  }
  else {
  Serial.print(" . ***BLANCO**");
  }
}