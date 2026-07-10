#include "MainSystem.h"
#include "config.h"

MainSystem::MainSystem(IRtc &rtc, IDisplay &display, IInputDevice &inputDevice,
                       IEEPROMWriter &writer, IEEPROMReader &reader)
    : display(display),
      status(),
      led(LED_RED_PIN, LED_GREEN_PIN, LED_BLUE_PIN),
      dateTimeService(rtc),
      watering(),
      persistence(watering.getController(), writer, reader),
      ui(display, inputDevice, dateTimeService, persistence, watering.getController())
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
    uint32_t now = dateTimeService.unixTime();
    persistence.load(now);
    ui.begin();
}

void MainSystem::update()
{
    uint32_t now = dateTimeService.unixTime();

    updateStatus();
    watering.getController().setAutomaticEnabled(isAutomaticWateringAllowed());

    watering.update(now);
    ui.update();

    led.update(status.get());
}

void MainSystem::updateStatus()
{
    if (!watering.getTank().hasWater())
    {
        status.set(SystemStatusCode::TankEmpty);
    }
    else if (watering.getController().isTesting())
    {
        status.set(SystemStatusCode::ValveTestRunning);
    }
    else if (ui.isEditing())
    {
        status.set(SystemStatusCode::MenuEditing);
    }
    else if (watering.getController().isWatering())
    {
        status.set(SystemStatusCode::AutoWatering);
    }
    else
    {
        status.set(SystemStatusCode::Ok);
    }
}

bool MainSystem::isAutomaticWateringAllowed()
{
    if (!watering.getTank().hasWater())
        return false;

    if (watering.getController().isTesting())
        return false;

    if (ui.isEditing())
        return false;

    return true;
}