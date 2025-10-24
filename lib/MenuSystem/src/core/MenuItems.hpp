#ifndef MENU_ITEMS_H
#define MENU_ITEMS_H

#include "Menu.h"
#include "submenus/MenuStrings.h"
#include "submenus/MainMenu.h"
#include "submenus/ValvesMenu.h"
#include "submenus/SettingsMenu.h"
#include "submenus/DateTimeMenu.h"

class MenuItems
{
private:
    MenuObj *mainMenu;
    MenuObj *valvesMenu;
    MenuObj *settingsMenu;
    MenuObj *dateTimeMenu;

public:
    MenuItems(Menu *menu)
    {
        mainMenu = new MainMenu(menu);
        valvesMenu = new ValvesMenu(menu);
        settingsMenu = new SettingsMenu(menu);
        dateTimeMenu = new DateTimeMenu(menu);
    };

    inline MenuObj *getMainMenu() { return mainMenu; }
    inline MenuObj *getValvesMenu() { return valvesMenu; }
    inline MenuObj *getSettingsMenu() { return settingsMenu; }
    inline MenuObj *getDateTimeMenu() { return dateTimeMenu; }
};

#endif // MENU_ITEMS_H