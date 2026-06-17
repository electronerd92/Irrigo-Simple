#include "MainSystem.h"

MainSystem::MainSystem(IRtc &rtc, IDisplay &display, IInputDevice &inputDevice)
    : dateTimeService(rtc),
      ui(display, inputDevice, dateTimeService)
{
}

void MainSystem::begin()
{
    ui.begin();
}

void MainSystem::update()
{
    ui.update();
}
