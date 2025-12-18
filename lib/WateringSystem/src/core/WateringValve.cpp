#include "WateringValve.h"

WateringValve::WateringValve(uint8_t valvePin, bool out)
    : pin(valvePin),
      isOutdoor(out),
      mode(ValveMode::OFF),
      frequency(0),
      timer(0),
      nextWateringTime(0),
      startTime(0)
{
    pinMode(pin, OUTPUT);
}

bool WateringValve::getIsOutdoor() const  
{
    return isOutdoor;
}

void WateringValve::setValveMode(ValveMode newMode, uint32_t currentTime)
{
    mode = newMode;
    updateNextWateringTime(currentTime);
}

int WateringValve::getState()
{
    return digitalRead(pin);
}

void WateringValve::open(bool state)
{
    digitalWrite(pin, state);
    timer.start();
}
void WateringValve::close(bool state)
{
    digitalWrite(pin, state);
    nextWateringTime += frequency; // schedule next watering
}

void WateringValve::setFrequency(uint8_t freq, uint32_t currentTime)
{
    frequency = (uint32_t)freq * 3600UL; // Convert hours to seconds;
    updateNextWateringTime(currentTime);
}

void WateringValve::setStartTime(uint16_t start, uint32_t currentTime)
{
    startTime = (uint32_t)start * 60UL; // Convert minutes since midnight to seconds
    updateNextWateringTime(currentTime);
}

void WateringValve::setPeriod(uint32_t period)
{
    timer.updateInterval(period * 60000UL); // Convert minutes to milliseconds
}

void WateringValve::updateNextWateringTime(uint32_t currentTime)
{
    if (mode == ValveMode::OFF || frequency == 0)
    {
        nextWateringTime = 0;
        return;
    }

    const uint32_t SECONDS_IN_DAY = 86400UL; // 24 * 60 * 60

    // Add frequency to current time
    uint32_t targetTime = currentTime + frequency;

    // Find midnight of the target day
    uint32_t completeDays = targetTime / SECONDS_IN_DAY;
    uint32_t targetDayMidnight = completeDays * SECONDS_IN_DAY;

    nextWateringTime = targetDayMidnight + startTime;
}

bool WateringValve::canBeOpened(uint32_t currentTime) const
{
    if (mode == ValveMode::TIMER && currentTime >= nextWateringTime)
    {
        return true;
    }

    return false;
}

bool WateringValve::canBeClosed() const
{
    if (mode == ValveMode::TIMER)
    {
        return timer.timeout();
    }
    return true;
}