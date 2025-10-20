#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <Arduino.h>
#include "../MenuObj.hpp"

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
public:
    MainMenu(Menu *menu);
    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};

#endif // MAIN_MENU_H