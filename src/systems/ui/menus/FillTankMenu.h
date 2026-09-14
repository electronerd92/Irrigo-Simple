#pragma once

#include <Arduino.h>
#include "systems/ui/EditableMenuObj.h"
#include "systems/watering/WateringController.h"

class MenuObj;

enum class FillTankMenuIndex : uint8_t
{
    BACK = 0,
    LEVEL,
    ELAPSED,
    ACTION,
    ELEMENT_COUNT
};

class FillTankMenu : public EditableMenuObj
{
private:
    WateringController &ctrl;
    MenuObj &actionsMenu;
    bool wasFilling{false};

    void handleSelect();
    void printLevel(uint8_t index, uint8_t row);
    void printElapsed(uint8_t index, uint8_t row);
    void printAction(uint8_t index, uint8_t row);

public:
    FillTankMenu(Menu &menu, MenuObj &actionsMenu, WateringController &ctrl);

    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};
