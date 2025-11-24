// ExternalPullDown - Example using external pull-down resistor

#include <Arduino.h>
#include <DigitalButton.h>

// Using external pull-down resistor (button connects pin to VCC)
DigitalButton button(2, false);  // false = INPUT mode (no internal pull-up)

void setup() {
  Serial.begin(9600);
  while (!Serial && millis() < 1000);

  button.begin();

  Serial.println("External Pull-down Example");
  Serial.println("Button connects pin to VCC");
}

void loop() {
  button.update();

  if (button.isPressed()) {
    Serial.println("Button is pressed");
  }

  if (button.isClicked()) {
    Serial.println("Button clicked!");
  }

  delay(10);
}
