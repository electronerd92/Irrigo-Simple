#pragma once

#include <Arduino.h>
#include "systems/ui/MenuObj.hpp"
#include "MainMenu.h"

class MenuObj;

enum class ActionsMenuIndex : uint8_t
{
    BACK = 0,
    VALVE_TEST,
    ELEMENT_COUNT
};

class ActionsMenu : public MenuObj
{
private:
    MenuObj *mainMenu{nullptr};
    MenuObj *valveTestMenu{nullptr};

    void handleSelect();

public:
    ActionsMenu(Menu &menu);

    void setMainMenu(MenuObj &m);
    void setValveTestMenu(MenuObj &menuObj);

    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};