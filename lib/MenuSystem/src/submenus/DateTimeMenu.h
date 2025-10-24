#ifndef DATE_TIME_MENU_H
#define DATE_TIME_MENU_H

#include <Arduino.h>
#include "core/MenuObj.hpp"

enum class DateTimeMenuIndex : uint8_t
{
    BACK = 0,
    DATE,
    TIME,
    ELEMENT_COUNT
};

class DateTimeMenu : public MenuObj
{
private:
    bool updateBlinker;
    void handleFieldSelection(EditingField lastField);
    void handleElementDisplay(uint8_t elementIndex, const char *buffer, uint8_t col, uint8_t row);
    void printBackElement(uint8_t row);
    void printDateElement(uint8_t index, uint8_t row);
    void printTimeElement(uint8_t index, uint8_t row);
    void handleNoCommand();
    void handleSelectCommand();
    void handleDirectionalCommand(Command cmd);
    void handleDateEditing(Command cmd, EditingField editingField);
    void handleTimeEditing(Command cmd, EditingField editingField);
    void navigateToSettingsMenu();

public:
    DateTimeMenu(Menu *menu);
    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};

#endif // DATE_TIME_MENU_H