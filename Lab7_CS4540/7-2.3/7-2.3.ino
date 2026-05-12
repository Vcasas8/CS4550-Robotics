#include <Wire.h>

// MPU6050 I2C address
const int MPU_addr = 0x68;

// Raw sensor values
int16_t AcX, AcY, AcZ;
int16_t GyX, GyY, GyZ;
int16_t Tmp;

// ---- OPTIONAL SMOOTHING ----
const int numReadings = 10;
int smoothX[numReadings];
int smoothY[numReadings];
int smoothZ[numReadings];
int indexX = 0, indexY = 0, indexZ = 0;
long totalX = 0, totalY = 0, totalZ = 0;

// Function to smooth a single axis
int smoothAxis(int rawValue, int readings[], long &total, int &index) {
  total -= readings[index];
  readings[index] = rawValue;
  total += readings[index];
  index = (index + 1) % numReadings;
  return total / numReadings;
}

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);      // Power management register
  Wire.write(0);         // Wake up MPU6050
  Wire.endTransmission(true);

  Serial.begin(9600);

  // Initialize smoothing arrays
  for (int i = 0; i < numReadings; i++) {
    smoothX[i] = 0;
    smoothY[i] = 0;
    smoothZ[i] = 0;
  }
}

void loop() {

  // Request accelerometer, temperature, and gyro data
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // Starting register for ACCEL_XOUT_H
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);

  // Read raw values
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();

  // ---- APPLY SMOOTHING ----
  float Ax = smoothAxis(AcX, smoothX, totalX, indexX);
  float Ay = smoothAxis(AcY, smoothY, totalY, indexY);
  float Az = smoothAxis(AcZ, smoothZ, totalZ, indexZ);

  // ---- ANGLE CALCULATIONS ----
  float pitch = atan2(Ay, Az) * 180.0 / PI;  
  float roll  = atan2(-Ax, sqrt(Ay * Ay + Az * Az)) * 180.0 / PI;
  float zAngle = atan2(Az, sqrt(Ax * Ax + Ay * Ay)) * 180.0 / PI;

  // ---- OUTPUT ----
  Serial.print("Pitch = ");
  Serial.print(pitch);

  Serial.print(" | Roll = ");
  Serial.print(roll);

  Serial.print(" | Z Angle = ");
  Serial.print(zAngle);

  Serial.print(" | Temp(C) = ");
  Serial.print(Tmp / 340.0 + 36.53);

  Serial.print(" | Raw AcX = ");
  Serial.print(AcX);

  Serial.print(" | Raw AcY = ");
  Serial.print(AcY);

  Serial.print(" | Raw AcZ = ");
  Serial.println(AcZ);

  delay(50);
}