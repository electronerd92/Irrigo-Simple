#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <Arduino.h>
#include "core/MenuObj.hpp"

enum class MainMenuIndex : uint8_t
{
    VALVES = 0,
    WATER_SOURCE,
    SENSORS,
    SETTINGS,
    INFO,
    ELEMENT_COUNT
};

class MainMenu : public MenuObj
{
private:
    void handleSelectCommand();
    void navigateToValvesMenu(MenuItems *menuItems);
    void navigateToWaterSourceMenu(MenuItems *menuItems);
    void navigateToSensorsMenu(MenuItems *menuItems);
    void navigateToSettingsMenu(MenuItems *menuItems);
    void navigateToInfoMenu(MenuItems *menuItems);

public:
    MainMenu(Menu *menu);
    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};

#endif // MAIN_MENU_H