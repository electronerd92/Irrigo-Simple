#ifndef MAIN_SYSTEM_H
#define MAIN_SYSTEM_H

#include <Arduino.h>
#include "RTClib.h"
#include "menu/MenuSystem.h"

// Forward declaration to avoid circular dependency
class SystemManager;

class MainSystem
{
private:
    RTC_DS3231 rtc;
    SystemManager *sysManager;
    MenuSystem *menuSys;

public:
    MainSystem();
    void update();
    RTC_DS3231 *getRTC();
};
#endif // MAIN_SYSTEM_H
