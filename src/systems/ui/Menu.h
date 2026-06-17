
#pragma once

#include <Arduino.h>
#include "hardware/interfaces/IDisplay.h"
#include "hardware/interfaces/IInputDevice.h"
#include "services/DateTimeService.hpp"
#include "Blinker.h"

class MenuObj;

class Menu
{
public:
    Menu(IDisplay &display,
         IInputDevice &input,
         Blinker &blinker,
         DateTimeService &dateTime,
         char *buffer,
         uint8_t bufferSize);

    void init(MenuObj &root);
    void update();

    // --- Access for MenuObj ---
    IDisplay &getDisplay();
    Blinker &getBlinker();
    DateTimeService &getDateTime();

    uint8_t getEditingField() const;

    char *getBuffer();
    uint8_t getBufferSize() const;

    uint8_t getSelectedIndex() const;

    void setCurrentMenu(MenuObj &menu, uint8_t index = 0);

    bool isEditing(uint8_t index) const;
    void nextField();
    void stopEditing();

    void requestRefresh(bool clear);

private:
    enum class RefreshType : uint8_t
    {
        None,
        CursorOnly,
        Full,     // redraw WITHOUT clear
        ClearFull // clear + redraw
    };

    enum class EditingField : uint8_t
    {
        None,
        First,
        Second,
        Third,
        Max
    };

    void handleNavigation(Command cmd);
    void draw(bool clear);
    void drawCursor();
    void drawCursorOnly();

private:
    IDisplay &display;
    IInputDevice &input;
    Blinker &blinker;
    DateTimeService &dateTime;

    MenuObj *current{nullptr};

    uint8_t selected{0};
    uint8_t cursor{0};

    EditingField field{EditingField::None};
    RefreshType refresh{RefreshType::ClearFull};

    char *buffer;
    uint8_t bufferSize;
};
