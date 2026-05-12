/*
1.) Wire up the switch using this "pull-down" resistor and 
"pull-up" switch input circuit configuration.
Run the program from the lecture to make the on-board 
LED to light up when the switch is being pressed and off when 
the switch is not being pressed.
(this should work the same as when you had the LED wired directly to the switch)
*/

void setup() {
  Serial.begin(9600);
  Serial.print("-------------------\n");
  Serial.print("Hello Arduino Land");
  Serial.print("-------------------\n");
  pinMode(13, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(10, INPUT);
}

int currentInputState = 0;

void loop() {
    currentInputState = digitalRead(10);
    Serial.print(currentInputState);
    Serial.print("\n");
    digitalWrite(4, currentInputState);
  }
