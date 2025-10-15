#ifndef EDIT_MENU_H
#define EDIT_MENU_H

#include <Arduino.h>
#include "../MenuObj.hpp"

class EditMenu : public MenuObj
{
private:
    static constexpr uint8_t titleIndex = 0;
    static constexpr uint8_t timeIndex = 1;
    static constexpr uint8_t elementCount = 2;

public:
    EditMenu(Menu *menu);
    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};

#endif // EDIT_MENU_H