#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <Arduino.h>
#include "../MenuObj.hpp"

class MainMenu : public MenuObj
{
private:
    static constexpr uint8_t editIndex = 0;
    static constexpr uint8_t infoIndex = 1;
    static constexpr uint8_t elementCount = 2;

public:
    MainMenu(Menu *menu);
    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};

#endif // MAIN_MENU_H