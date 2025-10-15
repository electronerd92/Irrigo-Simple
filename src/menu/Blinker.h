#ifndef BLINKER_H
#define BLINKER_H

#include <Arduino.h>
#include "../Config.h"
#include "Timer.hpp"
#include "InputOutput/Lcd.hpp"

class Blinker
{
private:
    Lcd *lcd;
    Timer blinkTimer;
    uint8_t col;
    uint8_t row;
    bool blinkState;
    bool isBlinking;
    char buffer[LCD_BLINK_BUFFER_SIZE];
    uint8_t wordLength;

    void printWord();
    void clearWord();

public:
    Blinker(Lcd *lcd);
    bool getIsBlinking();
    void startBlinking(const char *word, uint8_t c, uint8_t r);
    void stopBlinking();
    void update();
};

#endif // BLINKER_H