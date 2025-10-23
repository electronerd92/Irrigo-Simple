#include "Timer.h"

Timer::Timer(uint32_t intervalMilliseconds)
    : interval(intervalMilliseconds), startTime(0)
{
}

// Start or restart the timer
void Timer::start()
{
    startTime = millis();
}

// Check if the timer has timed out
bool Timer::timeout() const
{
    return (millis() - startTime) >= interval;
}

// Update the timer interval with an option to restart
void Timer::updateInterval(uint32_t newInterval, bool restart)
{
    interval = newInterval;
    if (restart)
    {
        start();
    }
}