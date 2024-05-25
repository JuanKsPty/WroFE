#include <Servo.h>

Servo myServo;  // Crear un objeto Servo

void setup() {
  myServo.attach(23);  // Adjuntar el servo al pin 9
}

void loop() {
  // Mover el servo a 0 grados
  myServo.write(80);
  delay(1000);  // Esperar 1 segundo

  // Mover el servo a 90 grados
  myServo.write(100);
  delay(1000);  // Esperar 1 segundo

  // Mover el servo a 180 grados
  myServo.write(120);
  delay(1000);  // Esperar 1 segundo
}
