#pragma once
#include <Arduino.h>
#include "hardware/interfaces/IInputDevice.h"
#include "Menu.h"

class MenuObj
{
protected:
    Menu &menu;
    const uint8_t count;

public:
    MenuObj(Menu &menu, uint8_t n)
        : menu(menu), count(n) {}

    virtual void executeCmd(Command cmd) = 0;
    virtual void printElement(uint8_t index, uint8_t row) = 0;

    uint8_t getElementsCount() const { return count; }
};