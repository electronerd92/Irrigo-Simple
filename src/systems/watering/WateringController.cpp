#include "WateringController.h"

WateringController::WateringController(Valve *valves,
                                       Valve &outdoorValve,
                                       Pump &pump,
                                       Tank &tank)
    : valves(valves),
      outdoorValve(outdoorValve),
      pump(pump),
      tank(tank),
      delayTimer(VALVE_PUMP_DELAY_MS)
{
    for (uint8_t i = 0; i < VALVE_COUNT; i++)
    {
        programs[i] = {}; // default OFF
    }
}

void WateringController::update(uint32_t now)
{
    switch (state)
    {
    case State::Idle:
    {
        if (activeValve != 255)
        {
            if (!tank.hasWater())
            {
                stopValve(); // emergency stop
                return;
            }

            if (shouldStop(activeValve, now))
                stopValve();
            return;
        }

        for (uint8_t i = 0; i < VALVE_COUNT; i++)
        {
            if (canStart(i, now))
            {
                startValve(i);
                break;
            }
        }
        break;
    }

    case State::Opening_WaitPump:
        if (delayTimer.timeout())
        {
            pump.start();
            programs[activeValve].startTimestamp = now;
            state = State::Idle;
        }
        break;

    case State::Closing_StopPump:
        if (delayTimer.timeout())
        {
            valves[activeValve].close();

            if (valves[activeValve].isOutdoor())
                outdoorValve.close();

            updateNextStart(activeValve, now);

            activeValve = 255;
            state = State::Idle;
        }
        break;
    }
}

bool WateringController::canStart(uint8_t i, uint32_t now)
{
    auto &p = programs[i];

    if (p.mode == ValveMode::Off)
        return false;

    if (p.mode == ValveMode::Timer)
    {
        if (!tank.hasWater())
            return false;

        return now >= p.nextStart;
    }

    return false;
}

bool WateringController::shouldStop(uint8_t i, uint32_t now)
{
    return now >= (programs[i].startTimestamp + programs[i].duration);
}

void WateringController::startValve(uint8_t i)
{
    activeValve = i;

    valves[i].open();

    if (valves[i].isOutdoor())
        outdoorValve.open();

    delayTimer.start();
    state = State::Opening_WaitPump;
}

void WateringController::stopValve()
{
    pump.stop();

    delayTimer.start();
    state = State::Closing_StopPump;
}

void WateringController::updateNextStart(uint8_t i, uint32_t now)
{
    auto &p = programs[i];

    if (p.mode == ValveMode::Off || p.frequency == 0)
    {
        p.nextStart = 0;
        return;
    }

    const uint32_t DAY = 86400UL;

    uint32_t target = now + p.frequency;

    uint32_t days = target / DAY;
    uint32_t midnight = days * DAY;

    uint32_t next = midnight + p.startTime;

    // push forward until in future
    while (next <= now)
    {
        next += p.frequency;
    }

    p.nextStart = next;
}

ValveProgram &WateringController::getProgram(uint8_t i)
{
    return programs[i];
}

void WateringController::updateProgram(uint8_t i, const ValveProgram &newProgram, uint32_t now)
{
    programs[i] = newProgram;
    updateNextStart(i, now);
}