#ifndef _FLYWHEEL_H_
#define _FLYWHEEL_H_

#include "vex.h"

namespace evAPI
{
  #define minFlywheelSpeed 20
  #define minFlywheelSpeedVoltage (12 * (.01 * minFlywheelSpeed))
  
  class flywheel {
    public:
      /****** setup ******/
      void setGearbox(gearSetting gearType);  //sets the gearbox for both flywheel motors
      void setupMotors(int motor1Port, bool reverse1);  //sets up one motor
      void setupMotors(int motor1Port, bool reverse1, int motor2Port, bool reverse2);  //sets up two motors
  
      /****** direct movement contorl ******/
      void spinFlywheel(double speed);  //spins both flywheel motors
      void stopFlywheel();  //stops the motors in coast
      void TBHUpdate(int speed);
  
      /*----- sensing -----*/
      double velocity( void );    //Gets the current rotation speed of the flywheel
  
    private:
      /****** motor pointer ******/
      gearSetting flywheelGearbox;
      motor * flywheelMotor1;
      motor * flywheelMotor2;
  
      /****** variables ******/
      //int flywheelSpeed;
  
  };

  extern flywheel Flywheel;
}

#endif //_FLYWHEEL_H_