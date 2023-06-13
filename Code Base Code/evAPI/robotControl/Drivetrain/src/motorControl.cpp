#include "../../../robotControl/Drivetrain/include/Drive.h"

namespace evAPI
{
  //======================================== private =============================================
  /************ motors ************/
  /*----- left motors -----*/
  void Drive::spinLeftMotors(int speed) {  //spins all motors on the left side
    switch(baseMotorCount){
      case 2:
        leftMotor1->spin(fwd, speed, percent);
        break;
      case 4:
        leftMotor1->spin(fwd, speed, percent);
        leftMotor2->spin(fwd, speed, percent);
        break;
      case 6:
        leftMotor1->spin(fwd, speed, percent);
        leftMotor2->spin(fwd, speed, percent);
        leftMotor3->spin(fwd, speed, percent);
        break;
      case 8:
        leftMotor1->spin(fwd, speed, percent);
        leftMotor2->spin(fwd, speed, percent);
        leftMotor3->spin(fwd, speed, percent);
        leftMotor4->spin(fwd, speed, percent);
        break;
    }
  }
  
  void Drive::stopLeftMotors(brakeType type) {  //stop all motors on the left side
    switch(baseMotorCount){
      case 2:
        leftMotor1->stop(type);
        break;
      case 4:
        leftMotor1->stop(type);
        leftMotor2->stop(type);
        break;
      case 6:
        leftMotor1->stop(type);
        leftMotor2->stop(type);
        leftMotor3->stop(type);
        break;
      case 8:
        leftMotor1->stop(type);
        leftMotor2->stop(type);
        leftMotor3->stop(type);
        leftMotor4->stop(type);
        break;
    }
  }
  
  /*----- right motors -----*/
  void Drive::spinRightMotors(int speed) {  //spins all motors on the right side
    switch(baseMotorCount){
      case 2:
        rightMotor1->spin(fwd, speed, percent);
        break;
      case 4:
        rightMotor1->spin(fwd, speed, percent);
        rightMotor2->spin(fwd, speed, percent);
        break;
      case 6:
        rightMotor1->spin(fwd, speed, percent);
        rightMotor2->spin(fwd, speed, percent);
        rightMotor3->spin(fwd, speed, percent);
        break;
      case 8:
        rightMotor1->spin(fwd, speed, percent);
        rightMotor2->spin(fwd, speed, percent);
        rightMotor3->spin(fwd, speed, percent);
        rightMotor4->spin(fwd, speed, percent);
        break;
    }
  }
  
  void Drive::stopRightMotors(brakeType type) {  //stop all motors on the right side
    switch(baseMotorCount){
      case 2:
        rightMotor1->stop(type);
        break;
      case 4:
        rightMotor1->stop(type);
        rightMotor2->stop(type);
        break;
      case 6:
        rightMotor1->stop(type);
        rightMotor2->stop(type);
        rightMotor3->stop(type);
        break;
      case 8:
        rightMotor1->stop(type);
        rightMotor2->stop(type);
        rightMotor3->stop(type);
        rightMotor4->stop(type);
        break;
    }
  }
}