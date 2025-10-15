#include "MainSystem.h"
#include "SystemManager.h"


MainSystem::MainSystem()
{
    systemManager = new SystemManager(this);
}

void MainSystem::update()
{
    systemManager->update();
}