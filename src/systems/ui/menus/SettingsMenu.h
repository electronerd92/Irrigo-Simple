#pragma once

#include <Arduino.h>
#include "systems/ui/MenuObj.hpp"

class MenuObj;

enum class SettingsMenuIndex : uint8_t
{
    BACK = 0,
    DATE_TIME,
    VALVES,
    ELEMENT_COUNT
};

class SettingsMenu : public MenuObj
{
private:
    MenuObj *mainMenu{nullptr};
    MenuObj *dateTimeMenu{nullptr};
    MenuObj *valvesMenu{nullptr};

    void handleSelect();

public:
    SettingsMenu(Menu &menu);

    void setMainMenu(MenuObj &m);
    void setDateTimeMenu(MenuObj &dt);
    void setValvesMenu(MenuObj &v);

    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};
