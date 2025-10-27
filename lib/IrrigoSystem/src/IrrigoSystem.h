#ifndef SYSTEM_H
#define SYSTEM_H

#include "core/MainSystem.h"
#include "core/SystemManager.h"

class IrrigoSystem
{
private:
    MainSystem mainSys;
    SystemManager sysManager;

public:
    IrrigoSystem()
        : mainSys(),
          sysManager(&mainSys) {}

    void update() { mainSys.update(); }
};

#endif // SYSTEM_H