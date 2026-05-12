void setup() {
  Serial.begin(9600);
  delay(1500);

  Serial.println("-------------------");
  Serial.println("One Button Modes");
  Serial.println("-------------------");

  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, INPUT);
}

const int buttonPin = 10;
const int led1 = 4;
const int led2 = 6;

// Button tracking
int buttonState = LOW;
int lastButtonState = LOW;
unsigned long pressStartTime = 0;
unsigned long lastReleaseTime = 0;

// Timing thresholds
const unsigned long longPressTime = 1000;   // hold 1 sec for long press
const unsigned long doublePressGap = 400;   // max gap between presses

bool waitingForDouble = false;

// Modes
int mode = 0; // 0 = off, 1 = stoplight, 2 = disco

// Animation timing
unsigned long previousModeTime = 0;
int stoplightState = 0;
bool discoState = false;

void loop() {
  unsigned long currentTime = millis();
  buttonState = digitalRead(buttonPin);

  // Button pressed
  if (buttonState == HIGH && lastButtonState == LOW) {
    pressStartTime = currentTime;
  }

  // Button released
  if (buttonState == LOW && lastButtonState == HIGH) {
    unsigned long pressDuration = currentTime - pressStartTime;

    // Long press
    if (pressDuration >= longPressTime) {
      mode = 0;
      waitingForDouble = false;
      Serial.println("Long press -> ALL LIGHTS OFF");
    }
    // Short press candidate
    else {
      if (waitingForDouble && (currentTime - lastReleaseTime <= doublePressGap)) {
        mode = 2;
        waitingForDouble = false;
        Serial.println("Double press -> DISCO MODE");
      } else {
        waitingForDouble = true;
        lastReleaseTime = currentTime;
      }
    }
  }

  // If time passes and no second press comes, treat it as a single short press
  if (waitingForDouble && (currentTime - lastReleaseTime > doublePressGap)) {
    mode = 1;
    waitingForDouble = false;
    Serial.println("Short press -> STOPLIGHT MODE");
  }

  lastButtonState = buttonState;

  // Run selected LED mode
  if (mode == 0) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }
  else if (mode == 1) {
    // Stoplight mode: alternate LEDs every 1 second
    if (currentTime - previousModeTime >= 1000) {
      previousModeTime = currentTime;
      stoplightState = !stoplightState;
    }

    digitalWrite(led1, stoplightState);
    digitalWrite(led2, !stoplightState);
  }
  else if (mode == 2) {
    // Disco mode: fast flashing pattern
    if (currentTime - previousModeTime >= 150) {
      previousModeTime = currentTime;
      discoState = !discoState;
    }

    digitalWrite(led1, discoState);
    digitalWrite(led2, !discoState);
  }
}
