#include "rotaryEncoder.h"

RotaryEncoder::RotaryEncoder(const RotaryConfig &rotaryConfig)
    : encoder(rotaryConfig.pinA, rotaryConfig.pinB),
      config(rotaryConfig),
      lastCommand(Command::NONE),
      lastPosition(encoder.read()),
      buttonPressed(false),
      debounceTimer(debounceDelay),
      accelerationTimer(accelerationTimeout),
      stepThreshold(defaultThreshold)
{
    pinMode(rotaryConfig.buttonPin, INPUT_PULLUP);
}

void RotaryEncoder::update()
{
    handleRotation();
    handleButton();
}

void RotaryEncoder::handleRotation()
{
    long currentPosition = encoder.read();
    long delta = currentPosition - lastPosition;

    if (abs(delta) >= stepThreshold)
    {
        // Adjust threshold based on rotation speed
        if (!accelerationTimer.timeout())
        {
            stepThreshold = fastThreshold;
        }
        else
        {
            stepThreshold = defaultThreshold;
        }

        accelerationTimer.start();
        lastCommand = (delta > 0) ? Command::LEFT : Command::RIGHT;
        lastPosition = currentPosition;
    }
}

void RotaryEncoder::handleButton()
{
    bool isPressed = digitalRead(config.buttonPin) == LOW;

    if (isPressed && !buttonPressed && debounceTimer.timeout())
    {
        buttonPressed = true;
        debounceTimer.start();
        lastCommand = Command::SELECT;
    }

    if (!isPressed && buttonPressed && debounceTimer.timeout())
    {
        buttonPressed = false;
        debounceTimer.start();
    }
}

Command RotaryEncoder::readCommand()
{
    update();
    Command cmd = lastCommand;
    lastCommand = Command::NONE;
    return cmd;
}