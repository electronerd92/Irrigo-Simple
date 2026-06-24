#include "MainSystem.h"
#include "config.h"

MainSystem::MainSystem(IRtc &rtc, IDisplay &display, IInputDevice &inputDevice)
    : display(display),
      dateTimeService(rtc),
      watering(),
      ui(display, inputDevice, dateTimeService, watering.getController())
{
}

void MainSystem::showWelcomeScreen()
{
    display.clear();

    // Row 1 (center): "Irrigo v1.0.0" = 13 chars → col 3
    display.setCursor(3, 1);
    display.print(PROJECT_NAME " v" PROJECT_VERSION);

    // Row 2 (center): "01/01/2026" = 10 chars → col 5
    display.setCursor(5, 2);
    display.print(RELEASE_DATE);

    delay(2000);
    display.clear();
}

void MainSystem::begin()
{
    showWelcomeScreen();
    ui.begin();
}

void MainSystem::update()
{
    uint32_t now = dateTimeService.unixTime();
    watering.update(now);

    ui.update();
}
