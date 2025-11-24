// MultipleButtons - Example using multiple buttons simultaneously

#include <Arduino.h>
#include <DigitalButton.h>

// Create multiple button instances
DigitalButton button1(2, true);
DigitalButton button2(3, true);
DigitalButton button3(4, true);

void setup() {
  Serial.begin(9600);
  while (!Serial && millis() < 1000);

  button1.begin();
  button2.begin();
  button3.begin();

  Serial.println("Multiple Buttons Example");
  Serial.println("Button 1: Pin 2, Button 2: Pin 3, Button 3: Pin 4");
}

void loop() {
  button1.update();
  button2.update();
  button3.update();

  if (button1.isClicked()) {
    Serial.println("Button 1 clicked");
  }

  if (button2.isClicked()) {
    Serial.println("Button 2 clicked");
  }

  if (button3.isClicked()) {
    Serial.println("Button 3 clicked");
  }

  delay(10);
}
