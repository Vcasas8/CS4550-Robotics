#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define MPU 0x68
Adafruit_SSD1306 display(128, 64, &Wire);

int16_t AcX, AcY, AcZ;

float ballX = 64, ballY = 32;
float velX = 0, velY = 0;

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

  // Convert to small acceleration force
  float ax = AcX / 20000.0;
  float ay = AcY / 20000.0;

  // Add acceleration to velocity
  velX += ax;
  velY += ay;

  // Apply friction
  velX *= 0.95;
  velY *= 0.95;

  // Update ball position
  ballX += velX;
  ballY += velY;

  // Bounce off walls
  if (ballX < 3 || ballX > 125) velX = -velX * 0.8;
  if (ballY < 3 || ballY > 61) velY = -velY * 0.8;

  // Clamp inside screen
  ballX = constrain(ballX, 3, 125);
  ballY = constrain(ballY, 3, 61);

  display.clearDisplay();
  display.fillCircle(ballX, ballY, 3, WHITE);
  display.display();

  delay(20);
}

