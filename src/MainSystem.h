#ifndef MAIN_SYSTEM_H
#define MAIN_SYSTEM_H

#include <Arduino.h>

// Forward declaration to avoid circular dependency
class SystemManager;

class MainSystem
{
private:
    SystemManager *systemManager;

public:
    MainSystem();
    void update();
};
#endif // MAIN_SYSTEM_H
