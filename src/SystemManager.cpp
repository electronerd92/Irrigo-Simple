#include "SystemManager.h"
#include "menu/Menu.h"

SystemManager::SystemManager(MainSystem *mainSystem)
    : mainSystem(mainSystem)
{
    menu = new Menu(this);
}

void SystemManager::update()
{
    menu->update();
}

DateTime SystemManager::getDateTime()
{
    return mainSystem->getDateTime();
}