#ifndef BLINKER_H
#define BLINKER_H

#include <Arduino.h>
#include <interfaces/IBlinker.h>
#include <interfaces/IDisplay.h>
#include <Timer.h>
#include "MenuConfig.h"

class Blinker : public IBlinker
{
private:
    IDisplay *dispay;
    Timer blinkTimer;
    uint8_t bufferSize;
    uint8_t col;
    uint8_t row;
    bool blinkState;
    bool isBlinking;
    char *buffer;
    uint8_t wordLength;

    void printWord();
    void clearWord();

public:
    Blinker(IDisplay *dispay, const BlinkerConfig &config);
    bool getIsBlinking() const override;
    void startBlinking(const char *word, uint8_t c, uint8_t r) override;
    void stopBlinking() override;
    void update() override;
};

#endif // BLINKER_H