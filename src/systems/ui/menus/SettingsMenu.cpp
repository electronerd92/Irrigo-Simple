#include "SettingsMenu.h"
#include "MainMenu.h"

SettingsMenu::SettingsMenu(Menu &menu, PersistenceService &p, ConfirmMenu &cm)
    : MenuObj(menu, static_cast<uint8_t>(SettingsMenuIndex::ELEMENT_COUNT)),
      persistence(p),
      confirmMenu(cm)
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
    // Check if confirmation just finished

    if (confirmMenu.isDone())
    {
        if (confirmMenu.getResult())
        {
            if (pending == PendingAction::Save)
            {
                bool ok = persistence.save();
                result = ok ? ActionResult::SavedOK : ActionResult::SavedError;
            }
            else if (pending == PendingAction::Load)
            {
                uint32_t now = menu.getDateTime().unixTime();
                bool ok = persistence.load(now);
                result = ok ? ActionResult::LoadedOK : ActionResult::LoadedError;
            }

            resultVisible = true; // trigger display
            menu.requestRefresh(false);
        }

        pending = PendingAction::None;
        confirmMenu.reset();
        return;
    }

    // Auto-clear result after one cycle (simple)
    if (resultVisible && cmd == Command::NONE)
    {
        resultVisible = false;
        result = ActionResult::None;
    }

    if (cmd == Command::SELECT)
    {
        handleSelect();
    }
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

    case SettingsMenuIndex::SAVE:
    {
        pending = PendingAction::Save;

        confirmMenu.setContext(*this, F("Save?"));
        menu.setCurrentMenu(confirmMenu, 1);

        break;
    }

    case SettingsMenuIndex::LOAD:
    {
        pending = PendingAction::Load;

        confirmMenu.setContext(*this, F("Load?"));
        menu.setCurrentMenu(confirmMenu, 1);

        break;
    }

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

    case SettingsMenuIndex::SAVE:
        d.print(F("Save"));
        if (resultVisible)
        {
            if (result == ActionResult::SavedOK)
            {
                d.setCursor(d.getColumns() - 3, row);
                d.print(F("OK"));
            }
            else if (result == ActionResult::SavedError)
            {
                d.setCursor(d.getColumns() - 4, row);
                d.print(F("ERR"));
            }
        }
        break;

    case SettingsMenuIndex::LOAD:
        d.print(F("Load"));
        if (resultVisible)
        {
            if (result == ActionResult::LoadedOK)
            {
                d.setCursor(d.getColumns() - 3, row);
                d.print(F("OK"));
            }
            else if (result == ActionResult::LoadedError)
            {
                d.setCursor(d.getColumns() - 4, row);
                d.print(F("ERR"));
            }
        }
        break;

    default:
        break;
    }
}