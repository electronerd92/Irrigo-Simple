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

enum class EditingField : uint8_t
{
    None,
    First,
    Second,
    Third,
    Max
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

    EditingField editingField;

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
    SystemManager *getSystelManager();
    Lcd *getLcd();
    Blinker *getBlinker();
    MenuItems *getMenuItems();
    void setCurrentMenu(MenuObj *menuItem, uint8_t position = 0);
    uint8_t getElementIndex() const;
    EditingField getEditingField() const;
    bool getIsEditingElement(uint8_t index);
    void incrementEditingField();
    void stopEditing();

    inline void requestFullRefresh(bool clearAll) { refreshType = clearAll ? RefreshType::ClearAndFullScreen : RefreshType::FullScreen; }

    DateTime getDateTime();
};

#endif // MENU_H