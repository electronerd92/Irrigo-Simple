#include "SettingsMenu.h"
#include "../MenuItems.hpp"

SettingsMenu::SettingsMenu(Menu *menu) : MenuObj(menu, (uint8_t)SettingsMenuIndex::ELEMENT_COUNT)
{
}

void SettingsMenu::executeCmd(Command cmd)
{
    if (cmd != Command::SELECT)
        return;

    MenuItems *menuItems = menu->getMenuItems();

    switch ((SettingsMenuIndex)menu->getElementIndex())
    {
    case SettingsMenuIndex::BACK:
        menu->setCurrentMenu(menuItems->getMainMenu(), (uint8_t)MainMenuIndex::SETTINGS);
        break;
    case SettingsMenuIndex::DATE_TIME:
        menu->setCurrentMenu(menuItems->getDateTimeMenu());
        break;
    default:
        break;
    }
}

void SettingsMenu::printElement(uint8_t index, uint8_t row)
{
    Lcd *lcd = menu->getLcd();
    switch ((SettingsMenuIndex)index)
    {
    case SettingsMenuIndex::BACK:
        lcd->print(F(SETTINGS_STR), 1, row, PrintFormat::TITLE_WITH_BACK);
        break;
    case SettingsMenuIndex::DATE_TIME:
        lcd->print(F(DATE_TIME_STR), 1, row);
        break;
    default:
        break;
    }
}