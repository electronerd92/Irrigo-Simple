#ifndef MOCK_INPUT_DEVICE_H
#define MOCK_INPUT_DEVICE_H

#include <interfaces/IInputDevice.h>

class MockInputDevice : public IInputDevice
{
private:
    Command nextCommand;
    Command commandQueue[10];
    uint8_t queueSize;
    uint8_t queueIndex;

public:
    MockInputDevice() : nextCommand(Command::NONE), queueSize(0), queueIndex(0)
    {
        for (int i = 0; i < 10; i++)
        {
            commandQueue[i] = Command::NONE;
        }
    }

    Command readCommand() override
    {
        if (queueSize > 0 && queueIndex < queueSize)
        {
            Command cmd = commandQueue[queueIndex];
            queueIndex++;
            if (queueIndex >= queueSize)
            {
                queueSize = 0;
                queueIndex = 0;
            }
            return cmd;
        }

        Command cmd = nextCommand;
        nextCommand = Command::NONE;
        return cmd;
    }

    // Test helper methods
    void setNextCommand(Command cmd) { nextCommand = cmd; }

    void queueCommands(Command *commands, uint8_t count)
    {
        queueSize = min(count, (uint8_t)10);
        queueIndex = 0;
        for (uint8_t i = 0; i < queueSize; i++)
        {
            commandQueue[i] = commands[i];
        }
    }

    void clearQueue()
    {
        queueSize = 0;
        queueIndex = 0;
        nextCommand = Command::NONE;
    }
};

#endif // MOCK_INPUT_DEVICE_H