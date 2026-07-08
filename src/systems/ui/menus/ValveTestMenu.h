#pragma once

#include "systems/ui/EditableMenuObj.h"
#include "systems/watering/WateringController.h"

enum class ValveTestMenuIndex : uint8_t
{
    BACK = 0,
    VALVE,
    DURATION,
    ACTION,
    ELEMENT_COUNT
};

class ValveTestMenu : public EditableMenuObj
{
private:
    WateringController &ctrl;
    MenuObj &actionsMenu;

    uint8_t selectedValve{0};

    uint8_t minutes{1};
    uint8_t seconds{0};

    bool wasRunningTest{false};

    uint32_t getDurationSeconds();

    void handleSelect();
    void handleEdit(Command cmd);
    void printSelected(uint8_t index, uint8_t row);
    void printDuration(uint8_t index, uint8_t row);
    void printAction(uint8_t index, uint8_t row);

public:
    ValveTestMenu(Menu &menu, MenuObj &actionsMenu, WateringController &ctrl);

    void executeCmd(Command cmd) override;
    void printElement(uint8_t index, uint8_t row) override;
};