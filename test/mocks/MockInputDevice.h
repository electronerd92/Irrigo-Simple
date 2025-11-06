#ifndef MOCK_INPUT_DEVICE_H
#define MOCK_INPUT_DEVICE_H

#include <interfaces/IInputDevice.h>

class MockInputDevice : public IInputDevice
{
public:
    Command nextCommand = Command::NONE;
    Command readAndClearCommand() override
    {
        Command cmd = nextCommand;
        nextCommand = Command::NONE;
        return cmd;
    }
};

#endif // MOCK_INPUT_DEVICE_H