#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* message = "This is a scrolling OLED display demo";
int xPos = 128;

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (true) {
    }
  }

  display.clearDisplay();
}

void loop() {
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(xPos, 20);
  display.print(message);

  display.display();

  xPos = xPos - 2;

  // Reset once the text has moved far enough left
  if (xPos < -300) {
    xPos = SCREEN_WIDTH;
  }

  delay(50);
}