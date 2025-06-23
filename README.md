# MCP23017_Library
Arduino Library for MCP23017
# CustomMCP23017 Library

A lightweight Arduino library to control the MCP23017 16-bit GPIO expander over I2C using the `Wire` library. 

Supports basic GPIO operations like pinMode, digitalWrite, digitalRead, pull-up control, and full 8-bit port control.

## 🚀 Features

- Initialize MCP23017 with custom I2C bus and address
- Control individual pins (0–15)
- Set pin direction: `INPUT` or `OUTPUT`
- Use `digitalWrite()` / `digitalRead()` on expander pins
- Control entire Port A or Port B using `writePortA/B()` and `readPortA/B()`
- Enable/disable internal pull-ups on specific pins
- Access and configure low-level registers (like IOCON)

## 📦 Installation

1. Clone this repository or download the ZIP.
2. Copy the `CustomMCP23017` folder into your Arduino `libraries` folder.
3. Restart Arduino IDE.

## 🧰 Usage

### Example: Basic Pin Control

```cpp
#include <Wire.h>
#include <CustomMCP23017.h>

CustomMCP23017 mcp(0x20); // Default I2C address

void setup() {
  Wire.begin();
  mcp.begin(&Wire);

  mcp.pinMode(0, OUTPUT);
  mcp.digitalWrite(0, HIGH);
}

void loop() {
  // Toggle pin 0
}
