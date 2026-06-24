#pragma once
#include <Arduino.h>

class IDisplay
{
public:
    virtual ~IDisplay() = default;

    virtual void begin() {}

    virtual uint8_t getColumns() const = 0;
    virtual uint8_t getRows() const = 0;

    virtual void clear() = 0;
    virtual void clearChar(uint8_t col, uint8_t row) = 0;

    virtual void setCursor(uint8_t col, uint8_t row) = 0;

    virtual void write(char c) = 0;
    virtual void print(const char *str) = 0;
    virtual void print(const __FlashStringHelper *str) = 0;

    virtual void power(bool on) = 0;
};
