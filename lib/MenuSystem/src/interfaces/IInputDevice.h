#pragma once
#include <Arduino.h>

enum class Command : uint8_t
{
    NONE,
    LEFT,
    RIGHT,
    SELECT
};

class IInputDevice
{
public:
    virtual Command readAndClearCommand() = 0;
};