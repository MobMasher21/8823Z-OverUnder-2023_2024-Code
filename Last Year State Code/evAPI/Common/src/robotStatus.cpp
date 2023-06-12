/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robotStatus.cpp                                           */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      20 Jan 2023                                               */
/*    Description:  Info regarding the status of our robot.                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../../Common/include/robotStatus.h"
#include "../../robotControl/include/Controllers.h"
#include "../../Common/include/evNamespace.h"

namespace evAPI
{
  #define autonTime 15
  #define driverTime 105
  robotStatus robotInfo;
  
  robotStatus::robotStatus()
  {
    if(primaryController.installed()) 
    { controllerAmount++; }
  
    if(secondaryController.installed()) 
    { controllerAmount++; }
  }
  
  void robotStatus::setAlliance(robotAlliance alliance)
  { currentAlliance = alliance; }
  
  int robotStatus::getAlliance()
  { return currentAlliance; }
  
  uint8_t robotStatus::controllerCount()
  { return controllerAmount; }
  
  void robotStatus::driverStart()
  {
    compTimer.reset();
    compMode = driverControl;
    //printf("Started Driver\n");
  }
  
  void robotStatus::autonStart()
  {
    compTimer.reset();
    compMode = autonomousControl;
    //printf("Started Auton\n");
  }
  
  void robotStatus::disabledStart()
  {
    compTimer.reset();
    compMode = disabled;
    //printf("Started Disabled\n");
  }
  
  double robotStatus::getCompetitionTime()
  {
    switch(compMode)
    {
      case disabled:
        return 0;
        break;
  
      case driverControl: 
        return (driverTime - floor(compTimer.time() * 1000));
        break;
  
      case autonomousControl:
        return (autonTime - floor(compTimer.time() * 1000));
        break;
    }
  
    return -1;
  }
}