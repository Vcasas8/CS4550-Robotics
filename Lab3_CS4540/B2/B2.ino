/*
B-2. Program 4 or 5 LED's so that they will continuously 
count in binary from 0 (0000) up to 15 (1111) 
and then back down to 0 again.
*/

int ledPins[] = {13, 11, 9, 7}; // Pins
int count = 0;
int direction = 1; // 1 for up, -1 for down

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT); //Configure LED pins
  }

}

void loop() {
  // update LEDs based on binary rep or Count
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], bitRead(count, i));
  }

  // count up or down
  count += direction;

  // reverse direction at 0 or 15
  if (count >= 15 || count <= 0) {
    direction = -direction;
  }

  delay(500);
}
