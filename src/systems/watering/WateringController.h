#pragma once

#include <Arduino.h>
#include "Pump.h"
#include "Tank.h"
#include "Valve.h"
#include "ValveProgram.h"
#include "utils/Timer.h"
#include "config.h"

enum class ManualState : uint8_t
{
    None,
    RunningTest,
    StoppingTest,
    FillingTank
};

class WateringController
{
private:
    Valve *valves;
    Valve &outdoorValve;
    Valve &tankFillValve;
    Valve &mainFeedValve;
    Pump &pump;
    Tank &tank;

    bool automaticEnabled{true};

    ManualState manualState{ManualState::None};
    uint8_t testValve{255};
    uint32_t testEndTime{0};
    uint32_t fillStartTime{0};
    uint32_t lastFillDuration{0};

    ValveProgram programs[VALVE_COUNT];

    uint8_t activeValve{255};

    enum class State : uint8_t
    {
        Idle,
        Opening_WaitPump,
        Closing_StopPump,
        Opening_WaitMainFeed,
        Closing_StopMainFeed
    };

    State state{State::Idle};
    Timer delayTimer;

public:
    WateringController(Valve *valves,
                       Valve &outdoorValve,
                       Valve &tankFillValve,
                       Valve &mainFeedValve,
                       Pump &pump,
                       Tank &tank);

    void update(uint32_t now);

    ValveProgram &getProgram(uint8_t i);
    void updateProgram(uint8_t i, const ValveProgram &, uint32_t now);

    bool startTest(uint8_t valve, uint32_t duration, uint32_t now);
    void stopTest();
    uint32_t getRemainingTestTime(uint32_t now);
    bool isTesting();
    bool startFillTank(uint32_t now);
    void stopFillTank(uint32_t now);
    bool isFillingTank();
    uint32_t getTankFillElapsedTime(uint32_t now);
    uint32_t getLastTankFillDuration() const;
    bool isTankFilled() const;
    bool isTankEmpty() const;
    void setAutomaticEnabled(bool enabled);
    bool isWatering();
    bool isAutomaticEnabled() const;
    uint8_t getActiveValve() const;

private:
    void updateNextStart(uint8_t i, uint32_t now);

    bool canStart(uint8_t i, uint32_t now);
    bool shouldStop(uint8_t i, uint32_t now);

    void startValve(uint8_t i);
    void stopValve();
};