#pragma once
#include <interfaces/IWateringValve.h>

class IWateringManager
{
public:
    virtual void update() = 0;
    virtual uint8_t getSelectedValve() = 0;
    virtual void setSelectedValve(uint8_t index) = 0;
    virtual uint8_t getValvesCount() = 0;
    virtual ValveMode getValveMode() = 0;
    virtual void setValveMode(ValveMode newMode) = 0;
};