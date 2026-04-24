#include "MainSystem.h"

MainSystem::MainSystem(IRtc &rtc, IDisplay &display, RotaryEncoder &inputDevice)
    : dateTimeService(rtc)
{
}

void MainSystem::begin()
{
    // nothing fancy
}

void MainSystem::update()
{
}
