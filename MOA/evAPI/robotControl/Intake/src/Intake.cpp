/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       Intake.h                                                  */
/*    Author:       Jayden Liffick                                            */
/*    Created:      July 22, 2023                                             */
/*    Description:  Cpp file for the intake class.                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/Intake.h"
#include "../../../Common/include/evNamespace.h"


namespace evAPI
{
  intake::intake()
  {}

  void intake::intakeSetup(int32_t motorPort, bool reversed)
  { intakeMotors[0] = new motor(smartPortLookupTable[motorPort], reversed); }

  void intake::intakeSetup(int32_t motorPort, gearSetting gears, bool reversed)
  { intakeMotors[0] = new motor(smartPortLookupTable[motorPort], gears, reversed); }

  void intake::intakeSetup(int32_t firstMotorPort, int32_t secondMotorPort, bool firstMotorReversed, bool secondMotorReversed)
  {
    intakeMotors[0] = new motor(smartPortLookupTable[firstMotorPort], firstMotorReversed);
    intakeMotors[1] = new motor(smartPortLookupTable[secondMotorPort], secondMotorReversed);
    usingSecondMotor = true;
  }

  void intake::intakeSetup(int32_t firstMotorPort, int32_t secondMotorPort, gearSetting firstMotorGears, gearSetting secondMotorMotorGears, bool firstMotorReversed, bool secondMotorReversed)
  {
    intakeMotors[0] = new motor(smartPortLookupTable[firstMotorPort], firstMotorGears, firstMotorReversed);
    intakeMotors[1] = new motor(smartPortLookupTable[secondMotorPort], secondMotorMotorGears, secondMotorReversed);
    usingSecondMotor = true;
  }
  
  intake::~intake()
  {
    delete intakeMotors[0];

    if(usingSecondMotor)
    { delete intakeMotors[1]; }
  }

  void intake::setVelocity(double velocity, velocityUnits units)
  {
    intakeMotors[0]->setVelocity(velocity, units);
    
    if(usingSecondMotor)
    { intakeMotors[1]->setVelocity(velocity, units); }
  }

  void intake::setVelocity(double velocity, percentUnits units)
  {
    intakeMotors[0]->setVelocity(velocity, units);
    
    if(usingSecondMotor)
    { intakeMotors[1]->setVelocity(velocity, units); }
  }

  void intake::spin(directionType dir)
  {
    intakeMotors[0]->spin(dir);
    
    if(usingSecondMotor)
    { intakeMotors[1]->spin(dir); }
  }

  void intake::spin(directionType dir, double velocity, velocityUnits units)
  {
    intakeMotors[0]->spin(dir, velocity, units);
    
    if(usingSecondMotor)
    { intakeMotors[1]->spin(dir, velocity, units); }
  }

  void intake::spin(directionType dir, double velocity, percentUnits units)
  {
    intakeMotors[0]->spin(dir, velocity, units);
    
    if(usingSecondMotor)
    { intakeMotors[1]->spin(dir, velocity, units); }
  }

  void intake::spin(directionType dir, double velocity, voltageUnits units)
  {
    intakeMotors[0]->spin(dir, velocity, units);
    
    if(usingSecondMotor)
    { intakeMotors[1]->spin(dir, velocity, units); }
  }

  void intake::stop()
  {
    intakeMotors[0]->stop();
    
    if(usingSecondMotor)
    { intakeMotors[1]->stop(); }
  }

  void intake::setMaxTorque(double value, percentUnits units)
  {
    intakeMotors[0]->setMaxTorque(value, units);
    
    if(usingSecondMotor)
    { intakeMotors[1]->setMaxTorque(value, units); }
  }

  void intake::setMaxTorque(double value, torqueUnits units)
  {
    intakeMotors[0]->setMaxTorque(value, units);
    
    if(usingSecondMotor)
    { intakeMotors[1]->setMaxTorque(value, units); }
  }

  void intake::setMaxTorque(double value, currentUnits units)
  {
    intakeMotors[0]->setMaxTorque(value, units);
    
    if(usingSecondMotor)
    { intakeMotors[1]->setMaxTorque(value, units); }
  }

  directionType intake::direction()
  { return intakeMotors[0]->direction(); }

  double intake::velocity(velocityUnits units)
  {
    if(usingSecondMotor)
    { return ((intakeMotors[0]->velocity(units) + intakeMotors[1]->velocity(units)) / 2); }

    return intakeMotors[0]->velocity(units);
  }

  double intake::velocity(percentUnits units)
  {
    if(usingSecondMotor)
    { return ((intakeMotors[0]->velocity(units) + intakeMotors[1]->velocity(units)) / 2); }

    return intakeMotors[0]->velocity(units);
  }

  double intake::current(currentUnits units)
  {
    if(usingSecondMotor)
    { return ((intakeMotors[0]->current(units) + intakeMotors[1]->current(units)) / 2); }

    return intakeMotors[0]->current(units);
  }

  double intake::current(percentUnits units)
  {
    if(usingSecondMotor)
    { return ((intakeMotors[0]->current(units) + intakeMotors[1]->current(units)) / 2); }

    return intakeMotors[0]->current(units);
  }

  double intake::voltage(voltageUnits units)
  {
    if(usingSecondMotor)
    { return ((intakeMotors[0]->voltage(units) + intakeMotors[1]->voltage(units)) / 2); }

    return intakeMotors[0]->voltage(units);
  }

  double intake::power(powerUnits units)
  {
    if(usingSecondMotor)
    { return (intakeMotors[0]->power(units) + intakeMotors[1]->power(units)); }

    return intakeMotors[0]->power(units);
  }

  double intake::torque(torqueUnits units)
  {
    if(usingSecondMotor)
    { return (intakeMotors[0]->torque(units) + intakeMotors[1]->torque(units)); }

    return intakeMotors[0]->torque(units);
  }

  double intake::efficiency(percentUnits units)
  {
    if(usingSecondMotor)
    { return ((intakeMotors[0]->efficiency(units) + intakeMotors[1]->efficiency(units)) / 2); }

    return intakeMotors[0]->efficiency(units);
  }

  double intake::temperature(temperatureUnits units)
  {
    if(usingSecondMotor)
    { return ((intakeMotors[0]->temperature(units) + intakeMotors[1]->temperature(units)) / 2); }

    return intakeMotors[0]->temperature(units);
  }

  double intake::temperature(percentUnits units)
  {
    if(usingSecondMotor)
    { return ((intakeMotors[0]->temperature(units) + intakeMotors[1]->temperature(units)) / 2); }

    return intakeMotors[0]->temperature(units);
  }
}
