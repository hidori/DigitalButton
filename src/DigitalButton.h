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

#ifndef __DIGITAL_BUTTON_H__
#define __DIGITAL_BUTTON_H__

#include <Arduino.h>

class DigitalButton {
 public:
  DigitalButton(uint8_t pin, bool useInputPullUp, unsigned long debounceDelay = 20, unsigned long longPressDelay = 1000);

  void begin();
  void update();

  bool isPressed();
  bool isClicked();
  bool isLongPressed();

 private:
  uint8_t pin;
  bool useInputPullUp;
  unsigned long debounceDelay;
  unsigned long longPressDelay;

  bool currentState;
  bool lastState;
  bool lastReading;
  unsigned long lastDebounceTime;
  unsigned long pressStartTime;
  bool longPressTriggered;
};

#endif  // __DIGITAL_BUTTON_H__
