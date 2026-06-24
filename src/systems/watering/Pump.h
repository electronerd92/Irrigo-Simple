
#pragma once

#include <Arduino.h>

class Pump
{
private:
    uint8_t pin;
    bool activeLevel;

public:
    Pump(uint8_t pin, bool activeLevel);

    void start();
    void stop();
    bool isRunning() const;
};
