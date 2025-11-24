// CustomTiming - Example of custom debounce and long-press timing

#include <Arduino.h>
#include <DigitalButton.h>

// Create button with custom timing
// Parameters: pin, usePullUp, debounceDelay, longPressDelay
DigitalButton button(2, true, 50, 2000);  // 50ms debounce, 2s long-press

void setup() {
  Serial.begin(9600);
  while (!Serial && millis() < 1000);

  button.begin();

  Serial.println("Custom Timing Example");
  Serial.println("Debounce: 50ms, Long-press: 2000ms");
}

void loop() {
  button.update();

  if (button.isClicked()) {
    Serial.println("Quick click!");
  }

  if (button.isLongPressed()) {
    Serial.println("Held for 2 seconds!");
  }

  delay(10);
}
