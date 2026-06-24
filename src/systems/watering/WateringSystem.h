#pragma once

#include "WateringController.h"
#include "Pump.h"
#include "Tank.h"
#include "Valve.h"
#include "config.h"

class WateringSystem
{
private:
    Pump pump;
    Tank tank;

    Valve valves[VALVE_COUNT];
    Valve outdoorValve;

    WateringController controller;

public:
    WateringSystem();

    void update(uint32_t now);

    WateringController &getController();
};