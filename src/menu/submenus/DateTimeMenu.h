#ifndef DATE_TIME_MENU_H
#define DATE_TIME_MENU_H

#include <Arduino.h>
#include "../MenuObj.hpp"

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
public:
    DateTimeMenu(Menu *menu);
    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};

#endif // DATE_TIME_MENU_H