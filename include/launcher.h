/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       launcher.h                                                */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Jan 29, 2024                                              */
/*    Description:  Launcher class for managing catapults and punchers        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "../evAPI/Common/include/evErrorTypes.h"
#include "../evAPI/Common/include/evNamespace.h"
#include "vex.h"
#include <vector>

class launcher
{
  public:
    /**
     * @brief Creates a new launcher object.
     * @param motor The motor the launcher uses.
    */
    launcher(vex::motor &motor);

    /**
     * @brief Creates a new launcher object.
     * @param motors A motor group containing the motors for the launcher.
    */
    launcher(vex::motor_group &motors);

    ~launcher();

    /**
     * @brief Adds a rotation sensor. Allows the launcher to automatically set its position
     *        after firing.
     * @param sensor A rotation sensor object.
     * @returns An evError. No_Device_In_Port if there aren't any devices in the port.
     *          Incorrect_Device_In_Port if the device in the port isn't a rotation sensor.
     *          No_Error if there aren't any errors.
     * @warning The launcher should be set to a predictable state when this function is called.
     *          If the launcher is set inconstantly, the launcher won't be able to consistently move
     *          to the specified critical angles.
    */
    evAPI::evError addSensor(vex::rotation &sensor);

    /**
     * @brief Gets the angle of the sensor if it exists.
     * @returns An evErrorDouble containing the error and the angle.
     *          No_Device_Defined if the sensor hasn't been created.
     *          No_Device_In_Port if the sensor isn't in the port.
     *          No_Error if there aren't any errors.
    */
    evAPI::evErrorDouble getSensorAngle();

    /**
     * @brief Starts the managing thread for the launcher.
     * @returns An evError. Data_Already_Exists if the thread was already created.
     *          No_Error if there aren't any errors.
    */
    evAPI::evError startThread();

    /**
     * @brief Sets the velocity of the launcher.
     * @param velocity The velocity of the motor(s).
     * @param units Optional. Units for the velocity of the motor(s).
    */
    void setLauncherVelocity(double velocity, vex::percentUnits units = vex::percentUnits::pct);

    /**
     * @brief Sets the velocity of the launcher.
     * @param velocity The velocity of the motor(s).
     * @param units Optional. Units for the velocity of the motor(s).
    */
    void setLauncherVelocity(double velocity, vex::velocityUnits units = vex::velocityUnits::pct);

    //!Manual control Functions

    /**
     * @brief Enables or disables manual control of the launcher.
     * @param mode A boolean controlling manual control mode.
    */
    void setManualControl(bool mode);

    /**
     * @returns True if manual control mode is enabled.
    */
    bool manualControlEnabled();

    /**
     * @brief Spins the launcher motor(s).
     * @attention Manual control mode needs to be enabled in order for this function to do anything.
    */
    void spinLauncher();

    /**
     * @brief Spins the launcher motor(s) at a specified speed.
     * @param velocity The velocity of the motor(s) in pct.
     * @attention Manual control mode needs to be enabled in order for this function to do anything.
    */
    void spinLauncher(double velocity);

    /**
     * @brief Stops the launcher motor(s).
     * @attention Manual control mode needs to be enabled in order for this function to do anything.
    */
    void stopLauncher();

    /**
     * @brief Stops the launcher motor(s) with a specified mode.
     * @param mode The stopping mode for the motor(s).
     * @attention Manual control mode needs to be enabled in order for this function to do anything.
    */
    void stopLauncher(vex::brakeType mode);

    /**
     * @brief Stops the launch with coast, allowing it to reset itself.
     * @attention This function enabled manual control mode. You will need to disable it in order
     *            for the critical angles to work.
    */
    void releaseLauncher();

    //!Critical angle functions

    /**
     * @brief Adds a critical angle to the launcher.
     * @param angle The critical angle value in degrees.
     * @returns The ID of the critical angle.
    */
    uint addCriticalAngle(double angle);

    /**
     * @brief Selects a critical angle given its ID.
     * @param id The ID of the critical angle.
     * @returns An evError. No_Data_Defined if there aren't any critical angles.
     *          Index_Out_Of_Range if the ID is invalid.
     *          No_Error if there aren't any errors.
    */
    evAPI::evError selectCriticalAngle(uint id);

    /**
     * @brief Gets the ID of the selected critical angle.
     * @returns An evErrorUint containing the error and ID.
     *          No_Data_Defined if there aren't any critical angles.
     *          No_Error if there aren't any errors.
    */
    evAPI::evErrorUInt getCriticalAngleID();

    /**
     * @brief Gets the value of the selected critical angle.
     * @returns An evErrorDouble containing the error and critical angle.
     *          No_Data_Defined if there aren't any critical angles.
     *          No_Error if there aren't any errors.
    */
    evAPI::evErrorDouble getCriticalAngle();

    //!Controller mapping functions

    enum launcherActions
    {
      //Activates the launcher.
      CONTROLLER_LAUNCH = 0,

      //Stops the launcher.
      CONTROLLER_STOP,

      //Force releases the launcher, also disabling automatic mode.
      CONTROLLER_FORCE_RELEASE,

      //Selects the critical angle ID from the optional "data" argument.
      CONTROLLER_SET_CRITICAL,

      //Increments the selected critical angle ID by 1.
      CONTROLLER_INCREMENT_CRITICAL,

      //Toggles manual mode.
      CONTROLLER_TOGGLE_MANUAL
    };

    /**
     * @brief Connects the launcher object with a controller, allowing for buttons to be directly
     *        mapped to actions in the launcher.
     * @param type The type of controller to get data from.
     * @returns An evError. No_Device_In_Port if the controller isn't connected.
     *          No_Error if there aren't any errors.
    */
    evAPI::evError pairController(vex::controllerType type);
    
    /**
     * @brief Gets the type of controller paired to the launcher, if there is one.
     * @returns An evErrorData object with vex::controllerType as the data.
     *          No_Device_Defined if there isn't a controller connected with the launcher
     *          No_Error if there aren't any errors.
    */
    evAPI::evErrorData<controllerType> getControllerType();

    /**
     * @brief Maps the button on a controller to an action for the launcher.
     * @param button The button to map the action to.
     * @param state The state the button needs to be in.
     * @param action The action to take when the button is triggered.
     * @param data Extra data needed for some actions.
     * @returns An evError. No_Data_Defined if there isn't a controller paired to the launcher.
     *          No_Device_In_Port if the controller isn't connected to the robot.
     *          No_Error if their aren't any errors.
    */
    evAPI::evError mapButton(evAPI::controllerButtons button, evAPI::buttonStatus state, 
                             launcherActions action, uint data = 0);

    struct controllerMappingData
    {
      evAPI::controllerButtons controllerButton;
      evAPI::buttonStatus buttonState;
      launcherActions launcherAction;
      uint otherData;
    };

  private:
    //Catapult hardware
    vex::motor_group *launcherMotors = nullptr;
    vex::rotation *launcherSensor = nullptr;

    //Main control thread
    vex::thread *launcherControlThread = nullptr;

    //Critical Angles
    std::vector<double> criticalAngles;
    uint selectedCriticalAngleID = 0;
    bool isManualControl = true;

    //Controller mappings
    controllerType mappedController;
    bool controllerPaired = false;

    std::vector<controllerMappingData> controllerMappings;

    void launcherInit();
};

#endif // LAUNCHER_H