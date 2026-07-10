#pragma once
#include <Arduino.h>

enum class SystemStatusCode : uint16_t
{
    Ok = 0,

    TankEmpty = 100,
    PersistenceLoadFailed = 101,
    RtcInvalid = 102,

    MenuEditing = 200,
    AutoWatering = 201,
    ValveTestRunning = 202,
};