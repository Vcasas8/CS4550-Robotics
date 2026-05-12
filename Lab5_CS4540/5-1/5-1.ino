void setup() {
  Serial.begin(9600);
  delay(1500);

  Serial.println("-------------------");
  Serial.println("Hello Arduino Land");
  Serial.println("-------------------");

  pinMode(4, OUTPUT);   // LED reacts to button
  pinMode(6, OUTPUT);   // Second LED reacts to button
  pinMode(10, INPUT);   // Button
}

int currentInputState = 0;
int previousInputState = 0;
int changeCount = 0;

unsigned long previousBlinkTime = 0;
bool blinkState = false;

void loop() {

  // --- LED on pin 13 blinking every 1 second ---
  unsigned long currentTime = millis();

  if (currentTime - previousBlinkTime >= 1000) {  // 1 second interval
    previousBlinkTime = currentTime;
    blinkState = !blinkState;
    digitalWrite(4, blinkState);  // Toggle LED
  }


  // --- Button and instant LED reaction ---
  currentInputState = digitalRead(10);

  if (currentInputState != previousInputState) {
    changeCount++;

    if (currentInputState == HIGH) {
      Serial.print("Button pressed   Count: ");
      Serial.println(changeCount);
    } else {
      Serial.print("Button released  Count: ");
      Serial.println(changeCount);
    }

    // Both LEDs respond immediately to button state
    digitalWrite(6, currentInputState);

    previousInputState = currentInputState;
  }
}