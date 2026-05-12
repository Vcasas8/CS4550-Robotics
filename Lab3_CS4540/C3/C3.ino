/*
C-3. Modify that program to make it print 
the count in horizontal lines of 20 numbers 
each with a dash between them.
*/

void setup() {
   // initialize both serial ports:
   Serial.begin(9600);
   Serial.print("-------------------\n");
   Serial.print("Hello Arduino Land");
   Serial.print("-------------------\n");
   pinMode(LED_BUILTIN, OUTPUT);
}

int count = 0;
int ledState = HIGH;
String countString = String(count);

void loop() {
   if(ledState == HIGH) {
      ledState = LOW;
   } else {
      ledState = HIGH;
   }

   digitalWrite(LED_BUILTIN, ledState);
   digitalWrite(LED_BUILTIN, ledState);

   Serial.print(count);

   // Modified portion
   if ((count + 1) % 20 != 0) {
      Serial.print(" - ");
   } else {
      Serial.println();
   }

   count ++;
   delay(500);
}