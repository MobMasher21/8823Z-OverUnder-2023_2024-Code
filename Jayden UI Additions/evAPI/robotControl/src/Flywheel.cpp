#include "../../robotControl/include/Flywheel.h"
#include "../../Common/include/generalFunctions.h"
#include "../../Common/include/robotStatus.h"
#include "../../Common/include/evNamespace.h"

namespace evAPI
{
  flywheel Flywheel;

  void flywheel::setGearbox(gearSetting gearType) {  //sets the gearbox for both flywheel motors
    flywheelGearbox = gearType;
  }
  
  void flywheel::setupMotors(int motor1Port, bool reverse1) {  //sets up one motor
    flywheelMotor1 = new motor(smartPortLookupTable[motor1Port], flywheelGearbox, reverse1);
  }
  
  void flywheel::setupMotors(int motor1Port, bool reverse1, int motor2Port, bool reverse2) {  //sets up two motors
    flywheelMotor1 = new motor(smartPortLookupTable[motor1Port], flywheelGearbox, reverse1);
    flywheelMotor2 = new motor(smartPortLookupTable[motor2Port], flywheelGearbox, reverse2);
  }
  
  void flywheel::spinFlywheel(double speed) {  //spins both flywheel motors
  
    //Limits the voltage to between "minFlywheelSpeedVoltage" and 12.
    speed = constrain(speed, minFlywheelSpeedVoltage, 12);
  
    if(flywheelMotor1) {
      flywheelMotor1->spin(fwd, speed, voltageUnits::volt);
    }
    if(flywheelMotor2) {
      flywheelMotor2->spin(fwd, speed, voltageUnits::volt);
    }
    //printf("%f, %f, %f, %f\n", flywheelMotor1->velocity(pct), flywheelMotor2->velocity(pct), flywheelMotor1->current(), flywheelMotor2->current());
  }
  
  void flywheel::stopFlywheel() {  //stops the motors in coast
    if(flywheelMotor1) {
      flywheelMotor1->stop(coast);
    }
    if(flywheelMotor2) {
      flywheelMotor2->stop(coast);
    }
  }
  
  double flywheel::velocity( void )    //gets the current rotation speed of the motor
  {
    double velocity1 = 0;
    double velocity2 = 0;
    
    if(flywheelMotor1) {
      velocity1 = flywheelMotor1->velocity(pct);
    }
    if(flywheelMotor2) {
      velocity2 = flywheelMotor2->velocity(pct);
    }
  
    if(velocity2 == 0)
    { velocity2 = velocity1; }
  
    if(velocity1 == 0)
    { velocity1 = velocity2; }
  
    return ((velocity1 + velocity2)/2);
  }
  
  void flywheel::TBHUpdate(int speed)
  {
    double error;
    double prevError = 0;
    double output;
    double tbh = 0;
    #define kI 0.1
  
    if(flywheelMotor1->velocity(pct) > 0)
    {
      error = speed - flywheelMotor1->velocity(pct);
      output = kI * error;
    
      if(signbit(error) != signbit(prevError))
      {
        output = 0.5 * (output + tbh);
        tbh = output;
      }
  
      spinFlywheel(output);
  
      prevError = error;
      
      /* output = output > 12? 12 : output;
  
      if(flywheelMotor1->velocity() < minSpeed)
      { spinFlywheel(12); }
  
      else
      { spinFlywheel(output); } */
    }
  }
  #undef kI
}