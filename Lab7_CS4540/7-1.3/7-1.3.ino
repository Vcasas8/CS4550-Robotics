#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int buttonPin = 6;

bool displayState = false;   // false = OFF, true = ON
int lastButtonState = LOW;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    for(;;);
  }

  display.clearDisplay();
  updateDisplay();
}

void loop() {
  int currentButtonState = digitalRead(buttonPin);

  // detect button press (LOW → HIGH)
  if (currentButtonState == HIGH && lastButtonState == LOW) {
    displayState = !displayState;  // toggle state
    updateDisplay();
    delay(200); // debounce
  }

  lastButtonState = currentButtonState;
}

void updateDisplay() {
  display.clearDisplay();

  display.setTextSize(4);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 20);

  if (displayState) {
    display.println("ON");
  } else {
    display.println("OFF");
  }

  display.display();
}