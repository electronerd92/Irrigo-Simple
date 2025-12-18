#include "WateringManager.h"
#include "interfaces/IMainSystem.h"

WateringManager::WateringManager(ISystemManager *sysManager, IWaterFeeder *waterFeeder,
                                 IWateringValve **valves, uint8_t valvesCount, uint8_t outdoorValvePin,
                                 bool valveOn, uint32_t valvePumpDelay)
    : sysManager(sysManager),
      waterFeeder(waterFeeder),
      wateringValves(valves),
      wateringValvesCount(valvesCount),
      outdoorValvePin(outdoorValvePin),
      valveOn(valveOn),
      valvePumpDelayTimer(valvePumpDelay),
      ongoingOpeningClosing(false)
{
    pinMode(outdoorValvePin, OUTPUT);
    turnWateringOff();
}

void WateringManager::update()
{
    // TODO
    /*
    - check se il sistema è attivo o in errore/pausa
    - check se il feedWater è ok, altrimenti stoppa tutto e allerta il sys
    - check se c'è una valvola che sta irrigando e aspetta il timeout o la condizione di end
    - check se c'è una valvola ready e start irrigazione con delay
    */

    if (sysManager->getSystemState() != SystemState::Normal)
    {
        return;
    }

    int8_t openedValve = getOpenedValve();

    if (ongoingOpeningClosing)
    {
        manageOngoingOperation(openedValve);
    }

    if (openedValve == -1)
    {
        checkAndOpenValve();
    }

    else
    {
        checkAndCloseValve();
    }
}

int8_t WateringManager::getOpenedValve()
{
    int8_t openValve = -1;
    for (uint8_t i = 0; i < wateringValvesCount; i++)
    {
        if ((bool)wateringValves[i]->getState() == valveOn)
        {
            openValve = i;
            break;
        }
    }
    return openValve;
}

void WateringManager::turnWateringOff()
{
    waterFeeder->stopMainWatering();
    waterFeeder->stopPump();
    waterFeeder->setTankValveState(!valveOn);
    setOutdoorValveState(!valveOn);
    for (uint8_t i = 0; i < wateringValvesCount; i++)
    {
        wateringValves[i]->close(!valveOn);
    }
}

void WateringManager::checkAndOpenValve()
{
    for (uint8_t i = 0; i < wateringValvesCount; i++)
    {
        if (wateringValves[i]->canBeOpened(sysManager->getUnixTime()))
        {
            wateringValves[i]->open(valveOn);
            if (wateringValves[i]->getIsOutdoor())
            {
                setOutdoorValveState(valveOn);
            }
            ongoingOpeningClosing = true;
            valvePumpDelayTimer.start();
            break;
        }
    }
}

void WateringManager::checkAndCloseValve()
{
    for (uint8_t i = 0; i < wateringValvesCount; i++)
    {
        if (wateringValves[i]->canBeClosed())
        {
            waterFeeder->stopPump();
            ongoingOpeningClosing = true;
            valvePumpDelayTimer.start();
            break;
        }
    }
}

void WateringManager::manageOngoingOperation(int8_t openedValve)
{
    if (!valvePumpDelayTimer.timeout())
        return;

    if (waterFeeder->isFeeding() && openedValve != -1)
    {
        wateringValves[openedValve]->close(!valveOn);
        if (wateringValves[openedValve]->getIsOutdoor())
        {
            setOutdoorValveState(!valveOn);
        }
    }
    else
    {
        waterFeeder->startPump();
    }
    ongoingOpeningClosing = false;
}

int WateringManager::getOutdoorValveState()
{
    return digitalRead(outdoorValvePin);
}

void WateringManager::setOutdoorValveState(bool state)
{
    digitalWrite(outdoorValvePin, state);
}