#pragma once
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