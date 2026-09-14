#include "WateringSystem.h"

WateringSystem::WateringSystem()
    : pump(PUMP_PIN, PUMP_ON),
      tank(TANK_LOW_LEVEL_PIN, TANK_HAS_WATER, TANK_FILLED_LEVEL_PIN, TANK_IS_FILLED),

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
      tankFillValve(TANK_FILL_VALVE_PIN, VALVE_ON, false),
      mainFeedValve(MAIN_FEED_VALVE_PIN, VALVE_ON, false),

      controller(valves, outdoorValve, tankFillValve, mainFeedValve, pump, tank)
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

Tank &WateringSystem::getTank()
{
    return tank;
}