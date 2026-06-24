#include "SettingsMenu.h"
#include "MainMenu.h"

SettingsMenu::SettingsMenu(Menu &menu)
    : MenuObj(menu, static_cast<uint8_t>(SettingsMenuIndex::ELEMENT_COUNT))
{
}

void SettingsMenu::setMainMenu(MenuObj &m)
{
    mainMenu = &m;
}

void SettingsMenu::setDateTimeMenu(MenuObj &dt)
{
    dateTimeMenu = &dt;
}

void SettingsMenu::setValvesMenu(MenuObj &v)
{
    valvesMenu = &v;
}

void SettingsMenu::executeCmd(Command cmd)
{
    if (cmd != Command::SELECT)
        return;

    handleSelect();
}

void SettingsMenu::handleSelect()
{
    switch (static_cast<SettingsMenuIndex>(menu.getSelectedIndex()))
    {
    case SettingsMenuIndex::BACK:
        menu.setCurrentMenu(*mainMenu, static_cast<uint8_t>(MainMenuIndex::SETTINGS));
        break;

    case SettingsMenuIndex::DATE_TIME:
        menu.setCurrentMenu(*dateTimeMenu);
        break;

    case SettingsMenuIndex::VALVES:
        menu.setCurrentMenu(*valvesMenu);
        break;

    default:
        break;
    }
}

void SettingsMenu::printElement(uint8_t index, uint8_t row)
{
    auto &d = menu.getDisplay();

    d.setCursor(1, row);

    switch (static_cast<SettingsMenuIndex>(index))
    {
    case SettingsMenuIndex::BACK:
        printBackElement(F("Settings"), row);
        break;

    case SettingsMenuIndex::DATE_TIME:
        d.print(F("Date & Time"));
        break;

    case SettingsMenuIndex::VALVES:
        printNextMenu(F("Valves"), row);
        break;

    default:
        break;
    }
}