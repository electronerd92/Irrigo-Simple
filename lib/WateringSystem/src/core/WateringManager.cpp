#include "WateringManager.h"

WateringManager::WateringManager(ISystemManager *sysManager, IWaterFeeder *waterFeeder, IWateringValve **valves, uint8_t valvesCount, bool valveOn, bool pumpOn)
    : sysManager(sysManager),
      waterFeeder(waterFeeder),
      wateringValves(valves),
      wateringValvesCount(valvesCount),
      valveOn(valveOn),
      pumpOn(pumpOn)
{
    turnWateringOff();
}

void WateringManager::update()
{
    //TODO
    /*
    - check se il sistema è attivo o in errore/pausa
    - check se il feedWater è ok, altrimenti stoppa tutto e allerta il sys
    - check se c'è una valvola che sta irrigando e aspetta il timeout o la condizione di end 
    - check se c'è una valvola ready e start irrigazione con delay
    */

    for (size_t i = 0; i < wateringValvesCount; i++)
    {
        wateringValves[i]->setState(!valveOn);
    }
}

void WateringManager::turnWateringOff()
{
    waterFeeder->setMainWaterValveState(!valveOn);
    waterFeeder->getPumpState(!pumpOn);
    waterFeeder->setTankValveState(!valveOn);
    for (size_t i = 0; i < wateringValvesCount; i++)
    {
        wateringValves[i]->setState(!valveOn);
    }
}