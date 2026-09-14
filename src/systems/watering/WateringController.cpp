#include "WateringController.h"

WateringController::WateringController(Valve *valves,
                                       Valve &outdoorValve,
                                       Valve &tankFillValve,
                                       Valve &mainFeedValve,
                                       Pump &pump,
                                       Tank &tank)
    : valves(valves),
      outdoorValve(outdoorValve),
      tankFillValve(tankFillValve),
      mainFeedValve(mainFeedValve),
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
        if (manualState == ManualState::FillingTank)
        {
            if (tank.isFilled())
                stopFillTank(now);
            return;
        }

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

        if (!automaticEnabled)
        {
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

    case State::Opening_WaitMainFeed:
        if (delayTimer.timeout())
        {
            mainFeedValve.open();
            state = State::Idle;
        }
        break;

    case State::Opening_WaitPump:
        if (delayTimer.timeout())
        {
            pump.start();

            if (manualState == ManualState::None)
            {
                programs[activeValve].startTimestamp = now;
            }

            state = State::Idle;
        }
        break;

    case State::Closing_StopPump:
        if (delayTimer.timeout())
        {
            valves[activeValve].close();

            if (valves[activeValve].isOutdoor())
                outdoorValve.close();

            if (manualState == ManualState::StoppingTest)
            {
                manualState = ManualState::None;
            }
            else
            {
                updateNextStart(activeValve, now);
            }

            activeValve = 255;
            state = State::Idle;
        }
        break;

    case State::Closing_StopMainFeed:
        if (delayTimer.timeout())
        {
            tankFillValve.close();

            manualState = ManualState::None;
            state = State::Idle;
        }
        break;
    }
}

void WateringController::setAutomaticEnabled(bool enabled)
{
    automaticEnabled = enabled;
}

bool WateringController::canStart(uint8_t i, uint32_t now)
{
    auto &p = programs[i];

    if (p.mode == ValveMode::Off)
        return false;

    if (p.mode == ValveMode::Timer)
        return now >= p.nextStart;

    return false;
}

bool WateringController::shouldStop(uint8_t i, uint32_t now)
{
    if (manualState == ManualState::RunningTest)
    {
        return now >= testEndTime;
    }
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
    if (manualState == ManualState::RunningTest)
    {
        manualState = ManualState::StoppingTest;
    }
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

bool WateringController::startTest(uint8_t valve, uint32_t duration, uint32_t now)
{
    if (duration == 0)
        return false;

    if (activeValve != 255)
        return false;

    if (manualState == ManualState::FillingTank)
        return false;

    if (!tank.hasWater())
        return false;

    testValve = valve;
    testEndTime = now + duration;

    startValve(valve);

    manualState = ManualState::RunningTest;

    return true;
}

void WateringController::stopTest()
{
    if (manualState != ManualState::RunningTest)
        return;

    stopValve();
}

uint32_t WateringController::getRemainingTestTime(uint32_t now)
{
    if (manualState != ManualState::RunningTest &&
        manualState != ManualState::StoppingTest)
        return 0;

    if (now >= testEndTime)
        return 0;

    return testEndTime - now;
}

bool WateringController::isTesting()
{
    return manualState == ManualState::RunningTest ||
           manualState == ManualState::StoppingTest;
}

bool WateringController::startFillTank(uint32_t now)
{
    if (activeValve != 255)
        return false;

    if (tank.isFilled())
        return false;

    fillStartTime = now;
    manualState = ManualState::FillingTank;

    tankFillValve.open();
    delayTimer.start();
    state = State::Opening_WaitMainFeed;

    return true;
}

void WateringController::stopFillTank(uint32_t now)
{
    if (manualState != ManualState::FillingTank)
        return;

    lastFillDuration = now - fillStartTime;
    mainFeedValve.close();

    delayTimer.start();
    state = State::Closing_StopMainFeed;
}

bool WateringController::isFillingTank()
{
    return manualState == ManualState::FillingTank;
}

uint32_t WateringController::getTankFillElapsedTime(uint32_t now)
{
    if (manualState != ManualState::FillingTank)
        return 0;

    if (state == State::Closing_StopMainFeed)
        return lastFillDuration;

    return now - fillStartTime;
}

uint32_t WateringController::getLastTankFillDuration() const
{
    return lastFillDuration;
}

bool WateringController::isTankFilled() const
{
    return tank.isFilled();
}

bool WateringController::isTankEmpty() const
{
    return !tank.hasWater();
}

bool WateringController::isWatering()
{
    return activeValve != 255;
}

bool WateringController::isAutomaticEnabled() const
{
    return automaticEnabled;
}

uint8_t WateringController::getActiveValve() const
{
    return activeValve;
}