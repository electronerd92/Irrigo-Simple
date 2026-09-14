#pragma once

#include <ArduinoFake.h>

using namespace fakeit;

inline void setupArduinoFake()
{
    ArduinoFakeReset();

    When(Method(ArduinoFake(), pinMode))
        .AlwaysReturn();

    When(Method(ArduinoFake(), digitalWrite))
        .AlwaysReturn();

    When(Method(ArduinoFake(), digitalRead))
        .AlwaysReturn(0);

    When(Method(ArduinoFake(), millis))
        .AlwaysReturn(0);
}