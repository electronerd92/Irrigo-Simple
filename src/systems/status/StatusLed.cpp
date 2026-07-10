#include "StatusLed.h"

StatusLed::StatusLed(uint8_t redPin,
                     uint8_t greenPin,
                     uint8_t bluePin)
    : redPin(redPin),
      greenPin(greenPin),
      bluePin(bluePin),
      blinkTimer(2000)
{
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    setColor(Color::Off);
}

void StatusLed::setColor(Color color)
{
    switch (color)
    {
    case Color::Off:
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, LOW);
        digitalWrite(bluePin, LOW);
        break;

    case Color::Green:
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, HIGH);
        digitalWrite(bluePin, LOW);
        break;

    case Color::Yellow:
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, HIGH);
        digitalWrite(bluePin, LOW);
        break;

    case Color::Red:
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, LOW);
        digitalWrite(bluePin, LOW);
        break;
    }
}

StatusLed::Pattern StatusLed::getPattern(SystemStatusCode status)
{
    switch (status)
    {
    case SystemStatusCode::AutoWatering:
        return {Color::Green, 500};

    case SystemStatusCode::ValveTestRunning:
        return {Color::Yellow, 500};

    case SystemStatusCode::MenuEditing:
        return {Color::Yellow, 1000};

    case SystemStatusCode::TankEmpty:
        return {Color::Red, 1000};

    case SystemStatusCode::Ok:
    default:
        return {Color::Green, 2000};
    }
}

void StatusLed::update(SystemStatusCode status)
{
    Pattern pattern = getPattern(status);

    if (status != currentStatus)
    {
        currentStatus = status;
        currentPeriod = pattern.blinkPeriodMs;

        blinkTimer.updateInterval(currentPeriod, true);

        ledOn = true;

        setColor(pattern.color);

        blinkTimer.start();

        return;
    }

    if (blinkTimer.timeout())
    {
        ledOn = !ledOn;

        if (ledOn)
        {
            setColor(pattern.color);
        }
        else
        {
            setColor(Color::Off);
        }

        blinkTimer.start();
    }
}