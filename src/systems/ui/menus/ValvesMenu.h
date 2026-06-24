#pragma once

#include "systems/ui/EditableMenuObj.h"
#include "systems/watering/WateringController.h"

enum class ValvesMenuIndex : uint8_t
{
    BACK = 0,
    SELECTED,
    MODE,
    FREQUENCY,
    DURATION,
    START_TIME,
    ELEMENT_COUNT
};

class ValvesMenu : public EditableMenuObj
{
private:
    WateringController &ctrl;
    MenuObj &settingsMenu;

    uint8_t selectedValve{0};

    void handleSelect();
    void handleEdit(Command cmd);

    void printSelected(uint8_t index, uint8_t row);
    void printMode(uint8_t index, uint8_t row);
    void printFrequency(uint8_t index, uint8_t row);
    void printDuration(uint8_t index, uint8_t row);
    void printStartTime(uint8_t index, uint8_t row);

    const char *valveModeToString(ValveMode m);

public:
    ValvesMenu(Menu &menu,
               MenuObj &settingsMenu,
               WateringController &ctrl);

    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};