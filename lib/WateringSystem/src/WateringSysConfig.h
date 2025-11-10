#pragma once
#include <Arduino.h>

struct ValvesPinout
{
    uint8_t valve1 = 1;
    uint8_t valve2 = 2;
    uint8_t valve3 = 3;
    uint8_t valve4 = 4;
    uint8_t valveOut5 = 5;
    uint8_t valveOut6 = 6;
    uint8_t valveOut7 = 7;
    uint8_t valveOut8 = 8;

    uint8_t valveMainWater = 9;
    uint8_t valveOut = 10;
    uint8_t valveTank = 11;
};

struct WateringSysConfig
{
    bool valveOn = LOW;
    bool pumpOn = LOW;
    uint8_t wateringValvesCount = 8;
    ValvesPinout valvePinout;
    uint8_t pumpPin = 30;
};