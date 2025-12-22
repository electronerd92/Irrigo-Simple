#pragma once

class IWateringManager
{
public:
    virtual void update() = 0;
    virtual uint8_t getSelectedValve() = 0;
    virtual void setSelectedValve(uint8_t index) = 0;
    virtual uint8_t getValvesCount() = 0;
};