#pragma once
#include <Arduino.h>

class Tank
{
private:
    uint8_t lowLevelPin;
    uint8_t filledLevelPin;
    bool hasWaterLevel;
    bool filledLevel;

public:
    Tank(uint8_t lowLevelPin,
         bool hasWaterLevel,
         uint8_t filledLevelPin,
         bool filledLevel);

    bool hasWater() const;
    bool isFilled() const;
};