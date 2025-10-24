#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <Arduino.h>
#include <ISystemManager.h>
#include "MainSystem.h"

class SystemManager : public ISystemManager
{
private:
    MainSystem *mainSystem;
    uint8_t daysInMonth(uint16_t year, uint8_t month);

public:
    SystemManager(MainSystem *mainSystem);
    void update();

    DateTime getDateTime() override;
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
#endif // SYSTEM_MANAGER_H