#pragma once
#include <Arduino.h>
#include "hardware/interfaces/IRtc.h"
#include "hardware/interfaces/IDisplay.h"
#include "hardware/interfaces/IInputDevice.h"

#include "services/DateTimeService.hpp"
#include "systems/ui/UiSystem.h"
#include "systems/watering/WateringSystem.h"

class MainSystem
{
private:
    IDisplay &display;
    // Services (non-hardware)
    DateTimeService dateTimeService;
    WateringSystem watering;
    UiSystem ui;

    void showWelcomeScreen();

public:
    MainSystem(IRtc &rtc, IDisplay &display, IInputDevice &inputDevice);
    void begin();
    void update();
};
