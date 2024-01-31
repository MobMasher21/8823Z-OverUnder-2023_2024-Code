/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       launcher.cpp                                              */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Jan 29, 2024                                              */
/*    Description:  Launcher class for managing catapults and punchers        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../evAPI/Common/include/evAPIBasicConfig.h"
#include "../evAPI/Common/include/generalFunctions.h"
#include "launcher.h"

struct launcherThreadData
{
  launcher *launcherObject;
  std::vector<double> *criticalAngles;
  std::vector<launcher::controllerMappingData> *controllerMappings;
};

int launcherThread(void *launcherDataRaw)
{
  //Convert the input data back into a launcher object
  launcherThreadData *launcherData = (launcherThreadData*)launcherDataRaw;
  launcher *Launcher = launcherData->launcherObject;
  //std::vector<double> *criticalAngles = launcherData->criticalAngles;
  //std::vector<launcher::controllerMappingData> *controllerMappings = launcherData->controllerMappings;

  //*Main thread loop
  while(true)
  {
    //*Check controller buttons
    /* for (size_t i = 0; i < count; i++)
    {

    } */

    //*Run auto code if manual control is disabled
    if(!Launcher->manualControlEnabled())
    {
      //Get the data from the sensor
      evAPI::evErrorDouble sensorAngle = Launcher->getSensorAngle();

      if(sensorAngle.errorData == evAPI::evError::No_Error)
      {
        //Get the critical angle
        evAPI::evErrorDouble criticalAngle = Launcher->getCriticalAngle();

        if(criticalAngle.errorData == evAPI::evError::No_Error)
        {
          //*Control the launcher motor(s)
          if(sensorAngle.data < criticalAngle.data)
          {
            Launcher->spinLauncher();
          }

          else
          {
            Launcher->stopLauncher();
          }
        }

        //*Force Enable manual control mode and print an error
        else
        {        
          Launcher->setManualControl(true);
          fprintf(stderr, "\nLauncher failed to get critical angles: %s\n", 
                  evErrorToString(criticalAngle.errorData).c_str());
        }
      }

      //*Force Enable manual control mode and print an error
      else
      {
        Launcher->setManualControl(true);
        fprintf(stderr, "\nLauncher failed to get sensor angle: %s\n", 
                evErrorToString(sensorAngle.errorData).c_str());
      }
    }

    this_thread::sleep_for(15);
  }

  return 0;
}

launcher::launcher(vex::motor &motor)
{
  launcherMotors = new vex::motor_group(motor);
  launcherInit();
}

launcher::launcher(vex::motor_group &motors)
{
  launcherMotors = &motors;
  launcherInit();
}

launcher::~launcher()
{}

evAPI::evError launcher::addSensor(vex::rotation &sensor)
{
  //Exit if the rotation sensor isn't detected
  if(!sensor.installed())
  {
    return evAPI::evError::No_Device_In_Port;
  }

  //Map the sensor pointer to the rotation sensor object
  launcherSensor = &sensor;

  launcherSensor->resetPosition();

  return evAPI::evError::No_Error;
}

evAPI::evErrorDouble launcher::getSensorAngle()
{
  //Value to return
  evAPI::evErrorDouble returnValue;

  //Return if the sensor hasn't been created
  if(launcherSensor == nullptr)
  {
    returnValue.errorData = evAPI::evError::No_Device_Defined;
    return returnValue;
  }

  //Return if the sensor isn't installed
  if(!launcherSensor->installed())
  {
    returnValue.errorData = evAPI::evError::No_Device_In_Port;
    return returnValue;
  }

  returnValue.data = launcherSensor->angle(vex::deg);
  return returnValue;
}

evAPI::evError launcher::startThread()
{
  //Exit if the thread already exists
  if(launcherControlThread != nullptr)
  {
    return evAPI::evError::Data_Already_Exists;
  }

  launcherThreadData launcherData;
  launcherData.launcherObject = this;
  launcherData.criticalAngles = &this->criticalAngles;
  launcherData.controllerMappings = &this->controllerMappings;

  //Create the thread
  launcherControlThread = new thread(launcherThread, &launcherData);

  return evAPI::evError::No_Error;
}

void launcher::setLauncherVelocity(double velocity, vex::percentUnits units)
{
  launcherMotors->setVelocity(velocity, units);
}

void launcher::setLauncherVelocity(double velocity, vex::velocityUnits units)
{
  launcherMotors->setVelocity(velocity, units);
}

//!Manual control functions

void launcher::setManualControl(bool mode)
{
  isManualControl = mode;
}

bool launcher::manualControlEnabled()
{
  return isManualControl;
}

void launcher::spinLauncher()
{
  launcherMotors->spin(fwd);
}

void launcher::spinLauncher(double velocity)
{
  launcherMotors->spin(fwd, velocity, vex::percentUnits::pct);
}

void launcher::stopLauncher()
{
  launcherMotors->stop(hold);
}

void launcher::stopLauncher(vex::brakeType mode)
{
  launcherMotors->stop(mode);
}

void launcher::releaseLauncher()
{
  isManualControl = true;
  launcherMotors->stop(coast);
}

//!Critical angle functions

uint launcher::addCriticalAngle(double angle)
{
  //Add the angle to the vector
  criticalAngles.push_back(angle);

  //Return the ID of the added data
  return criticalAngles.size()-1;
}

evAPI::evError launcher::selectCriticalAngle(uint id)
{
  //Return if there isn't any data to select
  if(criticalAngles.size() == 0)
  {
    return evAPI::evError::No_Data_Defined;
  }

  //Return if the index is invalid
  if(criticalAngles.size()-1 > id)
  {
    return evAPI::evError::Index_Out_Of_Range;
  }

  selectedCriticalAngleID = id;

  return evAPI::evError::No_Error;
}

evAPI::evErrorUInt launcher::getCriticalAngleID()
{
  evAPI::evErrorUInt returnData;

  //Return if there isn't any data to select
  if(criticalAngles.size() == 0)
  {
    returnData.errorData = evAPI::evError::No_Data_Defined;
    return returnData;
  }

  returnData.data = selectedCriticalAngleID;

  return returnData;
}

evAPI::evErrorDouble launcher::getCriticalAngle()
{
  evAPI::evErrorDouble returnData;

  //Return if there isn't any data to select
  if(criticalAngles.size() == 0)
  {
    returnData.errorData = evAPI::evError::No_Data_Defined;
    return returnData;
  }

  returnData.data = criticalAngles[selectedCriticalAngleID];

  return returnData;
}

//!Controller mapping functions

evAPI::evError launcher::pairController(vex::controllerType type)
{
  //*Pair the appropriate controller
  if(type == primary)
  {
    //Exit if the controller isn't connected
    if(!primaryController.installed())
    {
      return evAPI::evError::No_Device_In_Port;
    }
  }

  else
  {
    //Exit if the controller isn't connected
    if(!secondaryController.installed())
    {
      return evAPI::evError::No_Device_In_Port;
    }
  }

  mappedController = type;
  controllerPaired = true;

  return evAPI::evError::No_Error;
}

evAPI::evError launcher::mapButton(evAPI::controllerButtons button, evAPI::buttonStatus state, 
                                   launcherActions action, uint data)
{
  //Exit if there isn't a mapped controller
  if(!controllerPaired)
  {
    return evAPI::evError::No_Data_Defined;
  }

  //Exit if the controller isn't connected
  if(!evAPI::typeToController(mappedController).installed())
  {
    return evAPI::evError::No_Device_In_Port;
  }

  //Store mapping data
  controllerMappingData newData;

  newData.controllerButton = button;
  newData.buttonState = state;
  newData.launcherAction = action;
  newData.otherData = data;

  return evAPI::evError::No_Error;
}

//!Private functions

void launcher::launcherInit()
{
  launcherMotors->setMaxTorque(100, vex::percent);
  launcherMotors->setStopping(vex::hold);
}