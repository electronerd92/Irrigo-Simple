#pragma once

#include <Arduino.h>

class IBlinker
{
public:
    virtual void update() = 0;
    virtual bool getIsBlinking() const = 0;
    virtual void startBlinking(const char *word, uint8_t c, uint8_t r) = 0;
    virtual void stopBlinking() = 0;
};