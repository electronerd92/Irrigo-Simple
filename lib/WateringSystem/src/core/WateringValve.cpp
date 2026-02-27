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

void WateringValve::setSelectedValveMode(ValveMode newMode, uint32_t currentTime)
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

void WateringValve::setFrequency(uint32_t freq, uint32_t currentTime)
{
    frequency = freq; // Already in seconds
    updateNextWateringTime(currentTime);
}

void WateringValve::setStartTime(uint32_t start, uint32_t currentTime)
{
    startTime = start; // Already in seconds since midnight
    updateNextWateringTime(currentTime);
}

void WateringValve::setDuration(uint32_t period)
{
    timer.updateInterval(period * 1000UL); // Convert seconds to milliseconds
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

void WateringValve::save(IEEPROMWriter &writer) const
{
    // Write only persistent data (not pin, isOutdoor - those are hardware config)
    writer.writeEnum(static_cast<uint8_t>(mode));
    writer.writeUInt32(frequency);
    writer.writeUInt32(startTime);
    writer.writeUInt32(getDuration());
    // Total: 1 + 4 + 4 + 4 = 13 bytes
}

void WateringValve::load(IEEPROMReader &reader)
{
    mode = reader.readEnum<ValveMode>();
    frequency = reader.readUInt32();
    startTime = reader.readUInt32();
    setDuration(reader.readUInt32());
}

uint16_t WateringValve::getSerializedSize() const
{
    return 1 + 4 + 4 + 4; // 13 bytes
}