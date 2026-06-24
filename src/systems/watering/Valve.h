#pragma once
#include <Arduino.h>

class Valve
{
private:
    uint8_t pin;
    bool activeLevel;
    bool outdoor;

public:
    Valve(uint8_t pin, bool activeLevel, bool isOutdoor);

    void open();
    void close();
    bool isOpen() const;

    bool isOutdoor() const { return outdoor; }
};