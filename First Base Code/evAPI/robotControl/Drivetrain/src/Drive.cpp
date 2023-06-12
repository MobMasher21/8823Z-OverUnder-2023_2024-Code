#include "../../../robotControl/Drivetrain/include/Drive.h"

namespace evAPI
{
  //======================================== public =============================================
  /****** constructors ******/
  Drive::Drive( void ) {
  
  }
  
  Drive::Drive(gearSetting driveGear) {
    currentGear = driveGear;
  }
  
  /************ movement ************/  
  /*----- manual movement -----*/
  void Drive::spinBase(int leftSpeed, int rightSpeed) {
    spinLeftMotors(leftSpeed);
    spinRightMotors(rightSpeed); 
  }
  
  void Drive::stopRobot() {  //stops robot with type coast
    stopLeftMotors(coast);
    stopRightMotors(coast);
  }
  
  void Drive::stopRobot(brakeType stoppingMode) {  //stops robot with given type
    stopLeftMotors(stoppingMode);
    stopRightMotors(stoppingMode);
  }

  /*----- automatic -----*/
  
  //======================================== private =============================================
  /****** formulas ******/
  bool Drive::findDir(int startingAngle, int endingAngle) {
    bool output;
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
  
  int Drive::turnError(bool direction, int startAngle, int endAngle) {
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