#include "MainMenu.h"
#include "../MenuItems.hpp"

MainMenu::MainMenu(Menu *menu) : MenuObj(menu, (uint8_t)MainMenuIndex::ELEMENT_COUNT)
{
}

void MainMenu::executeCmd(Command cmd)
{
    if (cmd != Command::SELECT)
        return;

    MenuItems *menuItems = menu->getMenuItems();

    switch ((MainMenuIndex)menu->getElementIndex())
    {
    case MainMenuIndex::VALVES:
        menu->setCurrentMenu(menuItems->getValvesMenu());
        break;

    case MainMenuIndex::SETTINGS:
        menu->setCurrentMenu(menuItems->getSettingsMenu());
        break;

    default:
        break;
    }
}

void MainMenu::printElement(uint8_t index, uint8_t row)
{
    Lcd *lcd = menu->getLcd();
    MainMenuIndex menuIndex = static_cast<MainMenuIndex>(index);

    switch ((MainMenuIndex)menuIndex)
    {
    case MainMenuIndex::VALVES:
        lcd->print(F(VALVES_STR), 1, row, PrintFormat::WITH_NEXT);
        break;
    case MainMenuIndex::WATER_SOURCE:
        lcd->print(F(WATER_SOURCE_STR), 1, row);
        break;
    case MainMenuIndex::SENSORS:
        lcd->print(F(SENSORS_STR), 1, row);
        break;
    case MainMenuIndex::SETTINGS:
        lcd->print(F(SETTINGS_STR), 1, row, PrintFormat::WITH_NEXT);
        break;
    case MainMenuIndex::INFO:
        lcd->print(F(INFO_STR), 1, row);
        break;

    default:
        break;
    }
}