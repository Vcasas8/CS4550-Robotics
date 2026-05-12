#include <Wire.h>

const int MPU_addr = 0x68;

// Raw IMU values
int16_t AcX, AcY, AcZ;

// ---------- Smoothing parameters ----------
const int numReadings = 10;

int AcX_readings[numReadings];
int AcY_readings[numReadings];
int AcZ_readings[numReadings];

int readIndex = 0;
long AcX_total = 0;
long AcY_total = 0;
long AcZ_total = 0;

int AcX_avg = 0;
int AcY_avg = 0;
int AcZ_avg = 0;
// -----------------------------------------

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Wake up MPU-6050
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Initialize smoothing arrays
  for (int i = 0; i < numReadings; i++) {
    AcX_readings[i] = 0;
    AcY_readings[i] = 0;
    AcZ_readings[i] = 0;
  }
}

void loop() {
  // Read accelerometer registers
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();

  // --------- Moving average smoothing ---------
  AcX_total -= AcX_readings[readIndex];
  AcY_total -= AcY_readings[readIndex];
  AcZ_total -= AcZ_readings[readIndex];

  AcX_readings[readIndex] = AcX;
  AcY_readings[readIndex] = AcY;
  AcZ_readings[readIndex] = AcZ;

  AcX_total += AcX_readings[readIndex];
  AcY_total += AcY_readings[readIndex];
  AcZ_total += AcZ_readings[readIndex];

  readIndex++;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  AcX_avg = AcX_total / numReadings;
  AcY_avg = AcY_total / numReadings;
  AcZ_avg = AcZ_total / numReadings;
  // --------------------------------------------

  // Print raw vs smoothed values
  Serial.print("Raw X: "); Serial.print(AcX);
  Serial.print("  Smoothed X: "); Serial.print(AcX_avg);

  Serial.print(" | Raw Y: "); Serial.print(AcY);
  Serial.print("  Smoothed Y: "); Serial.print(AcY_avg);

  Serial.print(" | Raw Z: "); Serial.print(AcZ);
  Serial.print("  Smoothed Z: "); Serial.println(AcZ_avg);

  delay(50);
}