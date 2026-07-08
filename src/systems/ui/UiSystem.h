#pragma once

#include <Arduino.h>
#include "Blinker.h"
#include "Menu.h"
#include "ConfirmMenu.h"
#include "menus/SettingsMenu.h"
#include "menus/ActionsMenu.h"
#include "menus/DateTimeMenu.h"
#include "menus/ValvesMenu.h"
#include "menus/ValveTestMenu.h"
#include "menus/MainMenu.h"
#include "services/DateTimeService.hpp"
#include "services/PersistenceService.h"
#include "systems/watering/WateringController.h"

class UiSystem
{
private:
    Blinker blinker;
    char buffer[32];

    Menu menu;

    ConfirmMenu confirmMenu;
    SettingsMenu settingsMenu;
    ActionsMenu actionsMenu;
    DateTimeMenu dateTimeMenu;
    ValvesMenu valvesMenu;
    ValveTestMenu valveTestMenu;
    MainMenu mainMenu;

public:
    UiSystem(IDisplay &display,
             IInputDevice &input,
             DateTimeService &dateTime,
             PersistenceService &persistence,
             WateringController &wateringController)
        : blinker(display),
          menu(display, input, blinker, dateTime, buffer, sizeof(buffer)),
          confirmMenu(menu),
          settingsMenu(menu, persistence, confirmMenu),
          actionsMenu(menu),
          dateTimeMenu(menu, settingsMenu, dateTime),
          valvesMenu(menu, settingsMenu, wateringController),
          valveTestMenu(menu, actionsMenu, wateringController),
          mainMenu(menu)
    {
        // ----- LINK PHASE -----
        mainMenu.setSettingsMenu(settingsMenu);
        mainMenu.setActionsMenu(actionsMenu);

        settingsMenu.setMainMenu(mainMenu);
        settingsMenu.setDateTimeMenu(dateTimeMenu);
        settingsMenu.setValvesMenu(valvesMenu);

        actionsMenu.setMainMenu(mainMenu);
        actionsMenu.setValveTestMenu(valveTestMenu);
    }

    void begin()
    {
        menu.init(mainMenu);
    }

    void update()
    {
        menu.update();
    }
};
