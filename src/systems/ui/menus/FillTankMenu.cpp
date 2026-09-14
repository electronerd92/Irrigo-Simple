#include "FillTankMenu.h"
#include "ActionsMenu.h"

FillTankMenu::FillTankMenu(Menu &menu, MenuObj &actionsMenu, WateringController &ctrl)
    : EditableMenuObj(menu, static_cast<uint8_t>(FillTankMenuIndex::ELEMENT_COUNT)),
      ctrl(ctrl),
      actionsMenu(actionsMenu)
{
}

void FillTankMenu::executeCmd(Command cmd)
{
    switch (cmd)
    {
    case Command::SELECT:
        handleSelect();
        break;

    case Command::NONE:
    {
        bool filling = ctrl.isFillingTank();

        if (filling)
        {
            menu.requestRefresh(false);
        }
        else if (wasFilling)
        {
            menu.stopEditing();
            menu.requestRefresh(true);
        }

        wasFilling = filling;
        break;
    }

    default:
        break;
    }
}

void FillTankMenu::handleSelect()
{
    switch (static_cast<FillTankMenuIndex>(menu.getSelectedIndex()))
    {
    case FillTankMenuIndex::BACK:
        menu.setCurrentMenu(actionsMenu, static_cast<uint8_t>(ActionsMenuIndex::FILL_TANK));
        break;

    case FillTankMenuIndex::ACTION:
    {
        if (ctrl.isFillingTank())
        {
            ctrl.stopFillTank(menu.getDateTime().unixTime());
            menu.stopEditing();
            menu.requestRefresh(true);
            return;
        }

        uint32_t now = menu.getDateTime().unixTime();

        if (ctrl.startFillTank(now))
        {
            handleFieldSelection(1);
        }
        else
        {
            menu.requestRefresh(true);
        }

        break;
    }

    default:
        break;
    }
}

void FillTankMenu::printElement(uint8_t index, uint8_t row)
{
    switch (static_cast<FillTankMenuIndex>(index))
    {
    case FillTankMenuIndex::BACK:
        printBackElement(F("Fill Tank"), row);
        break;

    case FillTankMenuIndex::LEVEL:
        printLevel(index, row);
        break;

    case FillTankMenuIndex::ELAPSED:
        printElapsed(index, row);
        break;

    case FillTankMenuIndex::ACTION:
        printAction(index, row);
        break;

    default:
        break;
    }
}

void FillTankMenu::printLevel(uint8_t index, uint8_t row)
{
    auto &d = menu.getDisplay();

    d.setCursor(1, row);
    d.print(F("Level"));

    char *buf = menu.getBuffer();

    if (ctrl.isTankEmpty())
    {
        strcpy(buf, "Empty");
    }
    else if (ctrl.isTankFilled())
    {
        strcpy(buf, "Full");
    }
    else
    {
        strcpy(buf, "Partial");
    }

    const uint8_t col = d.getColumns() - strlen(buf);

    handleElementDisplay(index, buf, col, row);
}

void FillTankMenu::printElapsed(uint8_t index, uint8_t row)
{
    auto &d = menu.getDisplay();
    bool filling = ctrl.isFillingTank();

    d.setCursor(1, row);
    d.print(filling ? F("Elapsed") : F("Duration"));

    uint32_t time = filling
                        ? ctrl.getTankFillElapsedTime(menu.getDateTime().unixTime())
                        : ctrl.getLastTankFillDuration();

    char *buf = menu.getBuffer();
    snprintf(buf, menu.getBufferSize(), "%02lu:%02lu", time / 60UL, time % 60UL);

    handleElementDisplay(index, buf, d.getColumns() - 5, row);
}

void FillTankMenu::printAction(uint8_t index, uint8_t row)
{
    auto &d = menu.getDisplay();

    d.setCursor(1, row);

    if (ctrl.isFillingTank())
    {
        d.print(F("Stop"));
    }
    else
    {
        d.print(F("Start"));
    }

    handleElementDisplay(index, ">", d.getColumns() - 1, row);
}
