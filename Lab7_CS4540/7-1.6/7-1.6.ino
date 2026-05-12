#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int trigPin = 6;
int echoPin = 7;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (true) {
    }
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  // Send trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time
  long duration = pulseIn(echoPin, HIGH);

  // Convert to distance in cm
  float distanceCm = duration * 0.034 / 2.0;

  // Serial output for debugging
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  // OLED display
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Small label
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Distance");

  // Large bold-style number
  display.setTextSize(4);
  display.setCursor(10, 20);
  display.print((int)distanceCm);

  // Unit
  display.setTextSize(2);
  display.setCursor(95, 32);
  display.print("cm");

  display.display();

  delay(200);
}