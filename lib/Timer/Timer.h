#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer
{
private:
    uint32_t interval; // Time interval in milliseconds
    uint32_t startTime;

public:
    Timer(uint32_t intervalMilliseconds);

    // Start or restart the timer
    void start();

    // Check if the timer has timed out
    bool timeout() const;

    // Update the timer interval with an option to restart
    void updateInterval(uint32_t newInterval, bool restart = true);
};

#endif // TIMER_H