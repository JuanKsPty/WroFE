#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include "I2Cdev.h"
#include "MPU6050.h"

#define XSHUT1 2
#define XSHUT2 3

Adafruit_VL53L0X sensor1 = Adafruit_VL53L0X();
Adafruit_VL53L0X sensor2 = Adafruit_VL53L0X();
MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
  }

  // Inicializa los pines XSHUT
  pinMode(XSHUT1, OUTPUT);
  pinMode(XSHUT2, OUTPUT);

  // Desactiva ambos sensores
  digitalWrite(XSHUT1, LOW);
  digitalWrite(XSHUT2, LOW);
  delay(10);

  // Activa el primer sensor
  digitalWrite(XSHUT1, HIGH);
  delay(10);

  // Inicializa el primer sensor
  if (!sensor1.begin()) {
    Serial.println("Failed to boot first VL53L0X");
    while (1);
  }

  // Cambia la dirección I2C del primer sensor
  sensor1.setAddress(0x30);

  // Activa el segundo sensor
  digitalWrite(XSHUT2, HIGH);
  delay(10);

  // Inicializa el segundo sensor
  if (!sensor2.begin()) {
    Serial.println("Failed to boot second VL53L0X");
    while (1);
  }

  // Cambia la dirección I2C del segundo sensor
  sensor2.setAddress(0x31);

  // Inicializa el MPU6050
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    while (1);
  }

  Serial.println("Sensors initialized");
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure1;
  VL53L0X_RangingMeasurementData_t measure2;

  // Lee el primer sensor
  sensor1.rangingTest(&measure1, false); // pase "true" para obtener más detalles

  if (measure1.RangeStatus != 4) { // Lee correctamente
    Serial.print("Sensor 1: ");
    Serial.print(measure1.RangeMilliMeter);
    Serial.println(" mm");
  } else {
    Serial.println("Sensor 1: out of range");
  }

  // Lee el segundo sensor
  sensor2.rangingTest(&measure2, false); // pase "true" para obtener más detalles

  if (measure2.RangeStatus != 4) { // Lee correctamente
    Serial.print("Sensor 2: ");
    Serial.print(measure2.RangeMilliMeter);
    Serial.println(" mm");
  } else {
    Serial.println("Sensor 2: out of range");
  }

  // Lee los datos del MPU6050
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  Serial.print("MPU6050 Acceleration X: ");
  Serial.print(ax);
  Serial.print(" Y: ");
  Serial.print(ay);
  Serial.print(" Z: ");
  Serial.println(az);

  delay(100);
}
