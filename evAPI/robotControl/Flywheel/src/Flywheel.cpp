/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       Flywheel.cpp                                              */
/*    Author:       Jayden Liffick                                            */
/*    Created:      July 22, 2023                                             */
/*    Description:  Cpp file for the flywheel class.                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/Flywheel.h"
#include "../../../Common/include/evNamespace.h"

namespace evAPI
{
  flywheel::flywheel()
  {}

  void flywheel::flywheelSetup(int32_t motorPort, bool reversed)
  { flywheelMotors[0] = new motor(smartPortLookupTable[motorPort], reversed); }

  void flywheel::flywheelSetup(int32_t motorPort, gearSetting gears, bool reversed)
  { flywheelMotors[0] = new motor(smartPortLookupTable[motorPort], gears, reversed); }

  void flywheel::flywheelSetup(int32_t firstMotorPort, int32_t secondMotorPort, bool firstMotorReversed, bool secondMotorReversed)
  {
    flywheelMotors[0] = new motor(smartPortLookupTable[firstMotorPort], firstMotorReversed);
    flywheelMotors[1] = new motor(smartPortLookupTable[secondMotorPort], secondMotorReversed);
    usingSecondMotor = true;
  }

  void flywheel::flywheelSetup(int32_t firstMotorPort, int32_t secondMotorPort, gearSetting firstMotorGears, gearSetting secondMotorMotorGears, bool firstMotorReversed, bool secondMotorReversed)
  {
    flywheelMotors[0] = new motor(smartPortLookupTable[firstMotorPort], firstMotorGears, firstMotorReversed);
    flywheelMotors[1] = new motor(smartPortLookupTable[secondMotorPort], secondMotorMotorGears, secondMotorReversed);
    usingSecondMotor = true;
  }
  
  flywheel::~flywheel()
  {
    delete flywheelMotors[0];

    if(usingSecondMotor)
    { delete flywheelMotors[1]; }
  }

  void flywheel::setVelocity(double velocity, velocityUnits units)
  {
    flywheelMotors[0]->setVelocity(velocity, units);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->setVelocity(velocity, units); }
  }

  void flywheel::setVelocity(double velocity, percentUnits units)
  {
    flywheelMotors[0]->setVelocity(velocity, units);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->setVelocity(velocity, units); }
  }

  void flywheel::spin(directionType dir)
  {
    flywheelMotors[0]->spin(dir);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->spin(dir); }
  }

  void flywheel::spin(directionType dir, double velocity, velocityUnits units)
  {
    flywheelMotors[0]->spin(dir, velocity, units);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->spin(dir, velocity, units); }
  }

  void flywheel::spin(directionType dir, double velocity, percentUnits units)
  {
    flywheelMotors[0]->spin(dir, velocity, units);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->spin(dir, velocity, units); }
  }

  void flywheel::spin(directionType dir, double velocity, voltageUnits units)
  {
    flywheelMotors[0]->spin(dir, velocity, units);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->spin(dir, velocity, units); }
  }

  void flywheel::stop()
  {
    flywheelMotors[0]->stop(coast);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->stop(coast); }
  }

  void flywheel::setMaxTorque(double value, percentUnits units)
  {
    flywheelMotors[0]->setMaxTorque(value, units);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->setMaxTorque(value, units); }
  }

  void flywheel::setMaxTorque(double value, torqueUnits units)
  {
    flywheelMotors[0]->setMaxTorque(value, units);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->setMaxTorque(value, units); }
  }

  void flywheel::setMaxTorque(double value, currentUnits units)
  {
    flywheelMotors[0]->setMaxTorque(value, units);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->setMaxTorque(value, units); }
  }

  directionType flywheel::direction()
  { return flywheelMotors[0]->direction(); }

  double flywheel::velocity(velocityUnits units)
  {
    if(usingSecondMotor)
    { return ((flywheelMotors[0]->velocity(units) + flywheelMotors[1]->velocity(units)) / 2); }

    return flywheelMotors[0]->velocity(units);
  }

  double flywheel::velocity(percentUnits units)
  {
    if(usingSecondMotor)
    { return ((flywheelMotors[0]->velocity(units) + flywheelMotors[1]->velocity(units)) / 2); }

    return flywheelMotors[0]->velocity(units);
  }

  double flywheel::current(currentUnits units)
  {
    if(usingSecondMotor)
    { return ((flywheelMotors[0]->current(units) + flywheelMotors[1]->current(units)) / 2); }

    return flywheelMotors[0]->current(units);
  }

  double flywheel::current(percentUnits units)
  {
    if(usingSecondMotor)
    { return ((flywheelMotors[0]->current(units) + flywheelMotors[1]->current(units)) / 2); }

    return flywheelMotors[0]->current(units);
  }

  double flywheel::voltage(voltageUnits units)
  {
    if(usingSecondMotor)
    { return ((flywheelMotors[0]->voltage(units) + flywheelMotors[1]->voltage(units)) / 2); }

    return flywheelMotors[0]->voltage(units);
  }

  double flywheel::power(powerUnits units)
  {
    if(usingSecondMotor)
    { return (flywheelMotors[0]->power(units) + flywheelMotors[1]->power(units)); }

    return flywheelMotors[0]->power(units);
  }

  double flywheel::torque(torqueUnits units)
  {
    if(usingSecondMotor)
    { return (flywheelMotors[0]->torque(units) + flywheelMotors[1]->torque(units)); }

    return flywheelMotors[0]->torque(units);
  }

  double flywheel::efficiency(percentUnits units)
  {
    if(usingSecondMotor)
    { return ((flywheelMotors[0]->efficiency(units) + flywheelMotors[1]->efficiency(units)) / 2); }

    return flywheelMotors[0]->efficiency(units);
  }

  double flywheel::temperature(temperatureUnits units)
  {
    if(usingSecondMotor)
    { return ((flywheelMotors[0]->temperature(units) + flywheelMotors[1]->temperature(units)) / 2); }

    return flywheelMotors[0]->temperature(units);
  }

  double flywheel::temperature(percentUnits units)
  {
    if(usingSecondMotor)
    { return ((flywheelMotors[0]->temperature(units) + flywheelMotors[1]->temperature(units)) / 2); }

    return flywheelMotors[0]->temperature(units);
  }

} // namespace evAPI