#pragma once
#include <Arduino.h>
#include "MenuObj.hpp"

/**
 * @brief Base class for menus with editable fields that support blinking feedback
 *
 * This class provides common functionality for menus that allow editing values
 * with visual feedback (blinking) and field navigation.
 */
class EditableMenuObj : public MenuObj
{
protected:
    bool updateBlinker;

    /**
     * @brief Handles field selection cycling and stops editing when reaching last field
     * @param lastField The last editable field in the sequence
     */
    void handleFieldSelection(EditingField lastField);

    /**
     * @brief Displays an element with optional blinking when being edited
     * @param elementIndex Index of the element being displayed
     * @param buffer Text buffer to display
     * @param col Column position on display
     * @param row Row position on display
     * @param format Optional print format (default: NONE)
     */
    void handleElementDisplay(uint8_t elementIndex, const char *buffer, uint8_t col, uint8_t row);

    /**
     * @brief Prints a back/title element
     * @param title The title string (F macro string)
     * @param row Row position on display
     */
    void printBackElement(const __FlashStringHelper *title, uint8_t row);

    /**
     * @brief Executes increment or decrement based on command direction
     * @param cmd The directional command (LEFT/RIGHT)
     * @param incrementFunc Callable object for increment
     * @param decrementFunc Callable object for decrement
     *
     * @note This is a template function to support lambdas without STL dependency
     */
    template <typename IncrementFunc, typename DecrementFunc>
    void executeDirectionalEdit(Command cmd, IncrementFunc incrementFunc, DecrementFunc decrementFunc, bool forceClear = false)
    {
        if (cmd == Command::RIGHT)
        {
            incrementFunc();
        }
        else if (cmd == Command::LEFT)
        {
            decrementFunc();
        }

        requestBlinkerUpdate(forceClear);
    }

    /**
     * @brief Marks that blinker needs update and requests screen refresh
     */
    void requestBlinkerUpdate(bool forceRefresh);

public:
    EditableMenuObj(Menu *menu, uint8_t elementsCount);
};