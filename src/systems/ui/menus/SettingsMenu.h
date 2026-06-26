#pragma once

#include <Arduino.h>
#include "systems/ui/MenuObj.hpp"
#include "systems/ui/ConfirmMenu.h"

#include "services/PersistenceService.h"

class MenuObj;

enum class SettingsMenuIndex : uint8_t
{
    BACK = 0,
    DATE_TIME,
    VALVES,
    SAVE,
    LOAD,
    ELEMENT_COUNT
};

class SettingsMenu : public MenuObj
{
private:
    MenuObj *mainMenu{nullptr};
    MenuObj *dateTimeMenu{nullptr};
    MenuObj *valvesMenu{nullptr};

    PersistenceService &persistence;

    void handleSelect();

    ConfirmMenu &confirmMenu;

    enum class PendingAction : uint8_t
    {
        None,
        Save,
        Load
    };

    enum class ActionResult : uint8_t
    {
        None,
        SavedOK,
        SavedError,
        LoadedOK,
        LoadedError
    };

    PendingAction pending{PendingAction::None};
    ActionResult result{ActionResult::None};
    bool resultVisible{false};

public:
    SettingsMenu(Menu &menu, PersistenceService &p, ConfirmMenu &cm);

    void setMainMenu(MenuObj &m);
    void setDateTimeMenu(MenuObj &dt);
    void setValvesMenu(MenuObj &v);

    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};
