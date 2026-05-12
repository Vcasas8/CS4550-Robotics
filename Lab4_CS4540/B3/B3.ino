void setup() {
  Serial.begin(9600);
  delay(1500);

  Serial.println("-------------------");
  Serial.println("Hello Arduino Land");
  Serial.println("-------------------");

  pinMode(13, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(10, INPUT);
}

int currentInputState = 0;
int previousInputState = 0;
int changeCount = 0;

void loop() {
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

    digitalWrite(4, !currentInputState);
    previousInputState = currentInputState;
  }
}

