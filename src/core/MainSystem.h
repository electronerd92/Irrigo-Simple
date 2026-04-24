#pragma once
#include <Arduino.h>
#include "hardware/interfaces/IRtc.h"
#include "hardware/interfaces/IDisplay.h"
#include "hardware/RotaryEncoder.h"
#include "services/DateTimeService.hpp"

class MainSystem
{
private:
    // Services (non-hardware)
    DateTimeService dateTimeService;

    public:
    MainSystem(IRtc &rtc, IDisplay &display, RotaryEncoder &inputDevice);
    void begin();
    void update();
};
