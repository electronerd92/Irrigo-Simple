#pragma once
#include "IRtc.h"

class IMainSystem
{
public:
    virtual void update() = 0;
    virtual IRtc *getRTC() = 0;
};