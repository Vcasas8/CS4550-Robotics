void setup() {
  Serial.begin(9600);
  delay(1500);

  Serial.println("-------------------");
  Serial.println("Hello Arduino Land");
  Serial.println("-------------------");

  pinMode(13, OUTPUT);   // onboard LED (still available)
  pinMode(4, OUTPUT);    // LED you are toggling
  pinMode(10, INPUT);    // switch input
}

int currentInputState = 0;
int previousInputState = 0;
int changeCount = 0;

int ledState = LOW;      // LED starts OFF

void loop() {
  currentInputState = digitalRead(10);

  // Detect change from LOW → HIGH (button press)
  if (currentInputState != previousInputState) {
    if (currentInputState == HIGH) {
      changeCount++;
      Serial.print("Button pressed   Count: ");
      Serial.println(changeCount);

      // TOGGLE LED HERE
      ledState = !ledState;      
      digitalWrite(4, ledState);
    }
    else {
      Serial.print("Button released  Count: ");
      Serial.println(changeCount);
    }

    previousInputState = currentInputState;
  }
}