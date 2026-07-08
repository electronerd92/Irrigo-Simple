#include "WateringSystem.h"

WateringSystem::WateringSystem()
    : pump(PUMP_PIN, PUMP_ON),
      tank(TANK_LOW_LEVEL_PIN, TANK_HAS_WATER),

      valves{
          {VALVE_PINS[0], VALVE_ON, false},
          {VALVE_PINS[1], VALVE_ON, false},
          {VALVE_PINS[2], VALVE_ON, false},
          {VALVE_PINS[3], VALVE_ON, false},
          {VALVE_PINS[4], VALVE_ON, true},
          {VALVE_PINS[5], VALVE_ON, true},
          {VALVE_PINS[6], VALVE_ON, true},
          {VALVE_PINS[7], VALVE_ON, true},
      },

      outdoorValve(OUTDOOR_VALVE_PIN, VALVE_ON, false),

      controller(valves, outdoorValve, pump, tank)
{
}

void WateringSystem::update(uint32_t now)
{
    controller.update(now);
}

WateringController &WateringSystem::getController()
{
    return controller;
}