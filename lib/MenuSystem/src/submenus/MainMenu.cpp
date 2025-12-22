#include "MainMenu.h"
#include "core/MenuItems.hpp"

MainMenu::MainMenu(Menu *menu) : MenuObj(menu, (uint8_t)MainMenuIndex::ELEMENT_COUNT)
{
}

void MainMenu::executeCmd(Command cmd)
{
    if (cmd != Command::SELECT)
        return;

    handleSelectCommand();
}

void MainMenu::handleSelectCommand()
{
    const auto currentIndex = static_cast<MainMenuIndex>(menu->getElementIndex());
    MenuItems *menuItems = menu->getMenuItems();

    switch (currentIndex)
    {
    case MainMenuIndex::WATER_SOURCE:
        navigateToWaterSourceMenu(menuItems);
        break;

    case MainMenuIndex::SENSORS:
        navigateToSensorsMenu(menuItems);
        break;

    case MainMenuIndex::SETTINGS:
        navigateToSettingsMenu(menuItems);
        break;

    case MainMenuIndex::INFO:
        navigateToInfoMenu(menuItems);
        break;

    default:
        break;
    }
}

void MainMenu::navigateToWaterSourceMenu(MenuItems *menuItems)
{
    // TODO: Implement water source functionality
}

void MainMenu::navigateToSensorsMenu(MenuItems *menuItems)
{
    // TODO: Implement sensors functionality
}

void MainMenu::navigateToSettingsMenu(MenuItems *menuItems)
{
    menu->setCurrentMenu(menuItems->getSettingsMenu());
}

void MainMenu::navigateToInfoMenu(MenuItems *menuItems)
{
    // TODO: Implement info functionality
}

void MainMenu::printElement(uint8_t index, uint8_t row)
{
    IDisplay *dispay = menu->getDispay();
    const auto menuIndex = static_cast<MainMenuIndex>(index);

    switch (menuIndex)
    {
    case MainMenuIndex::WATER_SOURCE:
        dispay->printAt(F(WATER_SOURCE_STR), 1, row);
        break;
    case MainMenuIndex::SENSORS:
        dispay->printAt(F(SENSORS_STR), 1, row);
        break;
    case MainMenuIndex::SETTINGS:
        dispay->printAt(F(SETTINGS_STR), 1, row, PrintFormat::WITH_NEXT);
        break;
    case MainMenuIndex::INFO:
        dispay->printAt(F(INFO_STR), 1, row);
        break;

    default:
        break;
    }
}