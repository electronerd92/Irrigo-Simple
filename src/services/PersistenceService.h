
#pragma once
#include <Arduino.h>

#include "systems/watering/WateringController.h"
#include "hardware/interfaces/IEEPROMWriter.h"
#include "hardware/interfaces/IEEPROMReader.h"

class PersistenceService
{
private:
    static constexpr uint8_t VERSION_MAJOR = 1;
    static constexpr uint8_t VERSION_MINOR = 0;

    WateringController &watering;

    IEEPROMWriter &writer;
    IEEPROMReader &reader;

public:
    PersistenceService(WateringController &ctrl,
                       IEEPROMWriter &w,
                       IEEPROMReader &r);

    bool save();
    bool load(uint32_t now);
};
