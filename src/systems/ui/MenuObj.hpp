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

    void printWithNext(const __FlashStringHelper *text, uint8_t row)
    {
        auto &d = menu.getDisplay();

        d.setCursor(1, row);
        d.print(text);

        d.setCursor(d.getColumns() - 1, row);
        d.write('>');
    }

    void printWithBack(const __FlashStringHelper *text, uint8_t row)
    {
        auto &d = menu.getDisplay();

        d.setCursor(1, row);
        d.print(text);

        d.setCursor(d.getColumns() - 1, row);
        d.write('^');
    }
};