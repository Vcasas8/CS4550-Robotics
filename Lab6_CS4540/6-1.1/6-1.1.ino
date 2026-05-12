// ----- LED Setup -----
const int ledPins[] = {2, 3, 4, 5, 6};
const int numLeds = 5;
int ledPosition = 2;   // start in center

// ----- Rotary Encoder Pins -----
const int encoderCLK = 8;    // A
const int encoderDT  = 10;   // B
const int encoderSW  = 12;   // Push button

// ----- Encoder State -----
int lastCLK;
bool lastSW = HIGH;

void setup() {
  Serial.begin(9600);

  // LED pins
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Encoder pins
  pinMode(encoderCLK, INPUT_PULLUP);
  pinMode(encoderDT,  INPUT_PULLUP);
  pinMode(encoderSW,  INPUT_PULLUP);

  lastCLK = digitalRead(encoderCLK);
}

void loop() {

  // ----- ROTARY ENCODER ROTATION -----
  int currentCLK = digitalRead(encoderCLK);

  if (currentCLK != lastCLK) {
    if (digitalRead(encoderDT) != currentCLK) {
      // Clockwise → move right
      if (ledPosition > 0) {
        ledPosition--;
      }
      Serial.println("RIGHT");
    } else {
      // Counter‑clockwise → move left
      if (ledPosition < numLeds - 1) {
        ledPosition++;
      }
      Serial.println("LEFT");
    }
  }

  lastCLK = currentCLK;

  // ----- ENCODER BUTTON (RESET TO CENTER) -----
  bool swState = digitalRead(encoderSW);
  if (lastSW == HIGH && swState == LOW) {
    ledPosition = 2;
    Serial.println("RESET to center");
  }
  lastSW = swState;

  // ----- DISPLAY LED -----
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], i == ledPosition ? HIGH : LOW);
  }
}