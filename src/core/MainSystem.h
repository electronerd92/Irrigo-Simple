#pragma once
#include <Arduino.h>
#include "hardware/interfaces/IRtc.h"
#include "hardware/interfaces/IDisplay.h"
#include "hardware/interfaces/IInputDevice.h"

#include "services/DateTimeService.hpp"
#include "systems/ui/UiSystem.h"

class MainSystem
{
private:
    // Services (non-hardware)
    DateTimeService dateTimeService;
    UiSystem ui;

public:
    MainSystem(IRtc &rtc, IDisplay &display, IInputDevice &inputDevice);
    void begin();
    void update();
};
