#include "../../../robotControl/Drivetrain/include/Drive.h"

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