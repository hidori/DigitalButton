# Arduino: DigitalButton - Button library with click and long-press detection

A comprehensive button handling library with debouncing, click detection, and long-press support for Arduino. Perfect for reliable button input with minimal configuration.

## Features

- Click and long-press detection with configurable timing
- Automatic debouncing (eliminates mechanical noise)
- Support for `INPUT` and `INPUT_PULLUP` modes
- Simple API with minimal setup

## Installation

### Arduino IDE Library Manager

1. Open Arduino IDE
2. Go to Sketch → Include Library → Manage Libraries
3. Search for "DigitalButton"
4. Click Install

### Manual Installation

1. Download this repository as ZIP
2. In Arduino IDE: Sketch → Include Library → Add .ZIP Library
3. Select the downloaded ZIP file

## Quick Start

```cpp
#include <DigitalButton.h>

// Create button instance (pin 2, use internal pull-up)
DigitalButton button(2, true);

void setup() {
  Serial.begin(9600);
  button.begin();  // Initialize button
}

void loop() {
  button.update();  // Update button state (must be called every loop)

  // Detect short press and release
  if (button.isClicked()) {
    Serial.println("Button clicked!");
  }

  // Detect long press (held for 1000ms by default)
  if (button.isLongPressed()) {
    Serial.println("Button long pressed!");
  }

  delay(10);
}
```

## Examples

See the `examples/` directory for complete usage examples:

- **Basic**: Simple button usage with all detection methods
- **CustomTiming**: Custom debounce and long-press timing configuration
- **ExternalPullDown**: Using external pull-down resistor instead of internal pull-up
- **MultipleButtons**: Handling multiple buttons simultaneously

## API Reference

### Constructor

#### `DigitalButton(uint8_t pin, bool useInputPullUp, unsigned long debounceDelay = 20, unsigned long longPressDelay = 1000)`

Create a new button instance.

**Parameters:**
- `pin`: Arduino pin number connected to the button
- `useInputPullUp`: `true` to enable internal pull-up resistor (button connects to GND), `false` for external pull-down (button connects to VCC)
- `debounceDelay`: Debounce time in milliseconds (default: 20ms)
- `longPressDelay`: Long-press threshold in milliseconds (default: 1000ms)

**Example:**
```cpp
// Button on pin 2, internal pull-up, 20ms debounce, 1s long-press
DigitalButton button(2, true);

// Button on pin 3, external pull-down, 50ms debounce, 2s long-press
DigitalButton button(3, false, 50, 2000);
```

### Methods

#### `void begin()`

Initialize the button pin and internal state. Must be called in `setup()`.

**Example:**
```cpp
void setup() {
  button.begin();
}
```

#### `void update()`

Update button state. Must be called regularly in `loop()` to detect state changes.

**Example:**
```cpp
void loop() {
  button.update();
  // ... check button states
}
```

#### `bool isPressed()`

Check if button is currently pressed.

**Returns:** `true` if button is pressed, `false` otherwise

**Example:**
```cpp
if (button.isPressed()) {
  Serial.println("Button is currently pressed");
}
```

#### `bool isClicked()`

Check if button was clicked (pressed and released quickly, not a long-press).

**Returns:** `true` for one loop iteration after a click is detected, `false` otherwise

**Note:** This returns `true` only once per click event. You must call it in every loop iteration to catch the event.

**Example:**
```cpp
if (button.isClicked()) {
  Serial.println("Button was clicked!");
  clickCount++;
}
```

#### `bool isLongPressed()`

Check if button was long-pressed (held longer than `longPressDelay`).

**Returns:** `true` for one loop iteration after a long-press is detected, `false` otherwise

**Note:** This returns `true` only once per long-press event. You must call it in every loop iteration to catch the event.

**Example:**
```cpp
if (button.isLongPressed()) {
  Serial.println("Button was held for a long time!");
  resetSettings();
}
```

## Default Values

- **Debounce Delay**: 20 milliseconds
- **Long-press Delay**: 1000 milliseconds (1 second)

These values work well for most mechanical buttons but can be adjusted in the constructor:

```cpp
// Custom timing: 50ms debounce, 2s long-press
DigitalButton button(2, true, 50, 2000);
```

## Supported Platforms

This library is compatible with all Arduino platforms:

- Arduino UNO, Nano, Pro Mini
- Arduino Mega
- Arduino Leonardo, Pro Micro
- ATtiny 85, etc.
- And any other Arduino-compatible platform

## License

MIT License - see LICENSE file for details.

## Contributing

Pull requests and issues are welcome on GitHub.
