// Basic - A simple example of using the DigitalButton library

#include <Arduino.h>
#include <DigitalButton.h>

// Define the button pin
#define BUTTON_PIN 2

// Create a Button instance (using pull-up resistor)
DigitalButton button(BUTTON_PIN, true);

void setup() {
  // Initialize Serial for output
  Serial.begin(9600);
  while (!Serial && millis() < 1000);

  // Initialize the button
  button.begin();
}

void loop() {
  // Update button state
  button.update();

  // Check if the button is currently pressed
  if (button.isPressed()) {
    Serial.println("Button pressed!");
  }

  // Check if the button was clicked
  if (button.isClicked()) {
    Serial.println("Button clicked!");
  }

  // Check if the button was long pressed
  if (button.isLongPressed()) {
    Serial.println("Button long pressed!");
  }

  delay(10);
}
