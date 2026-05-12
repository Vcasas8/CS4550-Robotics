#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define MPU 0x68
Adafruit_SSD1306 display(128, 64, &Wire);

int16_t AcX, AcY, AcZ;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void loop() {
  // Read accelerometer
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();

  // Convert to tilt angles
  float Ax = AcX;
  float Ay = AcY;
  float Az = AcZ;

  float pitch = atan2(Ay, Az) * 180.0 / PI;
  float roll  = atan2(-Ax, sqrt(Ay * Ay + Az * Az)) * 180.0 / PI;

  // Map angles to screen coordinates
  int x = map(roll, -45, 45, 10, 118);
  int y = map(pitch, -45, 45, 10, 54);

  // Clamp inside screen
  x = constrain(x, 10, 118);
  y = constrain(y, 10, 54);

  display.clearDisplay();

  // Draw center circle (20% of screen height)
  display.drawCircle(64, 32, 12, WHITE);

  // Draw bubble
  display.fillCircle(x, y, 5, WHITE);

  display.display();
  delay(20);
}