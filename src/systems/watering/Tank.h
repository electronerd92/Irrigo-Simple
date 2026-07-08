#pragma once
#include <Arduino.h>

class Tank
{
private:
    uint8_t lowLevelPin;
    bool hasWaterLevel;

public:
    Tank(uint8_t pin, bool hasWaterLevel);

    bool hasWater() const;
};