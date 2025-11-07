#pragma once
#include <Arduino.h>

struct LcdConfig
{
    uint8_t address = 0x27;
    uint8_t columns = 20;
    uint8_t rows = 4;
    unsigned long timeOn = 60000;
    unsigned long blinkInterval = 500;
    uint8_t blinkBufferSize = 12;
};

struct RotaryConfig
{
    uint8_t pinA = 3;
    uint8_t pinB = 2;
    uint8_t buttonPin = 4;
};

struct BlinkerConfig
{
    unsigned long blinkInterval = 500; // ms
    uint8_t bufferSize = 12;           // character buffer size
};

struct MenuConfig
{
    LcdConfig lcd;
    RotaryConfig rotary;
    BlinkerConfig blinker;
    uint8_t bufferSize = 8;
};