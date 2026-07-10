
#include "SystemStatusService.h"

void SystemStatusService::set(SystemStatusCode s)
{
    status = s;
}

SystemStatusCode SystemStatusService::get() const
{
    return status;
}
