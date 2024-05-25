/* ============================================
  Simple_MPU6050 device library code is placed under the MIT license
  Copyright (c) 2021 Homer Creutz

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  ===============================================
*/
float yawPitRoll[3];
float gyroValues[3];
float accelValues[3];
/*
 *  Use with any MPU: MPU6050, MPU6500, MPU9150, MPU9155, MPU9250 
 *  Attach the MPU to the I2C bus
 *  Power MPU According to specs of the breakout board. Generic Breakout Version Powers with 5V and has an onboard Voltage regulator.
 *  run the Sketch
 */

#include "Simple_MPU6050.h"
#define MPU6050_DEFAULT_ADDRESS 0x68  // address pin low (GND), default for InvenSense evaluation board

Simple_MPU6050 mpu;
float yaw;
//***************************************************************************************
//******************              Callback Funciton                **********************
//***************************************************************************************

// See mpu.on_FIFO(print_Values); in the Setup Loop
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


//***************************************************************************************
//******************                Setup and Loop                 **********************
//***************************************************************************************

void setup() {
  // initialize serial communication
  Serial.begin(115200);
  while (!Serial)
    ;  // wait for Leonardo enumeration, others continue immediately
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
}

void loop() {
  mpu.dmp_read_fifo(false);
  Serial.println();
  Serial.print(yawPitRoll[2]);

  // dmp_raead_fifo(false) does the following
  // Tests for Data in the FIFO Buffer
  // when it finds data it runs the mpu.on_FIFO(print_Values)
  // the print_Values function which we set run the PrintAllValues Function
  // When data is captured dmp_read_fifo will return true.
  // The print_Values function MUST have the following variables available to attach data
  // void print_Values (int16_t *gyro, int16_t *accel, int32_t *quat, uint32_t *timestamp)
  // Variables:
  // int16_t *gyro for the gyro values to be passed to it (The * tells the function it will be a pointer to the value)
  // int16_t *accel for the accel values to be passed to it
  // int32_t *quat for the quaternion values to be passed to it
  // uint32_t *timestamp which will be the micros()value at the time we retrieved the Newest value from the FIFO Buffer.
}