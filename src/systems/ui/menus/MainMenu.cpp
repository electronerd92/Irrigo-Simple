#include "MainMenu.h"

MainMenu::MainMenu(Menu &menu)
    : MenuObj(menu, static_cast<uint8_t>(MainMenuIndex::ELEMENT_COUNT))
{
}

void MainMenu::setSettingsMenu(MenuObj &m)
{
    settingsMenu = &m;
}

void MainMenu::executeCmd(Command cmd)
{
    if (cmd != Command::SELECT)
        return;

    handleSelect();
}

void MainMenu::handleSelect()
{
    switch (static_cast<MainMenuIndex>(menu.getSelectedIndex()))
    {
    case MainMenuIndex::SETTINGS:
        menu.setCurrentMenu(*settingsMenu);
        break;

    case MainMenuIndex::WATER_SOURCE:
        // TODO
        break;

    case MainMenuIndex::SENSORS:
        // TODO
        break;

    case MainMenuIndex::INFO:
        // TODO
        break;

    default:
        break;
    }
}

void MainMenu::printElement(uint8_t index, uint8_t row)
{
    auto &display = menu.getDisplay();

    display.setCursor(1, row);

    switch (static_cast<MainMenuIndex>(index))
    {
    case MainMenuIndex::WATER_SOURCE:
        display.print(F("Water Source"));
        break;

    case MainMenuIndex::SENSORS:
        display.print(F("Sensors"));
        break;

    case MainMenuIndex::SETTINGS:
        display.print(F("Settings"));

        // next arrow
        display.setCursor(display.getColumns() - 1, row);
        display.write('>');
        break;

    case MainMenuIndex::INFO:
        display.print(F("Info"));
        break;

    default:
        break;
    }
}