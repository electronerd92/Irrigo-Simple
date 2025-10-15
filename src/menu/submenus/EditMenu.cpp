#include "EditMenu.h"
#include "../MenuItems.hpp"

EditMenu::EditMenu(Menu *menu) : MenuObj(menu, elementCount)
{
}

void EditMenu::executeCmd(Command cmd)
{
    if (cmd != Command::SELECT)
        return;

    MenuItems *menuItems = menu->getMenuItems();

    switch (menu->getElementIndex())
    {
    case titleIndex:
        menu->setCurrentMenu(menuItems->getMainMenu());
        break;

    default:
        break;
    }
}

void EditMenu::printElement(uint8_t index, uint8_t row)
{
    Lcd *lcd = menu->getLcd();
    switch (index)
    {
    case titleIndex:
        lcd->print(F(EDIT_STR), 1, row);
        menu->printBackArrow(row);
        break;
    case timeIndex:
        lcd->print(F(TIME_STR), 1, row);
        break;
    default:
        break;
    }
}