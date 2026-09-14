#include "Tank.h"

Tank::Tank(uint8_t lowLevelPin,
           bool hasWaterLevel,
           uint8_t filledLevelPin,
           bool filledLevel)
    : lowLevelPin(lowLevelPin),
      filledLevelPin(filledLevelPin),
      hasWaterLevel(hasWaterLevel),
      filledLevel(filledLevel)
{
    pinMode(lowLevelPin, INPUT_PULLUP);
    pinMode(filledLevelPin, INPUT_PULLUP);
}

bool Tank::hasWater() const
{
    return digitalRead(lowLevelPin) == hasWaterLevel;
}

bool Tank::isFilled() const
{
    return digitalRead(filledLevelPin) == filledLevel;
}