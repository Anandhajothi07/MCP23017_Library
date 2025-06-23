#ifndef CUSTOM_MCP23017_H
#define CUSTOM_MCP23017_H

#include <Arduino.h>
#include <Wire.h>

// MCP23017 Register Addresses (BANK=0 mode)
#define MCP23017_IODIRA     0x00  // I/O Direction Register Port A
#define MCP23017_IODIRB     0x01  // I/O Direction Register Port B
#define MCP23017_IPOLA      0x02  // Input Polarity Port A
#define MCP23017_IPOLB      0x03  // Input Polarity Port B
#define MCP23017_GPINTENA   0x04  // GPIO Interrupt-on-Change Port A
#define MCP23017_GPINTENB   0x05  // GPIO Interrupt-on-Change Port B
#define MCP23017_DEFVALA    0x06  // Default Value Register Port A
#define MCP23017_DEFVALB    0x07  // Default Value Register Port B
#define MCP23017_INTCONA    0x08  // Interrupt-on-Change Control Port A
#define MCP23017_INTCONB    0x09  // Interrupt-on-Change Control Port B
#define MCP23017_IOCON      0x0A  // I/O Expander Configuration Register
#define MCP23017_GPPUA      0x0C  // GPIO Pull-Up Resistor Port A
#define MCP23017_GPPUB      0x0D  // GPIO Pull-Up Resistor Port B
#define MCP23017_INTFA      0x0E  // Interrupt Flag Register Port A
#define MCP23017_INTFB      0x0F  // Interrupt Flag Register Port B
#define MCP23017_INTCAPA    0x10  // Interrupt Captured Value Port A
#define MCP23017_INTCAPB    0x11  // Interrupt Captured Value Port B
#define MCP23017_GPIOA      0x12  // General Purpose I/O Port A
#define MCP23017_GPIOB      0x13  // General Purpose I/O Port B
#define MCP23017_OLATA      0x14  // Output Latch Port A
#define MCP23017_OLATB      0x15  // Output Latch Port B

// Pin modes
#define MCP23017_INPUT      1
#define MCP23017_OUTPUT     0

// Default I2C address
#define MCP23017_BASE_ADDR  0x20

class CustomMCP23017 {
public:
    CustomMCP23017(uint8_t i2cAddr = MCP23017_BASE_ADDR);
    
    // Initialization
    bool begin(TwoWire* wire, uint8_t sda = 21, uint8_t scl = 22, uint32_t frequency = 400000);
    bool begin(TwoWire& wire, uint8_t sda = 21, uint8_t scl = 22, uint32_t frequency = 400000);
    
    // Pin control
    void pinMode(uint8_t pin, uint8_t mode);
    void digitalWrite(uint8_t pin, uint8_t value);
    uint8_t digitalRead(uint8_t pin);
    
    // Port control (8-bit operations)
    void writePortA(uint8_t value);
    void writePortB(uint8_t value);
    uint8_t readPortA();
    uint8_t readPortB();
    
    // Pull-up control
    void pullUp(uint8_t pin, uint8_t value);
    
    // Configuration
    void setIOCON(uint8_t config);
    
    // Low-level register access
    void writeRegister(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg);
    
private:
    uint8_t _i2cAddr;
    TwoWire* _wire;
    
    uint8_t _pinToPort(uint8_t pin);
    uint8_t _pinToBit(uint8_t pin);
    void _updateRegisterBit(uint8_t reg, uint8_t bit, uint8_t value);
};

#endif
    