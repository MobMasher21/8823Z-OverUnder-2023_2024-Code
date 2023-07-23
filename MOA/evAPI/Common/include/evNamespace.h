#ifndef __EVNAMESPACE_H__
#define __EVNAMESPACE_H__ 

//Format Year/Month/Day
#define EVAPI_VERSION 20230613

namespace evAPI
{
  using namespace vex;

  enum allianceMode
  {
    disabled = 0,
    driverControl = 1,
    autonomousControl = 2
  };

  enum robotAlliance
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

  enum leftAndRight //Used for turning functions
  {
    LEFT = 0,
    RIGHT = 1
  };

  const int32_t smartPortLookupTable[22] = {
    0,      PORT1,  PORT2,  PORT3,  PORT4,  PORT5,  PORT6,  PORT7,
    PORT8,  PORT9,  PORT10, PORT11, PORT12, PORT13, PORT14, PORT15,
    PORT16, PORT17, PORT18, PORT19, PORT20, PORT21
  };
}

#endif // __EVNAMESPACE_H__