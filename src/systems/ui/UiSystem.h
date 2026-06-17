#pragma once

#include <Arduino.h>
#include "Blinker.h"
#include "Menu.h"
#include "menus/SettingsMenu.h"
#include "menus/DateTimeMenu.h"
#include "menus/MainMenu.h"
#include "services/DateTimeService.hpp"

class UiSystem
{
private:
    Blinker blinker;
    char buffer[32];

    Menu menu;

    SettingsMenu settingsMenu;
    DateTimeMenu dateTimeMenu;
    MainMenu mainMenu;

public:
    UiSystem(IDisplay &display,
             IInputDevice &input,
             DateTimeService &dateTime)
        : blinker(display),
          menu(display, input, blinker, dateTime, buffer, sizeof(buffer)),
          settingsMenu(menu),
          dateTimeMenu(menu, settingsMenu, dateTime),
          mainMenu(menu)
    {
        // ----- LINK PHASE -----
        mainMenu.setSettingsMenu(settingsMenu);

        settingsMenu.setMainMenu(mainMenu);
        settingsMenu.setDateTimeMenu(dateTimeMenu);
        // settingsMenu.setValvesMenu(valvesMenu); // when exists
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
