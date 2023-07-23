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
  Flywheel::Flywheel(int32_t motorPort, bool reversed)
  { flywheelMotors[0] = new motor(motorPort, reversed); }

  Flywheel::Flywheel(int32_t motorPort, gearSetting gears, bool reversed)
  { flywheelMotors[0] = new motor(motorPort, gears, reversed); }

  Flywheel::Flywheel(int32_t firstMotorPort, int32_t secondMotorPort, bool firstMotorReversed, bool secondMotorReversed)
  {
    flywheelMotors[0] = new motor(firstMotorPort, firstMotorReversed);
    flywheelMotors[1] = new motor(secondMotorPort, secondMotorReversed);
    usingSecondMotor = true;
  }

  Flywheel::Flywheel(int32_t firstMotorPort, int32_t secondMotorPort, gearSetting firstMotorGears, gearSetting secondMotorMotorGears, bool firstMotorReversed, bool secondMotorReversed)
  {
    flywheelMotors[0] = new motor(firstMotorPort, firstMotorGears, firstMotorReversed);
    flywheelMotors[1] = new motor(secondMotorPort, secondMotorMotorGears, secondMotorReversed);
    usingSecondMotor = true;
  }
  
  Flywheel::~Flywheel()
  {
    delete flywheelMotors[0];

    if(usingSecondMotor)
    { delete flywheelMotors[1]; }
  }

  void Flywheel::setVelocity(double velocity, velocityUnits units)
  {
    flywheelMotors[0]->setVelocity(velocity, units);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->setVelocity(velocity, units); }
  }

  void Flywheel::setVelocity(double velocity, percentUnits units)
  {
    flywheelMotors[0]->setVelocity(velocity, units);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->setVelocity(velocity, units); }
  }

  void Flywheel::spin(directionType dir)
  {
    flywheelMotors[0]->spin(dir);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->spin(dir); }
  }

  void Flywheel::spin(directionType dir, double velocity, velocityUnits units)
  {
    flywheelMotors[0]->spin(dir, velocity, units);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->spin(dir, velocity, units); }
  }

  void Flywheel::spin(directionType dir, double velocity, percentUnits units)
  {
    flywheelMotors[0]->spin(dir, velocity, units);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->spin(dir, velocity, units); }
  }

  void Flywheel::spin(directionType dir, double velocity, voltageUnits units)
  {
    flywheelMotors[0]->spin(dir, velocity, units);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->spin(dir, velocity, units); }
  }

  void Flywheel::stop()
  {
    flywheelMotors[0]->stop();
    
    if(usingSecondMotor)
    { flywheelMotors[1]->stop(); }
  }

  void Flywheel::setMaxTorque(double value, percentUnits units)
  {
    flywheelMotors[0]->setMaxTorque(value, units);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->setMaxTorque(value, units); }
  }

  void Flywheel::setMaxTorque(double value, torqueUnits units)
  {
    flywheelMotors[0]->setMaxTorque(value, units);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->setMaxTorque(value, units); }
  }

  void Flywheel::setMaxTorque(double value, currentUnits units)
  {
    flywheelMotors[0]->setMaxTorque(value, units);
    
    if(usingSecondMotor)
    { flywheelMotors[1]->setMaxTorque(value, units); }
  }

  directionType Flywheel::direction()
  { return flywheelMotors[0]->direction(); }

  double Flywheel::velocity(velocityUnits units)
  {
    if(usingSecondMotor)
    { return ((flywheelMotors[0]->velocity(units) + flywheelMotors[1]->velocity(units)) / 2); }

    return flywheelMotors[0]->velocity(units);
  }

  double Flywheel::velocity(percentUnits units)
  {
    if(usingSecondMotor)
    { return ((flywheelMotors[0]->velocity(units) + flywheelMotors[1]->velocity(units)) / 2); }

    return flywheelMotors[0]->velocity(units);
  }

  double Flywheel::current(currentUnits units)
  {
    if(usingSecondMotor)
    { return ((flywheelMotors[0]->current(units) + flywheelMotors[1]->current(units)) / 2); }

    return flywheelMotors[0]->current(units);
  }

  double Flywheel::current(percentUnits units)
  {
    if(usingSecondMotor)
    { return ((flywheelMotors[0]->current(units) + flywheelMotors[1]->current(units)) / 2); }

    return flywheelMotors[0]->current(units);
  }

  double Flywheel::voltage(voltageUnits units)
  {
    if(usingSecondMotor)
    { return ((flywheelMotors[0]->voltage(units) + flywheelMotors[1]->voltage(units)) / 2); }

    return flywheelMotors[0]->voltage(units);
  }

  double Flywheel::power(powerUnits units)
  {
    if(usingSecondMotor)
    { return (flywheelMotors[0]->power(units) + flywheelMotors[1]->power(units)); }

    return flywheelMotors[0]->power(units);
  }

  double Flywheel::torque(torqueUnits units)
  {
    if(usingSecondMotor)
    { return (flywheelMotors[0]->torque(units) + flywheelMotors[1]->torque(units)); }

    return flywheelMotors[0]->torque(units);
  }

  double Flywheel::efficiency(percentUnits units)
  {
    if(usingSecondMotor)
    { return ((flywheelMotors[0]->efficiency(units) + flywheelMotors[1]->efficiency(units)) / 2); }

    return flywheelMotors[0]->efficiency(units);
  }

  double Flywheel::temperature(temperatureUnits units)
  {
    if(usingSecondMotor)
    { return ((flywheelMotors[0]->temperature(units) + flywheelMotors[1]->temperature(units)) / 2); }

    return flywheelMotors[0]->temperature(units);
  }

  double Flywheel::temperature(percentUnits units)
  {
    if(usingSecondMotor)
    { return ((flywheelMotors[0]->temperature(units) + flywheelMotors[1]->temperature(units)) / 2); }

    return flywheelMotors[0]->temperature(units);
  }

} // namespace evAPI