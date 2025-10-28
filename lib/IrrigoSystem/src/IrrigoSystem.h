#ifndef SYSTEM_H
#define SYSTEM_H

#include "core/MainSystem.h"
#include "core/SystemManager.h"

class IrrigoSystem
{
    MainSystem *mainSys = nullptr;

public:
    void begin() { mainSys = new MainSystem(); }
    void update() { mainSys->update(); }
};

#endif // SYSTEM_H