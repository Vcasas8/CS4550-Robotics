#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define MPU 0x68
Adafruit_SSD1306 display(128, 64, &Wire);

int16_t AcX, AcY, AcZ;

int cursorX = 64;
int cursorY = 32;

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

  float Ax = AcX;
  float Ay = AcY;
  float Az = AcZ;

  // Shake detection (erase screen)
  if (abs(Ax) > 20000 || abs(Ay) > 20000) {
    display.clearDisplay();
    display.display();
    delay(300);
    return;
  }

  // Tilt → movement
  int dx = map(Ax, -17000, 17000, -2, 2);
  int dy = map(Ay, -17000, 17000, -2, 2);

  cursorX += dx;
  cursorY += dy;

  cursorX = constrain(cursorX, 0, 127);
  cursorY = constrain(cursorY, 0, 63);

  // Draw pixel trail
  display.drawPixel(cursorX, cursorY, WHITE);
  display.display();

  delay(20);
}

