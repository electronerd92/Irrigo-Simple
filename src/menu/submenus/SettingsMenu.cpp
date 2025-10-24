#include "SettingsMenu.h"
#include "../MenuItems.hpp"

SettingsMenu::SettingsMenu(Menu *menu) : MenuObj(menu, (uint8_t)SettingsMenuIndex::ELEMENT_COUNT)
{
}

void SettingsMenu::executeCmd(Command cmd)
{
    if (cmd != Command::SELECT)
        return;

    handleSelectCommand();
}

void SettingsMenu::handleSelectCommand()
{
    const auto currentIndex = static_cast<SettingsMenuIndex>(menu->getElementIndex());
    MenuItems *menuItems = menu->getMenuItems();

    switch (currentIndex)
    {
    case SettingsMenuIndex::BACK:
        navigateToMainMenu(menuItems);
        break;

    case SettingsMenuIndex::DATE_TIME:
        navigateToDateTimeMenu(menuItems);
        break;

    default:
        break;
    }
}

void SettingsMenu::navigateToMainMenu(MenuItems *menuItems)
{
    menu->setCurrentMenu(menuItems->getMainMenu(), (uint8_t)MainMenuIndex::SETTINGS);
}

void SettingsMenu::navigateToDateTimeMenu(MenuItems *menuItems)
{
    menu->setCurrentMenu(menuItems->getDateTimeMenu());
}

void SettingsMenu::printElement(uint8_t index, uint8_t row)
{
    IDisplay *dispay = menu->getDispay();
    switch ((SettingsMenuIndex)index)
    {
    case SettingsMenuIndex::BACK:
        dispay->printAt(F(SETTINGS_STR), 1, row, PrintFormat::TITLE_WITH_BACK);
        break;
    case SettingsMenuIndex::DATE_TIME:
        dispay->printAt(F(DATE_TIME_STR), 1, row);
        break;
    default:
        break;
    }
}