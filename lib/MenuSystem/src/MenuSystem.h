#pragma once

#ifndef UNIT_TESTING
#include <interfaces/IMenuSystem.h>
#include "MenuConfig.h"
#include "core/Menu.h"
#include "hardware/Lcd.hpp"
#include "hardware/RotaryEncoder.h"
#include "ui/Blinker.h"

class MenuSystem : public IMenuSystem
{
private:
    Lcd lcd;
    RotaryEncoder encoder;
    Blinker blinker;
    Menu menu;

public:
    MenuSystem(ISystemManager *sysManager, const MenuConfig &config)
        : lcd(config.lcd),
          encoder(config.rotary),
          blinker(&lcd, config.blinker),
          menu(sysManager, &lcd, &encoder, &blinker, config.bufferSize) {}

    void update() override { menu.update(); }
    Menu *getMenu() { return &menu; }
};

#endif // UNIT_TESTING