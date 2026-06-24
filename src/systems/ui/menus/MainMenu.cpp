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
    case MainMenuIndex::MAIN:
        menu.sleep(); // sleep the system when selecting "Main"
        break;

    case MainMenuIndex::SETTINGS:
        menu.setCurrentMenu(*settingsMenu);
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
    case MainMenuIndex::MAIN:
        printBackElement(F("Main"), row);
        break;

    case MainMenuIndex::SETTINGS:
        printNextMenu(F("Settings"), row);
        break;

    case MainMenuIndex::INFO:
        display.print(F("Info"));
        break;

    default:
        break;
    }
}