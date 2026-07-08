#pragma once
#include <Arduino.h>

enum class SystemState : uint8_t
{
    Normal,
    MenuEditing,
    ValveTest
};