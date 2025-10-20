#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "../SystemManager.h"
#include "InputOutput/Lcd.hpp"
#include "InputOutput/RotaryEncoder.h"
#include "Blinker.h"

class MenuItems;
class MenuObj;

enum class RefreshType : uint8_t
{
    None,              // no refresh
    CursorOnly,        // redraw cursor
    FullScreen,        // redraw entire LCD
    ClearAndFullScreen // crear and redraw entire LCD
};

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
    RefreshType refreshType;

    void updateElementAndCursor(Command cmd);
    void updateScreen(Command cmd);
    void printCursor();
    void moveDown(uint8_t maxElements);
    void moveUp();
    void renderFullScreen(bool clearAll);
    void updateCursorOnly();

public:
    Menu(SystemManager *systemManager);
    void update();
    Lcd *getLcd();
    MenuItems *getMenuItems();
    void setCurrentMenu(MenuObj *menuItem, uint8_t position = 0);
    uint8_t getElementIndex() const;

    inline void requestFullRefresh(bool clearAll) { refreshType = clearAll ? RefreshType::ClearAndFullScreen : RefreshType::FullScreen; }

    DateTime getDateTime();
};

#endif // MENU_H