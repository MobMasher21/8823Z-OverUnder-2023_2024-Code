#include "../../../robotControl/Drivetrain/include/Drive.h"

namespace evAPI {
  //======================================== private =============================================
  /****** encoders ******/
  double Drive::getLeftPosition(rotationUnits units) {    //get the position of the left side on motor or rotation sensor
    if(!leftEncoder) {
      return(leftMotor1->position(units));
    } else {
      return(leftEncoder->position(units));
    }
  }

  double Drive::getRightPosition(rotationUnits units) {    //get the position of the right side on motor or rotation sensor
    if(!rightEncoder) {
      return(rightMotor1->position(units));
    } else {
      return(rightEncoder->position(units));
    }
  }

  double Drive::getBackPosition(rotationUnits units) {    //get the position of the back side on motor or rotation sensor
    if(backEncoder) {
      return(backEncoder->position(units));
    } else {
      return(0);
    }
  }

  void Drive::resetLeftPosition() {    //resets position of left encoder to 0
    if(!leftEncoder) {
      leftMotor1->resetPosition();
    } else {
      leftEncoder->resetPosition();
    }
  }

  void Drive::resetRightPosition() {    //resets position of right encoder to 0
    if(!leftEncoder) {
      leftMotor1->resetPosition();
    } else {
      leftEncoder->resetPosition();
    }
  }

  void Drive::resetBackPosition() {    //resets position of back encoder to 0
    if(backEncoder) {
      backEncoder->resetPosition();
    }
  }

}