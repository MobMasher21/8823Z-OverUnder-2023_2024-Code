#ifndef __EVNAMESPACE_H__
#define __EVNAMESPACE_H__ 

#include "../evAPI/Common/include/evAPIBasicConfig.h"

//Format YYYYMMDD
#define EVAPI_VERSION 20230805

namespace evAPI {
  using namespace vex;

  enum robotMode
  {
    disabled = 0,
    driverControl = 1,
    autonomousControl = 2
  };

  enum allianceType
  {
    noAlliance = 0,
    redAlliance = 1,
    blueAlliance = 2
  };

  enum driveBaseType
  {
    /**
     * @brief A H-Drive configuration, with a set of wheels on the left, and another on the right. The wheels
     * are either solid wheels or omniwheels.
    */
    HDriveStandard = 0,

    /**
     * @brief A H-Drive configuration, with a set of wheels on the left, and another on the right. The base
     * uses mecanum wheels. Each wheel has its own motor.
    */
    HDriveMecanum = 1,

    /**
     * @brief An X-Drive configuration, with four wheels all at a 90 degree angle from each other, and 45 
     * degrees from the base.
    */
    XDrive = 2
  };

  enum driveMode
  {
    /**
     * @brief Custom driving mode. Control needs to manually be set up in usercontrol.
    */
    Custom = 0,

    /**
     * @brief The primary stick is used for full control of the robot base. Like an arcade claw machine.
    */
    Arcade = 1,

    /**
     * @brief The left stick controls the left motors, and the right stick controls the right motors.
     * Setting the primary stick is not needed.
    */
    Tank = 2,

    /**
     * @brief A mode that should only be used temporarily during a match. The side to side motion of the
     * primary stick controls the angle the robot faces. Requires an inertial sensor to be set up in
     * odometry.
    */
    ServoSteering = 3,

    /**
     * @brief The primary stick drive the robot forward and backward, with the other in charge of turning it.
    */
    RCControl = 4
  };

  enum joystickType
  {
    leftStick = 0,
    rightStick = 1
  };

  enum class controllerButtons
  {
    L1 = 0,
    L2,
    R1,
    R2,
    A,
    B,
    X,
    Y,
    UP,
    DOWN,
    LEFT,
    RIGHT
  };

  enum class buttonStatus
  {
    Pressed = 0,
    Released,
    Hold_Press,
    Hold_Release
  };

  enum leftAndRight //Used for turning functions
  {
    LEFT = 0,
    RIGHT = 1
  };

  const int32_t smartPortLookupTable[22] = {
    0,      vex::PORT1,  vex::PORT2,  vex::PORT3,  vex::PORT4,  vex::PORT5,  vex::PORT6,  vex::PORT7,
    vex::PORT8,  vex::PORT9,  vex::PORT10, vex::PORT11, vex::PORT12, vex::PORT13, vex::PORT14, vex::PORT15,
    vex::PORT16, vex::PORT17, vex::PORT18, vex::PORT19, vex::PORT20, vex::PORT21
  };

  const vex::gearSetting redGearBox = vex::ratio36_1;
  const vex::gearSetting greenGearBox = vex::ratio18_1;
  const vex::gearSetting blueGearBox = vex::ratio6_1;

}

extern evAPI::allianceType robotAlliance;

#endif // __EVNAMESPACE_H__