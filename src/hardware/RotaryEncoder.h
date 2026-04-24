#pragma once
#ifndef UNIT_TESTING
#include <Arduino.h>
#include <Encoder.h>
#include "interfaces/IInputDevice.h"
#include "utils/Timer.h"

class RotaryEncoder : public IInputDevice
{
private:
    Encoder encoder;
    Command lastCommand;
    long lastPosition;
    bool buttonPressed;
    Timer debounceTimer;
    Timer accelerationTimer;
    int stepThreshold;

    // Constants
    static constexpr uint32_t debounceDelay = 50;
    static constexpr uint32_t accelerationTimeout = 400;
    static constexpr int defaultThreshold = 4;
    static constexpr int fastThreshold = 2;

    void handleRotation();
    void handleButton();
    void update();

public:
    RotaryEncoder();
    Command readAndClearCommand() override;
};

#endif // UNIT_TESTING