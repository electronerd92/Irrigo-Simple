#pragma once
#include <Arduino.h>
#include "hardware/interfaces/IRtc.h"
#include "hardware/interfaces/IDisplay.h"
#include "hardware/interfaces/IInputDevice.h"
#include "hardware/interfaces/IEEPROMReader.h"
#include "hardware/interfaces/IEEPROMWriter.h"

#include "services/DateTimeService.hpp"
#include "systems/ui/UiSystem.h"
#include "systems/watering/WateringSystem.h"
#include "services/PersistenceService.h"

class MainSystem
{
private:
    IDisplay &display;

    DateTimeService dateTimeService;
    WateringSystem watering;
    PersistenceService persistence;
    UiSystem ui;

    void showWelcomeScreen();

public:
    MainSystem(IRtc &rtc, IDisplay &display, IInputDevice &inputDevice,
               IEEPROMWriter &writer, IEEPROMReader &reader);
    void begin();
    void update();
};
