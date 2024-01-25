#include "../../../robotControl/Drivetrain/include/Drive.h"

namespace evAPI {
  //======================================== private =============================================
  /****** encoders ******/
  void Drive::leftFullReset() {  //resets all position data about left encoder
    leftDrivePositionOffset = 0;
    leftOdoPositionOffset = 0;
    if(!leftEncoder) {
      leftMotor1->resetPosition();
    } else {
      leftEncoder->resetPosition();
    }
  }

  void Drive::rightFullReset() {  //resets all position data about right encoder
    rightDrivePositionOffset = 0;
    rightOdoPositionOffset = 0;
    if(!rightEncoder) {
      rightMotor1->resetPosition();
    } else {
      rightEncoder->resetPosition();
    }
  }

  //======================================== private =============================================
  /****** encoders ******/
  double Drive::getLeftDrivePosition(rotationUnits units) {  //get the position of the left side on motor or rotation sensor for drive actions
    if(!leftEncoder) {
      return(leftMotor1->position(units) - leftDrivePositionOffset);
    } else {
      return(leftEncoder->position(units) - leftDrivePositionOffset);
    }
  }

  double Drive::getLeftOdoPosition(rotationUnits units) {  //get the position of the left side on motor or rotation sensor for odo actions
    if(!leftEncoder) {
      return(leftMotor1->position(units) - leftOdoPositionOffset);
    } else {
      return(leftEncoder->position(units) - leftOdoPositionOffset);
    }
  }

  double Drive::getRightDrivePosition(rotationUnits units) {  //get the position of the right side on motor or rotation sensor for drive actions
    if(!rightEncoder) {
      return(rightMotor1->position(units) - rightDrivePositionOffset);
    } else {
      return(rightEncoder->position(units) - rightDrivePositionOffset);
    }
  }

  double Drive::getRightOdoPosition(rotationUnits units) {  //get the position of the right side on motor or rotation sensor for odo actions
    if(!rightEncoder) {
      return(rightMotor1->position(units) - rightOdoPositionOffset);
    } else {
      return(rightEncoder->position(units) - rightOdoPositionOffset);
    }
  }

  double Drive::getBackPosition(rotationUnits units) {    //get the position of the back side on motor or rotation sensor
    if(backEncoder) {
      return(backEncoder->position(units));
    } else {
      return(0);
    }
  }

  void Drive::resetLeftDrivePosition() {    //resets position of left encoder to 0 for drive actions
    if(!leftEncoder) {
      leftDrivePositionOffset = leftMotor1->position(deg);
    } else {
      leftDrivePositionOffset = leftEncoder->position(deg);
    }
  }

  void Drive::resetLeftOdoPosition() {    //resets position of left encoder to 0 for odo actions
    if(!leftEncoder) {
      leftOdoPositionOffset = leftMotor1->position(deg);
    } else {
      leftOdoPositionOffset = leftEncoder->position(deg);
    }
  }

  void Drive::resetRightDrivePosition() {    //resets position of right encoder to 0 for drive actions
    if(!leftEncoder) {
      rightDrivePositionOffset = rightMotor1->position(deg);
    } else {
      rightDrivePositionOffset = rightEncoder->position(deg);
    }
  }

  void Drive::resetRightOdoPosition() {    //resets position of right encoder to 0 for odo actions
    if(!leftEncoder) {
      rightOdoPositionOffset = rightMotor1->position(deg);
    } else {
      rightOdoPositionOffset = rightEncoder->position(deg);
    }
  }

  void Drive::resetBackPosition() {    //resets position of back encoder to 0
    if(backEncoder) {
      backEncoder->resetPosition();
    }
  }

}