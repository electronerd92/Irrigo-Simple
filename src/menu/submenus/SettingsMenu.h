#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include <Arduino.h>
#include "../MenuObj.hpp"

enum class SettingsMenuIndex : uint8_t
{
    BACK = 0,
    DATE_TIME,
    ELEMENT_COUNT
};

class SettingsMenu : public MenuObj
{
private:
    void handleSelectCommand();
    void navigateToMainMenu(MenuItems *menuItems);
    void navigateToDateTimeMenu(MenuItems *menuItems);

public:
    SettingsMenu(Menu *menu);
    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};

#endif // SETTINGS_MENU_H