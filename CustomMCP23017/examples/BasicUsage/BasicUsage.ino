#include <Wire.h>
#include <CustomMCP23017.h>

CustomMCP23017 expander(0x20);

void setup() {
  Serial.begin(9600);
  expander.begin(&Wire);

  expander.pinMode(0, OUTPUT);
  expander.pinMode(1, INPUT);
  expander.pullUp(1, 1);
}

void loop() {
  expander.digitalWrite(0, HIGH);
  delay(500);
  expander.digitalWrite(0, LOW);
  delay(500);

  if (expander.digitalRead(1) == LOW) {
    Serial.println("Button Pressed!");
  }
}
