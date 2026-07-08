#include "ValveTestMenu.h"
#include "ActionsMenu.h"

ValveTestMenu::ValveTestMenu(Menu &menu, MenuObj &actionsMenu, WateringController &ctrl)
    : EditableMenuObj(menu, static_cast<uint8_t>(ValveTestMenuIndex::ELEMENT_COUNT)),
      ctrl(ctrl),
      actionsMenu(actionsMenu)
{
}

void ValveTestMenu::executeCmd(Command cmd)
{
    switch (cmd)
    {
    case Command::SELECT:
        handleSelect();
        break;

    case Command::LEFT:
    case Command::RIGHT:
        handleEdit(cmd);
        break;

    case Command::NONE:
    {
        bool running = ctrl.isTesting();

        if (running)
        {
            menu.requestRefresh(false);
        }
        else if (wasRunningTest)
        {
            // test just finished
            menu.stopEditing();
            menu.requestRefresh(true);
        }

        wasRunningTest = running;
        break;
    }

    default:
        break;
    }
}

void ValveTestMenu::handleSelect()
{
    switch (static_cast<ValveTestMenuIndex>(menu.getSelectedIndex()))
    {
    case ValveTestMenuIndex::BACK:
        menu.setCurrentMenu(actionsMenu, static_cast<uint8_t>(ActionsMenuIndex::VALVE_TEST));
        break;

    case ValveTestMenuIndex::VALVE:
        handleFieldSelection(1);
        break;

    case ValveTestMenuIndex::DURATION:
        handleFieldSelection(2);
        break;

    case ValveTestMenuIndex::ACTION:
    {
        if (ctrl.isTesting())
        {
            ctrl.stopTest();
            menu.stopEditing();
            menu.requestRefresh(true);
            return;
        }

        uint32_t now = menu.getDateTime().unixTime();

        if (ctrl.startTest(selectedValve, getDurationSeconds(), now))
        {
            handleFieldSelection(1);
        }

        break;
    }

    default:
        break;
    }
}

void ValveTestMenu::handleEdit(Command cmd)
{
    if (!menu.isEditing(menu.getSelectedIndex()))
        return;

    uint8_t f = menu.getEditingField();

    switch (static_cast<ValveTestMenuIndex>(menu.getSelectedIndex()))
    {
    case ValveTestMenuIndex::VALVE:
        executeDirectionalEdit(
            cmd,
            [&]()
            { selectedValve = (selectedValve + 1) % VALVE_COUNT; },
            [&]()
            { selectedValve = (selectedValve + VALVE_COUNT - 1) % VALVE_COUNT; });
        break;

    case ValveTestMenuIndex::DURATION:
        switch (f)
        {
        case 1: // minutes
            executeDirectionalEdit(
                cmd,
                [&]()
                { minutes = (minutes + 1) % 60; },
                [&]()
                { minutes = (minutes + 59) % 60; });
            break;
        case 2: // seconds
            executeDirectionalEdit(
                cmd,
                [&]()
                { seconds = (seconds + 1) % 60; },
                [&]()
                { seconds = (seconds + 59) % 60; });
            break;

        default:
            return;
        }

    default:
        return;
    }
}

void ValveTestMenu::printElement(uint8_t index, uint8_t row)
{
    switch (static_cast<ValveTestMenuIndex>(index))
    {
    case ValveTestMenuIndex::BACK:
        printBackElement(F("Valve Test"), row);
        break;

    case ValveTestMenuIndex::VALVE:
        printSelected(index, row);
        break;

    case ValveTestMenuIndex::DURATION:
        printDuration(index, row);
        break;

    case ValveTestMenuIndex::ACTION:
        printAction(index, row);
        break;
    default:
        break;
    }
}

void ValveTestMenu::printSelected(uint8_t index, uint8_t row)
{
    auto &d = menu.getDisplay();

    d.setCursor(1, row);
    d.print(F("Valve"));

    char *buf = menu.getBuffer();
    snprintf(buf, menu.getBufferSize(), "[%u]", selectedValve + 1);

    handleElementDisplay(index, buf, d.getColumns() - 3, row);
}

void ValveTestMenu::printDuration(uint8_t index, uint8_t row)
{
    auto &d = menu.getDisplay();
    d.setCursor(1, row);

    if (ctrl.isTesting())
    {
        d.print(F("Remaining"));

        uint32_t remaining = ctrl.getRemainingTestTime(menu.getDateTime().unixTime());

        char *buf = menu.getBuffer();
        snprintf(buf, menu.getBufferSize(), "%02lu:%02lu", remaining / 60UL, remaining % 60UL);

        handleElementDisplay(index, buf, d.getColumns() - 5, row);
    }
    else
    {
        d.print(F("Duration"));

        char *buf = menu.getBuffer();
        snprintf(buf, menu.getBufferSize(), "%02u:%02u", minutes, seconds);

        handleElementDisplay(index, buf, d.getColumns() - 5, row);
    }
}

void ValveTestMenu::printAction(uint8_t index, uint8_t row)
{
    auto &d = menu.getDisplay();

    d.setCursor(1, row);

    if (ctrl.isTesting())
    {
        d.print(F("Stop"));
    }
    else
    {
        d.print(F("Run"));
    }

    handleElementDisplay(index, ">", d.getColumns() - 1, row);
}

uint32_t ValveTestMenu::getDurationSeconds()
{
    return minutes * 60UL + seconds;
}
