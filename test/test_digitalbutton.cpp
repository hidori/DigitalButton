// test_digitalbutton.cpp

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

#include <gtest/gtest.h>

#include "Arduino.h"

unsigned long ArduinoMock::currentTime = 0;
MockPin ArduinoMock::pins[20] = {};

#include "../src/DigitalButton.h"

class DigitalButtonTest : public ::testing::Test {
 protected:
  void SetUp() override {
    ArduinoMock::reset();
  }
};

TEST_F(DigitalButtonTest, ConstructorAndBegin) {
  DigitalButton button(2, true);
  button.begin();

  EXPECT_EQ(ArduinoMock::pins[2].mode, INPUT_PULLUP);
  EXPECT_FALSE(button.isPressed());
}

TEST_F(DigitalButtonTest, ConstructorWithoutPullup) {
  DigitalButton button(3, false);
  button.begin();

  EXPECT_EQ(ArduinoMock::pins[3].mode, INPUT);
  EXPECT_FALSE(button.isPressed());
}

TEST_F(DigitalButtonTest, ButtonPress) {
  DigitalButton button(2, true);
  button.begin();

  ArduinoMock::pins[2].value = LOW;
  ArduinoMock::currentTime = 0;
  button.update();

  ArduinoMock::currentTime = 30;
  button.update();

  EXPECT_TRUE(button.isPressed());
  EXPECT_FALSE(button.isClicked());
  EXPECT_FALSE(button.isLongPressed());
}

TEST_F(DigitalButtonTest, ButtonClick) {
  DigitalButton button(2, true);
  button.begin();

  ArduinoMock::pins[2].value = LOW;
  ArduinoMock::currentTime = 0;
  button.update();

  ArduinoMock::currentTime = 30;
  button.update();
  EXPECT_TRUE(button.isPressed());

  ArduinoMock::pins[2].value = HIGH;
  ArduinoMock::currentTime = 100;
  button.update();

  ArduinoMock::currentTime = 130;
  button.update();

  EXPECT_FALSE(button.isPressed());
  EXPECT_TRUE(button.isClicked());
  EXPECT_FALSE(button.isLongPressed());
}

TEST_F(DigitalButtonTest, ButtonLongPress) {
  DigitalButton button(2, true, 20, 1000);
  button.begin();

  ArduinoMock::pins[2].value = LOW;
  ArduinoMock::currentTime = 0;
  button.update();

  ArduinoMock::currentTime = 30;
  button.update();
  EXPECT_TRUE(button.isPressed());

  ArduinoMock::pins[2].value = HIGH;
  ArduinoMock::currentTime = 1100;
  button.update();

  ArduinoMock::currentTime = 1130;
  button.update();

  EXPECT_FALSE(button.isPressed());
  EXPECT_FALSE(button.isClicked());
  EXPECT_TRUE(button.isLongPressed());
}

TEST_F(DigitalButtonTest, Debounce) {
  DigitalButton button(2, true, 50);
  button.begin();

  ArduinoMock::pins[2].value = LOW;
  ArduinoMock::currentTime = 0;
  button.update();
  EXPECT_FALSE(button.isPressed());

  ArduinoMock::currentTime = 30;
  button.update();
  EXPECT_FALSE(button.isPressed());

  ArduinoMock::currentTime = 60;
  button.update();
  EXPECT_TRUE(button.isPressed());
}

TEST_F(DigitalButtonTest, MultipleClicks) {
  DigitalButton button(2, true);
  button.begin();

  ArduinoMock::pins[2].value = LOW;
  ArduinoMock::currentTime = 0;
  button.update();

  ArduinoMock::currentTime = 30;
  button.update();

  ArduinoMock::pins[2].value = HIGH;
  ArduinoMock::currentTime = 100;
  button.update();

  ArduinoMock::currentTime = 130;
  button.update();
  EXPECT_TRUE(button.isClicked());

  ArduinoMock::currentTime = 200;
  button.update();
  EXPECT_FALSE(button.isClicked());

  ArduinoMock::pins[2].value = LOW;
  ArduinoMock::currentTime = 300;
  button.update();

  ArduinoMock::currentTime = 330;
  button.update();

  ArduinoMock::pins[2].value = HIGH;
  ArduinoMock::currentTime = 400;
  button.update();

  ArduinoMock::currentTime = 430;
  button.update();
  EXPECT_TRUE(button.isClicked());
}

TEST_F(DigitalButtonTest, CustomDebounceAndLongPressDelay) {
  DigitalButton button(2, true, 100, 2000);
  button.begin();

  ArduinoMock::pins[2].value = LOW;
  ArduinoMock::currentTime = 0;
  button.update();

  ArduinoMock::currentTime = 50;
  button.update();
  EXPECT_FALSE(button.isPressed());

  ArduinoMock::currentTime = 110;
  button.update();
  EXPECT_TRUE(button.isPressed());

  ArduinoMock::pins[2].value = HIGH;
  ArduinoMock::currentTime = 2200;
  button.update();

  ArduinoMock::currentTime = 2310;
  button.update();

  EXPECT_TRUE(button.isLongPressed());
  EXPECT_FALSE(button.isClicked());
}
