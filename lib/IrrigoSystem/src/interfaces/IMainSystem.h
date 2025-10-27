#ifndef I_MAIN_SYSTEM_H
#define I_MAIN_SYSTEM_H

#include "IRtc.h"

class IMainSystem
{
public:
    virtual void update() = 0;
    virtual IRtc *getRTC() = 0;
};

#endif // I_MAIN_SYSTEM_H