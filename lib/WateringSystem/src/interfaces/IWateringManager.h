#pragma once
#include <interfaces/IWateringValve.h>

class IWateringManager
{
public:
    virtual void update() = 0;
    virtual uint8_t getSelectedValve() = 0;
    virtual void setSelectedValve(uint8_t index) = 0;
    virtual uint8_t getValvesCount() = 0;
    virtual ValveMode getSelectedValveMode() = 0;
    virtual void setSelectedValveMode(ValveMode newMode) = 0;
    virtual uint32_t getSelectedValveFrequency() = 0;
    virtual void setSelectedValveFrequency(uint32_t frequency) = 0;
};