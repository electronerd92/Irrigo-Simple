#include "MainMenu.h"
#include "../MenuItems.hpp"

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
    case MainMenuIndex::VALVES:
        navigateToValvesMenu(menuItems);
        break;

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

void MainMenu::navigateToValvesMenu(MenuItems *menuItems)
{
    menu->setCurrentMenu(menuItems->getValvesMenu());
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
    Lcd *lcd = menu->getLcd();
    const auto menuIndex = static_cast<MainMenuIndex>(index);

    switch (menuIndex)
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