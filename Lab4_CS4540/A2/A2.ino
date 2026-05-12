/*
2. Write a program that will print the status of the input pin to 
the terminal output every time the switch state changes.
Have the program count every time the switch is pressed and released. 
You should find that occasionally a single push of the switch will 
count as 3 to 10 button pushes because of "switch bounce".
*/


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

  // Only react when the switch state changes
  if (currentInputState != previousInputState) {
    changeCount++;

    Serial.print("Switch changed to: ");
    Serial.print(currentInputState);
    Serial.print("   Count: ");
    Serial.println(changeCount);

    digitalWrite(4, currentInputState);

    previousInputState = currentInputState;
  }
}