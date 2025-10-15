#ifndef MENU_ITEMS_H
#define MENU_ITEMS_H

#include "Menu.h"
#include "submenus/MainMenu.h"
#include "submenus/EditMenu.h"

class MenuItems
{
private:
    MenuObj *mainMenu;
    MenuObj *editMenu;

public:
    MenuItems(Menu *menu)
    {
        mainMenu = new MainMenu(menu);
        editMenu = new EditMenu(menu);
    };

    inline MenuObj *getMainMenu() { return mainMenu; }
    inline MenuObj *getEditMenu() { return editMenu; }
};

#endif // MENU_ITEMS_H