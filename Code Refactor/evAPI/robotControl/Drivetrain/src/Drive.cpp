#include "../../../robotControl/Drivetrain/include/Drive.h"
#include "../../../Common/include/Controllers.h"

namespace evAPI
{
  //======================================== public =============================================
  /****** constructors ******/
  drive::drive( void ) {
  
  }
  
  drive::drive(gearSetting driveGear) {
    currentGear = driveGear;
  }
  
  /************ movement ************/  
  /*----- manual movement -----*/
  void drive::spinBase(int leftSpeed, int rightSpeed) {
    spinLeftMotors(leftSpeed);
    spinRightMotors(rightSpeed); 
  }
  
  void drive::stopRobot() {  //stops robot with type coast
    stopLeftMotors(coast);
    stopRightMotors(coast);
  }
  
  void drive::stopRobot(brakeType stoppingMode) {  //stops robot with given type
    stopLeftMotors(stoppingMode);
    stopRightMotors(stoppingMode);
  }

  void drive::controllerDrive()
  {
    switch(driverMode)
    {
      case Custom:
        break;

      case Arcade:
        switch(baseType)
        {
          case HDriveStandard:
            double leftSpeed;
            double rightSpeed;

            switch(primaryControllerStick)
            {
              case leftStick:
                leftSpeed = (primaryController.Axis3.position(pct) + primaryController.Axis4.position(pct)
                  * turnHandicap) * generalHandicap;

                rightSpeed = (primaryController.Axis3.position(pct) - primaryController.Axis4.position(pct)
                  * turnHandicap) * generalHandicap;
                break;

              case rightStick:
                leftSpeed = (primaryController.Axis2.position(pct) + primaryController.Axis1.position(pct)
                  * turnHandicap) * generalHandicap;

                rightSpeed = (primaryController.Axis2.position(pct) - primaryController.Axis1.position(pct)
                  * turnHandicap) * generalHandicap;

                break;

            }
            spinBase(leftSpeed, rightSpeed);
            break;

          case HDriveMecanum:
            switch(primaryControllerStick)
            {
              case leftStick:
    
                break;
    
              case rightStick:
    
                break;
            }
            break;

          case XDrive:
            switch(primaryControllerStick)
            {
              case leftStick:
    
                break;
    
              case rightStick:
    
                break;
            }
            break;
        }

        break;

      case Tank:
        switch(baseType)
        {
          case HDriveStandard:
            switch(primaryControllerStick)
            {
              case leftStick:

                break;

              case rightStick:

                break;
            }
            break;

          case HDriveMecanum:
            switch(primaryControllerStick)
            {
              case leftStick:
    
                break;
    
              case rightStick:
    
                break;
            }
            break;

          case XDrive:
            switch(primaryControllerStick)
            {
              case leftStick:
    
                break;
    
              case rightStick:
    
                break;
            }
            break;
        }
        break;

      case ServoSteering:
        switch(baseType)
        {
          case HDriveStandard:
            switch(primaryControllerStick)
            {
              case leftStick:

                break;

              case rightStick:

                break;
            }
            break;

          case HDriveMecanum:
            switch(primaryControllerStick)
            {
              case leftStick:
    
                break;
    
              case rightStick:
    
                break;
            }
            break;

          case XDrive:
            switch(primaryControllerStick)
            {
              case leftStick:
    
                break;
    
              case rightStick:
    
                break;
            }
            break;
        }

        break;

      case RCControl:
        switch(baseType)
        {
          case HDriveStandard:
            double leftSpeed;
            double rightSpeed;

            switch(primaryControllerStick)
            {
              case leftStick:
                leftSpeed = (primaryController.Axis3.position(pct) + primaryController.Axis1.position(pct)
                  * turnHandicap) * generalHandicap;

                rightSpeed = (primaryController.Axis3.position(pct) - primaryController.Axis1.position(pct)
                  * turnHandicap) * generalHandicap;
                break;

              case rightStick:
                leftSpeed = (primaryController.Axis2.position(pct) + primaryController.Axis4.position(pct)
                  * turnHandicap) * generalHandicap;

                rightSpeed = (primaryController.Axis2.position(pct) - primaryController.Axis4.position(pct)
                  * turnHandicap) * generalHandicap;

                break;

            }
            spinBase(leftSpeed, rightSpeed);
            break;

          case HDriveMecanum:
            switch(primaryControllerStick)
            {
              case leftStick:

                break;

              case rightStick:

                break;
            }
            break;

          case XDrive:
            switch(primaryControllerStick)
            {
              case leftStick:
    
                break;
    
              case rightStick:
    
                break;
            }
            break;
        }
        break;
    }
  }

  /*----- automatic -----*/
  
  //======================================== private =============================================
  /****** formulas ******/
  leftAndRight drive::findDir(int startingAngle, int endingAngle) {
    leftAndRight output;
    int leftDegs;
    int rightDegs;
    int x;  //starting angle + 360
    //left turn
    x = startingAngle + 360;
    if(x - endingAngle > 360) {
      x = startingAngle;
    }
    leftDegs = x - endingAngle;
    //right turn
    x = endingAngle + 360;
    if(x - startingAngle > 360) {
      x = endingAngle;
    }
    rightDegs = x - startingAngle;
    //return lines
    if(leftDegs > rightDegs) {
      output = RIGHT;
    } else {
      output = LEFT;
    }
    return(output);
  }
  
  int drive::turnError(leftAndRight direction, int startAngle, int endAngle) {
    int turnError = 0;
    if(direction == LEFT) {
    
      //===============================LEFT
      if(((startAngle + 360) - endAngle) > 180) {
        if(startAngle - endAngle < 180) {
          turnError = startAngle - endAngle;
        } else if(startAngle - endAngle > 180) {
          turnError = (startAngle - endAngle) - 360;
        }
      } else if(((startAngle + 360) - endAngle) < 180) {
        turnError = (startAngle + 360) - endAngle;
      }  
    } else if(direction == RIGHT) {
    
      //===============================RIGHT
      if(((endAngle + 360) - startAngle) > 180) {
        if(endAngle - startAngle < 180) {
          turnError = endAngle - startAngle;
        } else if(endAngle - startAngle > 180) {
          turnError = (endAngle - startAngle) - 360;
        }
      } else if(((endAngle + 360) - startAngle) < 180) {
        turnError = (endAngle + 360) - startAngle;
      }
      //===============================
    }
  
    return(turnError);
  }
}