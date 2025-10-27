#ifndef MAIN_SYSTEM_H
#define MAIN_SYSTEM_H

#include <Arduino.h>
#include "interfaces/IMainSystem.h"
#include "interfaces/IRtc.h"
#include <MenuSystem.h>

// Forward declaration to avoid circular dependency
class SystemManager;

class MainSystem : public IMainSystem
{
private:
    IRtc *rtc;
    SystemManager *sysManager;
    MenuSystem *menuSys;

public:
    MainSystem();
    void update() override;
    IRtc *getRTC();
};
#endif // MAIN_SYSTEM_H
