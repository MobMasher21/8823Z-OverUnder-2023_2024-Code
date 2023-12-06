#include "../include/DriverBaseControl.h"

namespace evAPI {
  /**
   * @brief Construct a new Driver Control object
   * 
   * @param controllerIN A vex controller
   * @param driveTypeIN The type of controlling that will be used
   * @param drivetrainIN The drivetrain that will be controlled
   */
  DriverBaseControl::DriverBaseControl(controller &controllerIN, driveMode driveTypeIN, Drive &drivetrainIN) {
    vexController = &controllerIN;
    driverType = driveTypeIN;
    drivetrain = &drivetrainIN;
  }

  /**
   * @brief Set the Handicaps
   * 
   * @param driveCap Percent power of the drive stick
   * @param turnCap Percent power of the turn stick
   */
  void DriverBaseControl::setHandicaps(int driveCap, int turnCap) {
    driveHandicap = driveCap;
    turnHandicap = turnCap;
  }
  void DriverBaseControl::setHandicaps(int driveCap) {
    driveHandicap = driveCap;
  }

  /**
   * @brief Set the primary stick for drive types that need it
   * 
   * @param primaryStickIN 
   */
  void DriverBaseControl::setPrimaryStick(joystickType primaryStickIN) {
    primaryStick = primaryStickIN;
  }

  /**
   * @brief Called in the main driver contorl loop to drive the base
   * 
   */
  void DriverBaseControl::driverLoop() {
    int leftSpeed;
    int rightSpeed;
    switch (driverType) {
      case Arcade:
        switch (primaryStick) {
          case leftStick:
            leftSpeed = (vexController->Axis3.position(pct) * driveHandicap +
                         vexController->Axis1.position(pct) * turnHandicap);
            rightSpeed = (vexController->Axis3.position(pct) * driveHandicap -
                          vexController->Axis1.position(pct) * turnHandicap);
            break;
          case rightStick:
            leftSpeed = (vexController->Axis2.position(pct) * driveHandicap +
                         vexController->Axis4.position(pct) * turnHandicap);
            rightSpeed = (vexController->Axis2.position(pct) * driveHandicap -
                          vexController->Axis4.position(pct) * turnHandicap);
            break;
        }
        break;
      case Tank:
        leftSpeed = vexController->Axis3.position(pct);
        rightSpeed = vexController->Axis2.position(pct);
      case RCControl:
        switch (primaryStick) {
          case leftStick:
            leftSpeed = (vexController->Axis3.position(pct) * driveHandicap +
                         vexController->Axis4.position(pct) * turnHandicap);
            rightSpeed = (vexController->Axis3.position(pct) * driveHandicap -
                          vexController->Axis4.position(pct) * turnHandicap);
            break;
          case rightStick:
            leftSpeed = (vexController->Axis2.position(pct) * driveHandicap +
                         vexController->Axis1.position(pct) * turnHandicap);
            rightSpeed = (vexController->Axis2.position(pct) * driveHandicap -
                          vexController->Axis1.position(pct) * turnHandicap);
            break;
        }
        break;
    }
    
    if(leftSpeed > 100) leftSpeed = 100;
    if(leftSpeed < -100) leftSpeed = -100;
    if(rightSpeed > 100) rightSpeed = 100;
    if(rightSpeed < -100) rightSpeed = -100;

    drivetrain->spinBase(leftSpeed, rightSpeed);
  }
}