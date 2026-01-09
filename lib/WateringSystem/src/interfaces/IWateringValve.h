#pragma once
#include <Arduino.h>

enum class ValveMode : uint8_t
{
    OFF,
    TIMER,
    COUNT // used to get the number of ValveMode by Menu
};

// In ValvesMenu.h or utility header
inline static const char *valveModeToString(ValveMode mode)
{
    switch (mode)
    {
    case ValveMode::OFF:
        return "OFF";
    case ValveMode::TIMER:
        return "TIMER";
    default:
        return "?";
    }
}

class IWateringValve
{
public:
    virtual ValveMode getMode() const = 0;
    virtual uint32_t getFrequency() const = 0;
    virtual void setSelectedValveMode(ValveMode newMode, uint32_t currentTime) = 0;
    virtual bool getIsOutdoor() const = 0;
    virtual int getState() = 0;
    virtual void open(bool state) = 0;
    virtual void close(bool state) = 0;
    virtual void setFrequency(uint32_t freq, uint32_t currentTime) = 0;
    virtual void setStartTime(uint16_t start, uint32_t currentTime) = 0;
    virtual void setPeriod(uint32_t period) = 0;
    virtual bool canBeOpened(uint32_t currentTime) const = 0;
    virtual bool canBeClosed() const = 0;
};