
#include "ValvesMenu.h"
#include "systems/watering/ValveProgram.h"
#include "config.h"

ValvesMenu::ValvesMenu(Menu &menu,
                       MenuObj &settingsMenu,
                       WateringController &ctrl)
    : EditableMenuObj(menu, (uint8_t)ValvesMenuIndex::ELEMENT_COUNT),
      ctrl(ctrl),
      settingsMenu(settingsMenu)
{
}

void ValvesMenu::executeCmd(Command cmd)
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

    default:
        break;
    }
}

void ValvesMenu::handleSelect()
{
    auto idx = (ValvesMenuIndex)menu.getSelectedIndex();

    switch (idx)
    {
    case ValvesMenuIndex::BACK:
        menu.setCurrentMenu(settingsMenu);
        break;

    case ValvesMenuIndex::SELECTED:
        handleFieldSelection(1);
        break;

    case ValvesMenuIndex::MODE:
        handleFieldSelection(1);
        break;

    case ValvesMenuIndex::FREQUENCY:
        handleFieldSelection(1); // single field
        break;

    case ValvesMenuIndex::DURATION:
        handleFieldSelection(1); // single field
        break;

    case ValvesMenuIndex::START_TIME:
        handleFieldSelection(2); // HH / MM
        break;

    default:
        break;
    }
}
void ValvesMenu::handleEdit(Command cmd)
{

    if (!menu.isEditing(menu.getSelectedIndex()))
        return;

    uint8_t f = menu.getEditingField();

    uint32_t now = menu.getDateTime().unixTime();

    auto idx = static_cast<ValvesMenuIndex>(menu.getSelectedIndex());

    ValveProgram p = ctrl.getProgram(selectedValve);

    if (p.mode == ValveMode::Off)
    {
        switch (idx)
        {
        case ValvesMenuIndex::FREQUENCY:
        case ValvesMenuIndex::DURATION:
        case ValvesMenuIndex::START_TIME:
            return; // block edits
        default:
            break;
        }
    }

    switch (idx)
    {
    case ValvesMenuIndex::SELECTED:
        executeDirectionalEdit(
            cmd,
            [&]()
            { selectedValve = (selectedValve + 1) % VALVE_COUNT; },
            [&]()
            { selectedValve = (selectedValve + VALVE_COUNT - 1) % VALVE_COUNT; },
            true // force refresh
        );
        break;

    case ValvesMenuIndex::MODE:
        executeDirectionalEdit(
            cmd,
            [&]()
            {
                uint8_t current = static_cast<uint8_t>(p.mode);
                uint8_t count = static_cast<uint8_t>(ValveMode::COUNT);

                current = (current + 1) % count;

                p.mode = static_cast<ValveMode>(current);

                ctrl.updateProgram(selectedValve, p, now);
            },
            [&]()
            {
                uint8_t current = static_cast<uint8_t>(p.mode);
                uint8_t count = static_cast<uint8_t>(ValveMode::COUNT);

                current = (current + count - 1) % count;

                p.mode = static_cast<ValveMode>(current);

                ctrl.updateProgram(selectedValve, p, now);
            });
        break;

    case ValvesMenuIndex::FREQUENCY:
        executeDirectionalEdit(
            cmd,
            [&]()
            {
                p.frequency += 12 * 3600UL;
                ctrl.updateProgram(selectedValve, p, now);
            },
            [&]()
            {
                if (p.frequency >= 12 * 3600UL)
                    p.frequency -= 12 * 3600UL;

                ctrl.updateProgram(selectedValve, p, now);
            });
        break;

    case ValvesMenuIndex::DURATION:
        executeDirectionalEdit(
            cmd,
            [&]()
            {
                p.duration += 60;
                ctrl.updateProgram(selectedValve, p, now);
            },
            [&]()
            {
                if (p.duration >= 60)
                    p.duration -= 60;

                ctrl.updateProgram(selectedValve, p, now);
            });
        break;

    case ValvesMenuIndex::START_TIME:
        switch (f)
        {
        case 1: // hours
        {
            uint8_t h = p.startTime / 3600;
            uint8_t m = (p.startTime % 3600) / 60;

            executeDirectionalEdit(
                cmd,
                [&]()

                {
                    h = (h + 1) % 24;
                    p.startTime = h * 3600UL + m * 60UL;
                    ctrl.updateProgram(selectedValve, p, now);
                },
                [&]()
                {
                    h = (h + 23) % 24;
                    p.startTime = h * 3600UL + m * 60UL;
                    ctrl.updateProgram(selectedValve, p, now);
                });

            break;
        }

        case 2: // minutes
        {
            uint8_t h = p.startTime / 3600;
            uint8_t m = (p.startTime % 3600) / 60;

            executeDirectionalEdit(
                cmd,
                [&]()
                {
                    m = (m + 1) % 60;
                    p.startTime = h * 3600UL + m * 60UL;
                    ctrl.updateProgram(selectedValve, p, now);
                },
                [&]()
                {
                    m = (m + 59) % 60;
                    p.startTime = h * 3600UL + m * 60UL;
                    ctrl.updateProgram(selectedValve, p, now);
                });

            break;
        }

        default:
            return;
        }
        break;

    default:
        break;
    }
}

void ValvesMenu::printElement(uint8_t index, uint8_t row)
{
    auto menuIndex = (ValvesMenuIndex)index;

    switch (menuIndex)
    {
    case ValvesMenuIndex::BACK:
        printBackElement(F("Valves"), row);
        break;

    case ValvesMenuIndex::SELECTED:
        printSelected(index, row);
        break;

    case ValvesMenuIndex::MODE:
        printMode(index, row);
        break;

    case ValvesMenuIndex::FREQUENCY:
        printFrequency(index, row);
        break;

    case ValvesMenuIndex::DURATION:
        printDuration(index, row);
        break;

    case ValvesMenuIndex::START_TIME:
        printStartTime(index, row);
        break;

    default:
        break;
    }
}

void ValvesMenu::printSelected(uint8_t index, uint8_t row)
{
    auto &d = menu.getDisplay();

    d.setCursor(1, row);
    d.print(F("Valve"));

    char *buf = menu.getBuffer();
    snprintf(buf, menu.getBufferSize(), "[%u]", selectedValve + 1);

    handleElementDisplay(index, buf, d.getColumns() - 3, row);
}

void ValvesMenu::printMode(uint8_t index, uint8_t row)
{
    auto &d = menu.getDisplay();

    d.setCursor(1, row);
    d.print(F("Mode"));

    auto p = ctrl.getProgram(selectedValve);

    char *buf = menu.getBuffer();

    snprintf(buf, menu.getBufferSize(), "%s", valveModeToString(p.mode));

    handleElementDisplay(index, buf, d.getColumns() - strlen(buf), row);
}

void ValvesMenu::printFrequency(uint8_t index, uint8_t row)
{
    auto &d = menu.getDisplay();

    d.setCursor(1, row);
    d.print(F("Freq"));

    auto p = ctrl.getProgram(selectedValve);

    char *buf = menu.getBuffer();

    if (p.mode == ValveMode::Off)
    {
        snprintf(buf, menu.getBufferSize(), "-");
    }
    else
    {
        snprintf(buf, menu.getBufferSize(), "%luh", p.frequency / 3600UL);
    }

    handleElementDisplay(index, buf, d.getColumns() - strlen(buf), row);
}

void ValvesMenu::printDuration(uint8_t index, uint8_t row)
{
    auto &d = menu.getDisplay();

    d.setCursor(1, row);
    d.print(F("Dur"));

    auto p = ctrl.getProgram(selectedValve);

    char *buf = menu.getBuffer();

    if (p.mode == ValveMode::Off)
    {
        snprintf(buf, menu.getBufferSize(), "-");
    }
    else
    {

        snprintf(buf, menu.getBufferSize(), "%lumin", p.duration / 60UL);
    }

    handleElementDisplay(index, buf, d.getColumns() - strlen(buf), row);
}

void ValvesMenu::printStartTime(uint8_t index, uint8_t row)
{
    auto &d = menu.getDisplay();

    d.setCursor(1, row);
    d.print(F("Start"));

    auto p = ctrl.getProgram(selectedValve);

    uint8_t h = p.startTime / 3600;
    uint8_t m = (p.startTime % 3600) / 60;

    char *buf = menu.getBuffer();

    if (p.mode == ValveMode::Off)
    {
        snprintf(buf, menu.getBufferSize(), "--:--");
    }
    else
    {
        snprintf(buf, menu.getBufferSize(), "%02u:%02u", h, m);
    }

    handleElementDisplay(index, buf, d.getColumns() - 5, row);
}

const char *ValvesMenu::valveModeToString(ValveMode m)
{
    switch (m)
    {
    case ValveMode::Off:
        return "Off";
    case ValveMode::Timer:
        return "Timer";
    default:
        return "?";
    }
}
