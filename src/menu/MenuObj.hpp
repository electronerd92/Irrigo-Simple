#ifndef MENU_OBJ_H
#define MENU_OBJ_H

#include <Arduino.h>
#include "Menu.h"
#include "InputOutput/Command.h"

class MenuObj
{
protected:
    Menu *menu;
    uint8_t elementCount;
    MenuObj(Menu *menu, uint8_t n) : menu(menu), elementCount(n) {};

public:
    virtual void executeCmd(Command cmd) = 0;
    virtual void printElement(uint8_t index, uint8_t row) = 0;
    inline uint8_t getElementsCount() { return elementCount; }
};

#endif // MENU_OBJ_H