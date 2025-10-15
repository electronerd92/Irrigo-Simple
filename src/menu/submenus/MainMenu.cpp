#include "MainMenu.h"
#include "../MenuItems.hpp"

MainMenu::MainMenu(Menu *menu) : MenuObj(menu, elementCount)
{
}

void MainMenu::executeCmd(Command cmd)
{
    if (cmd != Command::SELECT)
        return;

    MenuItems *menuItems = menu->getMenuItems();

    switch (menu->getElementIndex())
    {
    case editIndex:
        menu->setCurrentMenu(menuItems->getEditMenu());
        break;

    default:
        break;
    }
}

void MainMenu::printElement(uint8_t index, uint8_t row)
{
    Lcd *lcd = menu->getLcd();
    switch (index)
    {
    case editIndex:
        lcd->print(F("Edit"), 1, row);
        break;
    case infoIndex:
        lcd->print(F("Info"), 1, row);
        break;

    default:
        break;
    }
}