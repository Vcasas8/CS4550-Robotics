#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Long multi-line message
const char* lines[] = {
  "A long time ago",
  "in a galaxy",
  "far, far away....",
  "",
  "It is a period",
  "of embedded",
  "systems learning.",
  "",
  "Students have",
  "been building",
  "circuits with",
  "buttons, LEDs,",
  "sensors, and",
  "displays.",
  "",
  "Using Arduino,",
  "they battle",
  "wiring bugs and",
  "logic errors",
  "to complete",
  "their lab work.",
  "",
  "The mission:",
  "make it work."
};

const int numLines = sizeof(lines) / sizeof(lines[0]);
const int textSize = 1;
const int lineHeight = 8;   // good for text size 1

int yOffset = SCREEN_HEIGHT;  // start below screen

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
  display.setTextSize(textSize);
  display.setTextColor(SSD1306_WHITE);

  // Draw all lines with vertical offset
  for (int i = 0; i < numLines; i++) {
    int y = yOffset + (i * lineHeight);

    // only draw if line is on or near the screen
    if (y > -lineHeight && y < SCREEN_HEIGHT) {
      display.setCursor(0, y);
      display.println(lines[i]);
    }
  }

  display.display();

  yOffset--;

  // reset once all text has scrolled off the top
  if (yOffset < -(numLines * lineHeight)) {
    yOffset = SCREEN_HEIGHT;
  }

  delay(60);
}