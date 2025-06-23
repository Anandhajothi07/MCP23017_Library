#include "CustomMCP23017.h"

CustomMCP23017::CustomMCP23017(uint8_t i2cAddr) {
    _i2cAddr = i2cAddr;
    _wire = nullptr;
}

bool CustomMCP23017::begin(TwoWire* wire, uint8_t sda, uint8_t scl, uint32_t frequency) {
    _wire = wire;
    _wire->begin(sda, scl, frequency);
    
    // Test communication
    _wire->beginTransmission(_i2cAddr);
    if (_wire->endTransmission() != 0) {
        return false;
    }
    
    // Configure IOCON register for optimal operation
    // BANK=0, MIRROR=0, SEQOP=1 (disable sequential operation)
    writeRegister(MCP23017_IOCON, 0x20);
    
    // Set all pins as inputs by default (reset state)
    writeRegister(MCP23017_IODIRA, 0xFF);
    writeRegister(MCP23017_IODIRB, 0xFF);
    
    return true;
}

bool CustomMCP23017::begin(TwoWire& wire, uint8_t sda, uint8_t scl, uint32_t frequency) {
    return begin(&wire, sda, scl, frequency);
}

void CustomMCP23017::pinMode(uint8_t pin, uint8_t mode) {
    if (pin > 15) return;
    
    uint8_t iodir_reg = (pin < 8) ? MCP23017_IODIRA : MCP23017_IODIRB;
    uint8_t bit = _pinToBit(pin);
    
    _updateRegisterBit(iodir_reg, bit, mode);
}

void CustomMCP23017::digitalWrite(uint8_t pin, uint8_t value) {
    if (pin > 15) return;
    
    uint8_t gpio_reg = (pin < 8) ? MCP23017_GPIOA : MCP23017_GPIOB;
    uint8_t bit = _pinToBit(pin);
    
    _updateRegisterBit(gpio_reg, bit, value);
}

uint8_t CustomMCP23017::digitalRead(uint8_t pin) {
    if (pin > 15) return 0;
    
    uint8_t gpio_reg = (pin < 8) ? MCP23017_GPIOA : MCP23017_GPIOB;
    uint8_t bit = _pinToBit(pin);
    
    uint8_t regValue = readRegister(gpio_reg);
    return (regValue >> bit) & 0x01;
}

void CustomMCP23017::writePortA(uint8_t value) {
    writeRegister(MCP23017_GPIOA, value);
}

void CustomMCP23017::writePortB(uint8_t value) {
    writeRegister(MCP23017_GPIOB, value);
}

uint8_t CustomMCP23017::readPortA() {
    return readRegister(MCP23017_GPIOA);
}

uint8_t CustomMCP23017::readPortB() {
    return readRegister(MCP23017_GPIOB);
}

void CustomMCP23017::pullUp(uint8_t pin, uint8_t value) {
    if (pin > 15) return;
    
    uint8_t gppu_reg = (pin < 8) ? MCP23017_GPPUA : MCP23017_GPPUB;
    uint8_t bit = _pinToBit(pin);
    
    _updateRegisterBit(gppu_reg, bit, value);
}

void CustomMCP23017::setIOCON(uint8_t config) {
    writeRegister(MCP23017_IOCON, config);
}

void CustomMCP23017::writeRegister(uint8_t reg, uint8_t value) {
    if (_wire == nullptr) return;
    
    _wire->beginTransmission(_i2cAddr);
    _wire->write(reg);
    _wire->write(value);
    _wire->endTransmission();
}

uint8_t CustomMCP23017::readRegister(uint8_t reg) {
    if (_wire == nullptr) return 0;
    
    _wire->beginTransmission(_i2cAddr);
    _wire->write(reg);
    _wire->endTransmission();
    
    _wire->requestFrom(_i2cAddr, (uint8_t)1);
    if (_wire->available()) {
        return _wire->read();
    }
    return 0;
}

uint8_t CustomMCP23017::_pinToPort(uint8_t pin) {
    return (pin < 8) ? 0 : 1;
}

uint8_t CustomMCP23017::_pinToBit(uint8_t pin) {
    return pin % 8;
}

void CustomMCP23017::_updateRegisterBit(uint8_t reg, uint8_t bit, uint8_t value) {
    uint8_t regValue = readRegister(reg);
    
    if (value) {
        regValue |= (1 << bit);
    } else {
        regValue &= ~(1 << bit);
    }
    
    writeRegister(reg, regValue);
}
