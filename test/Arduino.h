// Arduino.h

#ifndef _ARDUINO_H_
#define _ARDUINO_H_

// MIT License
//
// Copyright (c) 2025 Hiroaki SHIBUKI a.k.a. hidori
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <stddef.h>
#include <stdint.h>

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define LOW 0x0
#define HIGH 0x1

struct MockPin {
  uint8_t mode;
  uint8_t value;
};

class ArduinoMock {
 public:
  static unsigned long currentTime;
  static MockPin pins[20];

  static void reset() {
    currentTime = 0;
    for (int i = 0; i < 20; i++) {
      pins[i].mode = INPUT;
      pins[i].value = LOW;
    }
  }
};

inline void pinMode(uint8_t pin, uint8_t mode) {
  ArduinoMock::pins[pin].mode = mode;
}

inline uint8_t digitalRead(uint8_t pin) {
  return ArduinoMock::pins[pin].value;
}

inline void digitalWrite(uint8_t pin, uint8_t value) {
  ArduinoMock::pins[pin].value = value;
}

inline unsigned long millis() {
  return ArduinoMock::currentTime;
}

inline void delay(unsigned long ms) {
  ArduinoMock::currentTime += ms;
}

#endif  // _ARDUINO_H_
