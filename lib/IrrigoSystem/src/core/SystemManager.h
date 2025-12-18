#pragma once
#include <Arduino.h>
#include "interfaces/ISystemManager.h"
#include "interfaces/IMainSystem.h"

class SystemManager : public ISystemManager
{
private:
    IMainSystem *mainSystem;
    uint8_t daysInMonth(uint16_t year, uint8_t month);

public:
    SystemManager(IMainSystem *mainSystem);
    void update() override;
    SystemState getSystemState() override;
    void setSystemState(SystemState sysState) override;

    RtcDateTime getDateTime() override;
    uint32_t getUnixTime() override;
    void incrementDay() override;
    void decreaseDay() override;
    void incrementMonth() override;
    void decreaseMonth() override;
    void incrementYear() override;
    void decreaseYear() override;
    void incrementHour() override;
    void decreaseHour() override;
    void incrementMinute() override;
    void decreaseMinute() override;
};