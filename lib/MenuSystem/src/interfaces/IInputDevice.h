#ifndef I_INPUT_DEVICE_H
#define I_INPUT_DEVICE_H

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

#endif // I_INPUT_DEVICE_H