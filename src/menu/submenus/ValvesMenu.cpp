#include "ValvesMenu.h"
#include "../MenuItems.hpp"

ValvesMenu::ValvesMenu(Menu *menu) : MenuObj(menu, (uint8_t)ValvesMenuIndex::ELEMENT_COUNT)
{
}

void ValvesMenu::executeCmd(Command cmd)
{
    if (cmd != Command::SELECT)
        return;

    MenuItems *menuItems = menu->getMenuItems();

    switch ((ValvesMenuIndex)menu->getElementIndex())
    {
    case ValvesMenuIndex::BACK:
        menu->setCurrentMenu(menuItems->getMainMenu(), (uint8_t)MainMenuIndex::VALVES);
        break;

    default:
        break;
    }
}

void ValvesMenu::printElement(uint8_t index, uint8_t row)
{
    IDisplay *dispay = menu->getDispay();
    switch ((ValvesMenuIndex)index)
    {
    case ValvesMenuIndex::BACK:
        dispay->printAt(F(VALVES_STR), 1, row, PrintFormat::TITLE_WITH_BACK);
        break;
    default:
        break;
    }
}