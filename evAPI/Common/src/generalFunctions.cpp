#include <math.h>
#include "../include/evAPIBasicConfig.h"
#include "../include/generalFunctions.h"

namespace evAPI
{
  robotMode getCompetitionStatus()
  {
    //*Check the status of the competition, and return the proper robotMode value
    if(!Competition.isEnabled())
    {
      return robotMode::disabled;
    }

    else if(Competition.isDriverControl())
    {
      return robotMode::driverControl;
    }

    return robotMode::autonomousControl;
  }

  bool isConnectToField()
  {
    return Competition.isCompetitionSwitch() || Competition.isFieldControl();
  }

  controller& typeToController(controllerType type)
  {
    if(type == primary)
    {
      return primaryController;
    }

    return secondaryController;
  }

  buttonStatus getButtonStatus(controllerType type, controllerButtons targetButton)
  {
    //Button state variables
    static bool prevButtons[12][2];
    uint8_t controllerSelection = 0;
    bool currentButtonState = false;
    buttonStatus returnStatus;

    //*Select which controller to use
    controller *selectedController;
    
    if(type == primary)
    {
      selectedController = &primaryController;
      controllerSelection = 0;
    }

    else
    {
      selectedController = &secondaryController;
      controllerSelection = 1;
    }

    //*Check the corresponding button
    switch(targetButton)
    {
      case controllerButtons::L1:
        currentButtonState = selectedController->ButtonL1.pressing();
        break;

      case controllerButtons::L2:
        currentButtonState = selectedController->ButtonL2.pressing();
        break;

      case controllerButtons::R1:
        currentButtonState = selectedController->ButtonR1.pressing();
        break;

      case controllerButtons::R2:
        currentButtonState = selectedController->ButtonR2.pressing();
        break;

      case controllerButtons::A:
        currentButtonState = selectedController->ButtonA.pressing();
        break;

      case controllerButtons::B:
        currentButtonState = selectedController->ButtonB.pressing();
        break;

      case controllerButtons::X:
        currentButtonState = selectedController->ButtonX.pressing();
        break;

      case controllerButtons::Y:
        currentButtonState = selectedController->ButtonY.pressing();
        break;

      case controllerButtons::UP:
        currentButtonState = selectedController->ButtonUp.pressing();
        break;

      case controllerButtons::DOWN:
        currentButtonState = selectedController->ButtonDown.pressing();
        break;

      case controllerButtons::LEFT:
        currentButtonState = selectedController->ButtonLeft.pressing();
        break;

      case controllerButtons::RIGHT:
        currentButtonState = selectedController->ButtonRight.pressing();
        break;
    }

    //*Determine the state of the target button
    if(currentButtonState && prevButtons[(int)targetButton][controllerSelection])
    {
      returnStatus = buttonStatus::Hold_Press;
    }

    else if(currentButtonState && !prevButtons[(int)targetButton][controllerSelection])
    {
      returnStatus = buttonStatus::Pressed;
    }

    else if(!currentButtonState && prevButtons[(int)targetButton][controllerSelection])
    {
      returnStatus = buttonStatus::Released;
    }

    else
    {
      returnStatus = buttonStatus::Hold_Release;
    }

    //Store the current state of the button
    prevButtons[(int)targetButton][controllerSelection] = currentButtonState;

    return returnStatus;
  }

  std::string evErrorToString(evError error)
  {
    std::string errorString = "Unhandled_Error";

    //*Select the string to return
    switch(error)
    {
      case evError::No_Error:
        errorString = "No_Error";
        break;

      case evError::No_Motors_Defined:
        errorString = "No_Motors_Defined";
        break;

      case evError::No_Sensor_Defined:
        errorString = "No_Sensor_Defined";
        break;

      case evError::No_Device_Defined:
        errorString = "No_Device_Defined";
        break;

      case evError::No_Device_In_Port:
        errorString = "No_Device_In_Port";
        break;

      case evError::Incorrect_Device_In_Port:
        errorString = "Incorrect_Device_In_Port";
        break;

      case evError::Invalid_Device_In_Port:
        errorString = "Invalid_Device_In_Port";
        break;

      case evError::No_Data_Defined:
        errorString = "No_Data_Defined";
        break;

      case evError::Device_Already_Exists:
        errorString = "Device_Already_Exists";
        break;

      case evError::Data_Already_Exists:
        errorString = "Data_Already_Exists";
        break;

      case evError::Calibration_Already_Complete:
        errorString = "Calibration_Already_Complete";
        break;

      case evError::Invalid_Argument_Data:
        errorString = "Invalid_Argument_Data";
        break;

      case evError::Object_Does_Not_Exist:
        errorString = "Object_Does_Not_Exist";
        break;

      case evError::Object_Property_Not_Specified:
        errorString = "Object_Property_Not_Specified";
        break;

      case evError::Range_Limit_Reached:
        errorString = "Range_Limit_Reached";
        break;

      case evError::Index_Out_Of_Range:
        errorString = "Index_Out_Of_Range";
        break;

      case evError::Object_State_Is_Changing:
        errorString = "Object_State_Is_Changing";
        break;

      case evError::Unknown_Error:
        errorString = "Unknown_Error";
        break;
    }

    return errorString;
  }

  evErrorBool isCorrectDeviceInPort(int32_t port, V5_DeviceType type)
  {
    //Get the current device in the port
    vex::device deviceCheck = vex::device(port);

    //Return data
    evErrorBool returnValue;
    returnValue.data = false;

    //*Return depending on the type of device in the port.
    if(deviceCheck.type() == type)
    {
      returnValue.errorData = evError::No_Error;
      returnValue.data = true;
    }

    else if(deviceCheck.type() == kDeviceTypeNoSensor)
    {
      returnValue.errorData = evError::No_Device_In_Port;
    }

    else if(deviceCheck.type() == kDeviceTypeUndefinedSensor)
    {
      returnValue.errorData = evError::Invalid_Device_In_Port;
    }

    else
    {
      returnValue.errorData = evError::Incorrect_Device_In_Port;
    }

    return returnValue;
  }
}