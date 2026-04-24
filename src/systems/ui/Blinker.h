#pragma once

#include <Arduino.h>
#include "hardware/interfaces/IDisplay.h"
#include "utils/Timer.h"

class Blinker
{
public:
    explicit Blinker(IDisplay &display);

    void update();
    bool getIsBlinking() const;
    void startBlinking(const char *word, uint8_t col, uint8_t row);
    void stopBlinking();

private:
    static constexpr uint32_t blinkIntervalMs = 500;
    static constexpr uint8_t bufferSize = 12;

    void printWord();
    void clearWord();

private:
    IDisplay &display;
    Timer blinkTimer;

    char buffer[bufferSize];
    uint8_t wordLength{0};
    uint8_t col{0};
    uint8_t row{0};

    bool blinkState{false};
    bool isBlinking{false};
};