#pragma once
#include <Arduino.h>
#include "core/EditableMenuObj.h"

enum class ValvesMenuIndex : uint8_t
{
    BACK = 0,
    SELECTED_VALVE,
    VALVE_MODE,
    FREQUENCY,
    ELEMENT_COUNT
};

class ValvesMenu : public EditableMenuObj
{
private:
    void handleSelectCommand();
    void handleDirectionalCommand(Command cmd);
    void navigateToSettingsMenu();
    void printSelectedValve(uint8_t index, uint8_t row);
    void printValveMode(uint8_t index, uint8_t row);
    void printFrequency(uint8_t index, uint8_t row);

public:
    ValvesMenu(Menu *menu);
    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};