const int ledRedPin = 13;   // Pin del LED rojo
const int ledGreenPin = 12; // Pin del LED verde

void setup() {
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char received = Serial.read();
    
    if (received == 'R') {
      digitalWrite(ledRedPin, HIGH);
      digitalWrite(ledGreenPin, LOW);
    }
    else if (received == 'G') {
      digitalWrite(ledRedPin, LOW);
      digitalWrite(ledGreenPin, HIGH);
    }
  }
}
