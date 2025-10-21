#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <Arduino.h>
#include "MainSystem.h"

// Forward declaration to avoid circular dependency
class Menu;

class SystemManager
{
private:
    MainSystem *mainSystem;
    Menu *menu;

    uint8_t daysInMonth(uint16_t year, uint8_t month);

public:
    SystemManager(MainSystem *mainSystem);
    void update();

    DateTime getDateTime();

    void incrementDay();
    void decreaseDay();
    void incrementMonth();
    void decreaseMonth();
    void incrementYear();
    void decreaseYear();
    void incrementHour();
    void decreaseHour();
    void incrementMinute();
    void decreaseMinute();
};
#endif // SYSTEM_MANAGER_H