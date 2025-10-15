#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "../SystemManager.h"
#include "InputOutput/Lcd.hpp"
#include "InputOutput/RotaryEncoder.h"
#include "Blinker.h"

class MenuItems;
class MenuObj;

class Menu
{
private:
    SystemManager *systemManager;
    Lcd lcd;
    RotaryEncoder rotaryEncoder;
    Blinker blinker;

    MenuItems *menuItems;
    MenuObj *currentMenuItem;

    uint8_t elementIndex;
    uint8_t cursor;
    bool refreshScreen;

    void updateElementAndCursor(Command cmd);
    void updateScreen(Command cmd);
    void printCursor();
    void moveDown(uint8_t maxElements);
    void moveUp();
    void renderFullScreen();
    void updateCursorOnly();

public:
    Menu(SystemManager *systemManager);
    void update();
    Lcd *getLcd();
    MenuItems *getMenuItems();
    void setCurrentMenu(MenuObj *menuItem);
    uint8_t getElementIndex() const;
};

#endif // MENU_H