#pragma once

#include <Arduino.h>
#include "systems/ui/MenuObj.hpp"

class MenuObj; // forward

enum class MainMenuIndex : uint8_t
{
    SETTINGS,
    INFO,
    ELEMENT_COUNT
};

class MainMenu : public MenuObj
{
private:
    MenuObj *settingsMenu{nullptr};

    void handleSelect();

public:
    MainMenu(Menu &menu);

    void setSettingsMenu(MenuObj &menuObj);

    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};
