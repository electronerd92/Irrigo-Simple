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

public:
    SystemManager(MainSystem *mainSystem);
    void update();

    DateTime getDateTime();
};
#endif // SYSTEM_MANAGER_H