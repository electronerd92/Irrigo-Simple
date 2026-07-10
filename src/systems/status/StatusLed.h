#pragma once
#include <Arduino.h>

#include "services/SystemStatusCode.h"
#include "utils/Timer.h"

class StatusLed
{
private:
    enum class Color : uint8_t
    {
        Off,
        Green,
        Yellow,
        Red
    };

    struct Pattern
    {
        Color color;
        uint32_t blinkPeriodMs;
    };

private:
    uint8_t redPin;
    uint8_t greenPin;
    uint8_t bluePin;

    SystemStatusCode currentStatus{SystemStatusCode::Ok};

    uint32_t currentPeriod{2000};

    bool ledOn{true};

    Timer blinkTimer;

private:
    Pattern getPattern(SystemStatusCode status);

    void setColor(Color color);

public:
    StatusLed(uint8_t redPin,
              uint8_t greenPin,
              uint8_t bluePin);

    void update(SystemStatusCode status);
};