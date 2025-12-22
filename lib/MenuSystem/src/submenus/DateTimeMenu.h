#pragma once
#include <Arduino.h>
#include "core/EditableMenuObj.h"

enum class DateTimeMenuIndex : uint8_t
{
    BACK = 0,
    DATE,
    TIME,
    ELEMENT_COUNT
};

class DateTimeMenu : public EditableMenuObj
{
private:
    void handleNoCommand();
    void handleSelectCommand();
    void handleDirectionalCommand(Command cmd);
    void handleDateEditing(Command cmd);
    void handleTimeEditing(Command cmd);
    void navigateToSettingsMenu();
    void printDateElement(uint8_t index, uint8_t row);
    void printTimeElement(uint8_t index, uint8_t row);

public:
    DateTimeMenu(Menu *menu);
    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};