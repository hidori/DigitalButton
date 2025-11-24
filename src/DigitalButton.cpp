// DigitalButton

/*
 * MIT License
 *
 * Copyright (c) 2025 Hiroaki SHIBUKI
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "DigitalButton.h"

DigitalButton::DigitalButton(uint8_t pin, bool useInputPullUp, unsigned long debounceDelay, unsigned long longPressDelay)
    : pin(pin),
      useInputPullUp(useInputPullUp),
      debounceDelay(debounceDelay),
      longPressDelay(longPressDelay),
      currentState(false),
      lastState(false),
      lastReading(false),
      lastDebounceTime(0),
      pressStartTime(0),
      longPressTriggered(false) {}

void DigitalButton::begin() {
  pinMode(pin, useInputPullUp ? INPUT_PULLUP : INPUT);
  currentState = false;
  lastState = currentState;
  lastReading = currentState;
  lastDebounceTime = millis();
  pressStartTime = 0;
  longPressTriggered = false;
}

void DigitalButton::update() {
  bool reading = !digitalRead(pin);
  if (reading != lastReading) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    lastState = currentState;
    currentState = reading;

    if (!lastState && currentState) {
      pressStartTime = millis();
      longPressTriggered = false;
    }

    if (lastState && !currentState) {
      if (!longPressTriggered && (millis() - pressStartTime) >= longPressDelay) {
        longPressTriggered = true;
      } else {
        longPressTriggered = false;
      }
      pressStartTime = 0;
    }
  }
  lastReading = reading;
}

bool DigitalButton::isPressed() { return currentState; }

bool DigitalButton::isClicked() { return lastState && !currentState && !longPressTriggered; }

bool DigitalButton::isLongPressed() { return lastState && !currentState && longPressTriggered; }
