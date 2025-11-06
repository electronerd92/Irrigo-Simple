#ifdef UNIT_TESTING
#else
#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <Arduino.h>
#include <Encoder.h>
#include <Timer.h>
#include <interfaces/IInputDevice.h>
#include <MenuConfig.h>

class RotaryEncoder : public IInputDevice
{
private:
    Encoder encoder;
    RotaryConfig config;
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
    RotaryEncoder(const RotaryConfig &rotaryConfig);
    Command readAndClearCommand() override;
};

#endif // ROTARY_ENCODER_H
#endif // UNIT_TESTING