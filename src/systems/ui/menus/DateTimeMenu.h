#pragma once

#include <Arduino.h>
#include "systems/ui/EditableMenuObj.h"
#include "services/DateTimeService.hpp"

class MenuObj;

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
    MenuObj &settingsMenu;
    DateTimeService &dateTime;

    void handleSelect();
    void handleEdit(Command cmd);

    void printDate(uint8_t index, uint8_t row);
    void printTime(uint8_t index, uint8_t row);

public:
    DateTimeMenu(Menu &menu,
                 MenuObj &settingsMenu,
                 DateTimeService &service);

    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};