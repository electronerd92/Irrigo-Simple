#pragma once

#include <Arduino.h>
#include "Pump.h"
#include "Tank.h"
#include "Valve.h"
#include "ValveProgram.h"
#include "utils/Timer.h"
#include "config.h"

class WateringController
{
private:
    Valve *valves;
    Valve &outdoorValve;
    Pump &pump;
    Tank &tank;

    ValveProgram programs[VALVE_COUNT];

    uint8_t activeValve{255};

    enum class State : uint8_t
    {
        Idle,
        Opening_WaitPump,
        Closing_StopPump
    };

    State state{State::Idle};
    Timer delayTimer;

public:
    WateringController(Valve *valves,
                       Valve &outdoorValve,
                       Pump &pump,
                       Tank &tank);

    void update(uint32_t now);

    ValveProgram &getProgram(uint8_t i);
    void updateProgram(uint8_t i, const ValveProgram &, uint32_t now);

private:
    void updateNextStart(uint8_t i, uint32_t now);

    bool canStart(uint8_t i, uint32_t now);
    bool shouldStop(uint8_t i, uint32_t now);

    void startValve(uint8_t i);
    void stopValve();
};