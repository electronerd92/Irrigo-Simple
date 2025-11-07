#pragma once

#include <interfaces/IBlinker.h>

class MockBlinker : public IBlinker
{
public:
    bool blinking = false;
    void update() override {}
    bool getIsBlinking() const override { return blinking; }
    void startBlinking(const char *, uint8_t, uint8_t) override { blinking = true; }
    void stopBlinking() override { blinking = false; }
};