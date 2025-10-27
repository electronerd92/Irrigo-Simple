#ifndef MOCK_MENU_OBJECTS_H
#define MOCK_MENU_OBJECTS_H

#include <interfaces/IInputDevice.h>

class MenuObj
{
public:
    virtual ~MenuObj() = default;
    virtual void executeCmd(Command cmd) = 0;
    virtual uint8_t getElementsCount() = 0;
    virtual void printElement(uint8_t elementIndex, uint8_t row) = 0;
};

class MenuItems
{
public:
    MenuItems(void *menu) {}
    virtual ~MenuItems() = default;
    virtual MenuObj *getMainMenu() = 0;
};

class MockMenuObj : public MenuObj
{
private:
    uint8_t elementsCount;
    Command lastExecutedCmd;
    uint8_t lastPrintElementIndex;
    uint8_t lastPrintElementRow;
    uint8_t executeCmdCallCount;

public:
    MockMenuObj(uint8_t count = 5)
        : elementsCount(count), lastExecutedCmd(Command::NONE),
          lastPrintElementIndex(255), lastPrintElementRow(255), executeCmdCallCount(0) {}

    void executeCmd(Command cmd) override
    {
        lastExecutedCmd = cmd;
        executeCmdCallCount++;
    }

    uint8_t getElementsCount() override { return elementsCount; }

    void printElement(uint8_t elementIndex, uint8_t row) override
    {
        lastPrintElementIndex = elementIndex;
        lastPrintElementRow = row;
    }

    // Test helper methods
    Command getLastExecutedCmd() const { return lastExecutedCmd; }
    uint8_t getLastPrintElementIndex() const { return lastPrintElementIndex; }
    uint8_t getLastPrintElementRow() const { return lastPrintElementRow; }
    uint8_t getExecuteCmdCallCount() const { return executeCmdCallCount; }
    void setElementsCount(uint8_t count) { elementsCount = count; }
    void resetCallCounts()
    {
        executeCmdCallCount = 0;
        lastExecutedCmd = Command::NONE;
        lastPrintElementIndex = 255;
        lastPrintElementRow = 255;
    }
};

class MockMenuItems : public MenuItems
{
private:
    MockMenuObj *mainMenu;

public:
    MockMenuItems() : MenuItems(nullptr)
    {
        mainMenu = new MockMenuObj();
    }

    ~MockMenuItems() { delete mainMenu; }

    MenuObj *getMainMenu() override { return mainMenu; }
    MockMenuObj *getMockMainMenu() { return mainMenu; }
};

#endif // MOCK_MENU_OBJECTS_H