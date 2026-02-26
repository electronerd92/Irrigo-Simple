#pragma once
#include <interfaces/IWateringValve.h>

class RtcDateTime;
enum class SystemState : uint8_t;

class ISystemManager
{
public:
    virtual void update() = 0;
    virtual SystemState getSystemState() = 0;
    virtual void setSystemState(SystemState sysState) = 0;
    virtual RtcDateTime getDateTime() = 0;
    virtual uint32_t getUnixTime() = 0;
    virtual void incrementDay() = 0;
    virtual void decreaseDay() = 0;
    virtual void incrementMonth() = 0;
    virtual void decreaseMonth() = 0;
    virtual void incrementYear() = 0;
    virtual void decreaseYear() = 0;
    virtual void incrementHour() = 0;
    virtual void decreaseHour() = 0;
    virtual void incrementMinute() = 0;
    virtual void decreaseMinute() = 0;

    virtual uint8_t getSelectedValve() = 0;
    virtual void incrementSelectedValve() = 0;
    virtual void decreaseSelectedValve() = 0;

    virtual ValveMode getSelectedValveMode() = 0;
    virtual void incrementSelectedValveMode() = 0;
    virtual void decreaseSelectedValveMode() = 0;

    virtual uint32_t getSelectedValveFrequency() = 0;
    virtual void incrementSelectedValveFrequency() = 0;
    virtual void decreaseSelectedValveFrequency() = 0;

    virtual uint32_t getSelectedValveDuration() = 0;
    virtual void incrementSelectedValveDuration() = 0;
    virtual void decreaseSelectedValveDuration() = 0;

    virtual uint32_t getSelectedValveStartTime() = 0;  // Returns seconds for business logic
    virtual uint8_t getSelectedValveStartHour() = 0;   // Returns hour for UI display
    virtual uint8_t getSelectedValveStartMinute() = 0; // Returns minute for UI display
    virtual void incrementSelectedValveStartHour() = 0;
    virtual void decreaseSelectedValveStartHour() = 0;
    virtual void incrementSelectedValveStartMinute() = 0;
    virtual void decreaseSelectedValveStartMinute() = 0;
};