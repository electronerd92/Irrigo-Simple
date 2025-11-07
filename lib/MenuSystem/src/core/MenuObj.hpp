#pragma once
#include <Arduino.h>
#include <interfaces/IInputDevice.h>
#include "Menu.h"

class MenuObj
{
protected:
    Menu *menu;
    const uint8_t elementCount;
    MenuObj(Menu *menu, uint8_t n) : menu(menu), elementCount(n) {};

public:
    virtual void executeCmd(Command cmd) = 0;
    virtual void printElement(uint8_t index, uint8_t row) = 0;
    inline uint8_t getElementsCount() const { return elementCount; }
};