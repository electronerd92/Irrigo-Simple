#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include <ISystemManager.h>
#include <IDisplay.h>
#include <IInputDevice.h>
#include <IBlinker.h>

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
    ISystemManager *sysManager;
    IDisplay *display;
    uint8_t dispayBufferSize;
    IInputDevice *inputDevice;
    IBlinker *blinker;
    char *dispayBuffer;
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
    Menu(ISystemManager *sysManager, IDisplay *display, IInputDevice *inputDevice, IBlinker *blinker, uint8_t bufferSize);
    void update();
    ISystemManager *getSystemManager();
    IDisplay *getDispay();
    char *getDisplayBuffer();
    uint8_t getDisplayBufferSize();

    IBlinker *getBlinker();
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