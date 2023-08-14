const int enA = 2;
const int in1 = 3;
const int in2 = 4;
int redled = 32;      // initialize digital pin 5.
int yellowled = 31;  // initialize digital pin 4.
int greenled = 30;   // initialize digital pin 3.

void setup() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(redled, OUTPUT);     // set the pin with red LED as “output”
  pinMode(yellowled, OUTPUT);  // set the pin with yellow LED as “output”
  pinMode(greenled, OUTPUT);   // set the pin with green LED as “output”

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void loop() {
  digitalWrite(greenled, HIGH);  //// turn on green LED
  delay(5000);                   // wait 5 seconds
  digitalWrite(greenled, LOW);   // turn off green LED
  for (int i = 0; i < 3; i++)    // blinks for 3 times
  {
    delay(500);                     // wait 0.5 seconds
    digitalWrite(yellowled, HIGH);  // turn on yellow LED
    delay(500);                     // wait 0.5 seconds
    digitalWrite(yellowled, LOW);   // turn off yellow LED
  }
  delay(500);                  // wait 0.5 seconds
  digitalWrite(redled, HIGH);  // turn on red LED
  delay(5000);                 // wait 5 seconds
  digitalWrite(redled, LOW);   // turn off red LED
  delay(100000);
  directionControl();
  delay(1000);
  speedControl();
  delay(1000);
}

// This function lets you control spinning direction of motors
void directionControl() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 255);

  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(2000);

  // Now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(2000);

  // Turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

// This function lets you control speed of the motors
void speedControl() {
  // Turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);



  // Accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++) {
    analogWrite(enA, i);

    delay(20);
  }

  // Decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i) {
    analogWrite(enA, i);

    delay(20);
  }

  // Now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}