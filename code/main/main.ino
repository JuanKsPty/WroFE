const int enA = 2;
const int in1 = 3;
const int in2 = 4;
int redled = 32;     // initialize digital pin 5.
int yellowled = 31;  // initialize digital pin 4.
int greenled = 30;
const int buttonPin = 11;  // button
float yawPitRoll[3];
float gyroValues[3];
float accelValues[3];
int numberOfLineRight = 1;
int numberOfLineLeft = 1;

#include <Servo.h>
#include "Simple_MPU6050.h"
#define MPU6050_DEFAULT_ADDRESS 0x68  // address pin low (GND), default for InvenSense evaluation board

Simple_MPU6050 mpu;
Servo servoMotor;

void Print_Values(int16_t *gyro, int16_t *accel, int32_t *quat) {
  Quaternion q;
  VectorFloat gravity;
  float ypr[3] = { 0, 0, 0 };
  float xyz[3] = { 0, 0, 0 };
  mpu.GetQuaternion(&q, quat);
  mpu.GetGravity(&gravity, &q);
  mpu.GetYawPitchRoll(ypr, &q, &gravity);
  mpu.ConvertToDegrees(ypr, xyz);
  yawPitRoll[0] = xyz[0];
  yawPitRoll[1] = xyz[2];
  yawPitRoll[2] = xyz[1];
  gyroValues[0] = gyro[0];
  gyroValues[1] = gyro[1];
  gyroValues[2] = gyro[2];
  accelValues[0] = accel[0];
  accelValues[2] = accel[1];
  accelValues[3] = accel[2];
}

void ledRed() {
  digitalWrite(yellowled, LOW);  // turn off yellow LED
  digitalWrite(greenled, LOW);   // turn off green LED
  digitalWrite(redled, HIGH);    // turn on red LED
}
void ledGreen() {
  digitalWrite(redled, LOW);     // turn on red LED
  digitalWrite(yellowled, LOW);  // turn off yellow LED
  digitalWrite(greenled, HIGH);  // turn off green LED
}
void ledYellow() {
  digitalWrite(redled, LOW);      // turn on red LED
  digitalWrite(greenled, LOW);    // turn off green LED
  digitalWrite(yellowled, HIGH);  // turn off yellow LED
}
void ledOff() {
  digitalWrite(redled, LOW);     // turn on red LED
  digitalWrite(greenled, LOW);   // turn off green LED
  digitalWrite(yellowled, LOW);  // turn off yellow LED
}
void motorForward(int pwm_enA) {
  analogWrite(enA, pwm_enA);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}
void motorBackward(int pwm_enA) {
  analogWrite(enA, pwm_enA);
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
}
// This function lets you control speed of the motors
void motorOff() {
  // Turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(enA, LOW);
}

void left() {
  servoMotor.write(55);  // turn off yellow LED
}
void right() {
  servoMotor.write(125);  // turn off yellow LED
}
void straight() {
  servoMotor.write(100);  // turn off yellow LED
}


void rotateRight() {
  right();
  motorForward(200);
  switch (numberOfLineRight) {
    case 1:
      while (yawPitRoll[0] < 88) {
      Serial.print("case1");
        mpu.dmp_read_fifo(false);
        Serial.println();
        Serial.print(yawPitRoll[0]);
      }
      break;
    case 2:
      while (yawPitRoll[0] < 175) {
      Serial.print("case2");
        mpu.dmp_read_fifo(false);
        Serial.println();
        Serial.print(yawPitRoll[0]);
      }
      break;
    case 3:
      if (yawPitRoll[0] > 0) {
        Serial.println("cambia");
        yawPitRoll[0] = yawPitRoll[0] * -1;
      }
      while (yawPitRoll[0] < -95) {
        Serial.print("case 3");
        mpu.dmp_read_fifo(false);
        Serial.println();
        Serial.print(yawPitRoll[0]);
      }
      break;
    case 4:
      while (yawPitRoll[0] < 0) {
        Serial.print("Case4");
        mpu.dmp_read_fifo(false);
        Serial.println();
        Serial.print(yawPitRoll[0]);
      }
      break;
  }
  motorOff();
  straight();
  if (numberOfLineRight > 4) {
    numberOfLineRight = 1;
  } else {
    numberOfLineRight += 1;
  }
}
void acomodarse() {
  switch (numberOfLineRight) {
    case 1:
      if (yawPitRoll[0] > 70 && yawPitRoll[0] < 87) {
        right();
        Serial.print("righ");
      } else if (yawPitRoll[0] > 93 && yawPitRoll[0] < 110) {
        left();
        Serial.print("izq");
      } else {
        straight();
      }
      break;
    case 2:
      if (yawPitRoll[0] > 70 && yawPitRoll[0] < 87) {
        right();
        Serial.print("righ");
      } else if (yawPitRoll[0] > 93 && yawPitRoll[0] < 110) {
        left();
        Serial.print("izq");
      } else {
        straight();
      }
  }
}
void setup() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  servoMotor.attach(33);  //servo

  pinMode(redled, OUTPUT);     // set the pin with red LED as “output”
  pinMode(yellowled, OUTPUT);  // set the pin with yellow LED as “output”
  pinMode(greenled, OUTPUT);   // set the pin with green LED as “output”
  ledRed();
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
  straight();
  //while (!Serial)
  //;  // wait for Leonardo enumeration, others continue immediately
  Serial.println(F("Start:"));

  // Setup the MPU and TwoWire aka Wire library all at once
  mpu.begin();
  mpu.Set_DMP_Output_Rate_Hz(10);  // Set the DMP output rate from 200Hz to 5 Minutes.
  //mpu.Set_DMP_Output_Rate_Seconds(10);   // Set the DMP output rate in Seconds
  //mpu.Set_DMP_Output_Rate_Minutes(5);    // Set the DMP output rate in Minute
  mpu.CalibrateMPU();         // Calibrates the MPU.
  mpu.load_DMP_Image();       // Loads the DMP image into the MPU and finish configuration.
  mpu.on_FIFO(Print_Values);  // Set callback function that is triggered when FIFO Data is retrieved
  // Setup is complete!
  ledGreen();
}

void loop() {
  mpu.dmp_read_fifo(false);
  byte buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    rotateRight();
  }
}