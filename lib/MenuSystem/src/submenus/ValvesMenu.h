#pragma once
#include <Arduino.h>
#include "core/MenuObj.hpp"

enum class ValvesMenuIndex : uint8_t
{
    BACK = 0,
    SELECTED_VALVE,
    ELEMENT_COUNT
};

class ValvesMenu : public MenuObj
{
private:
    bool updateBlinker;
    void handleSelectCommand();
    void handleDirectionalCommand(Command cmd);
    void navigateToSettingsMenu();
    void printBackElement(uint8_t row);
    void printSelectedValve(uint8_t index, uint8_t row);
    void handleElementDisplay(uint8_t elementIndex, const char *buffer, uint8_t col, uint8_t row);
    void handleFieldSelection(EditingField lastField);

public:
    ValvesMenu(Menu *menu);
    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};