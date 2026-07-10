
#pragma once
#include <Arduino.h>

#include "SystemStatusCode.h"

class SystemStatusService
{
private:
    SystemStatusCode status{SystemStatusCode::Ok};

public:
    void set(SystemStatusCode s);
    SystemStatusCode get() const;
};
