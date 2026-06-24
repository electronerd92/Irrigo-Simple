#pragma once
#include <Arduino.h>

enum class ValveMode : uint8_t
{
    Off,
    Timer,
    COUNT
};

struct ValveProgram
{
    ValveMode mode{ValveMode::Off};

    uint32_t startTimestamp{0};

    uint32_t frequency{0}; // seconds (e.g. 86400 for daily)
    uint32_t startTime{0}; // seconds since midnight

    uint32_t duration{0}; // seconds

    uint32_t nextStart{0}; // computed runtime value
};