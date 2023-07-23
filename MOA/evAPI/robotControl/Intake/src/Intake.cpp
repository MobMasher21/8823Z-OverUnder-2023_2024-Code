/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       Intake.h                                                  */
/*    Author:       Jayden Liffick                                            */
/*    Created:      July 22, 2023                                             */
/*    Description:  Cpp file for the intake class.                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/Intake.h"

namespace evAPI
{
  Intake::Intake(int32_t motorPort, bool reversed)
  { intakeMotors[0] = new motor(motorPort, reversed); }

  Intake::Intake(int32_t motorPort, gearSetting gears, bool reversed)
  { intakeMotors[0] = new motor(motorPort, gears, reversed); }

  Intake::Intake(int32_t firstMotorPort, int32_t secondMotorPort, bool firstMotorReversed, bool secondMotorReversed)
  {
    intakeMotors[0] = new motor(firstMotorPort, firstMotorReversed);
    intakeMotors[1] = new motor(secondMotorPort, secondMotorReversed);
    usingSecondMotor = true;
  }

  Intake::Intake(int32_t firstMotorPort, int32_t secondMotorPort, gearSetting firstMotorGears, gearSetting secondMotorMotorGears, bool firstMotorReversed, bool secondMotorReversed)
  {
    intakeMotors[0] = new motor(firstMotorPort, firstMotorGears, firstMotorReversed);
    intakeMotors[1] = new motor(secondMotorPort, secondMotorMotorGears, secondMotorReversed);
    usingSecondMotor = true;
  }
  
  Intake::~Intake()
  {
    delete intakeMotors[0];

    if(usingSecondMotor)
    { delete intakeMotors[1]; }
  }

  void Intake::setVelocity(double velocity, velocityUnits units)
  {
    intakeMotors[0]->setVelocity(velocity, units);
    
    if(usingSecondMotor)
    { intakeMotors[1]->setVelocity(velocity, units); }
  }

  void Intake::setVelocity(double velocity, percentUnits units)
  {
    intakeMotors[0]->setVelocity(velocity, units);
    
    if(usingSecondMotor)
    { intakeMotors[1]->setVelocity(velocity, units); }
  }

  void Intake::spin(directionType dir)
  {
    intakeMotors[0]->spin(dir);
    
    if(usingSecondMotor)
    { intakeMotors[1]->spin(dir); }
  }

  void Intake::spin(directionType dir, double velocity, velocityUnits units)
  {
    intakeMotors[0]->spin(dir, velocity, units);
    
    if(usingSecondMotor)
    { intakeMotors[1]->spin(dir, velocity, units); }
  }

  void Intake::spin(directionType dir, double velocity, percentUnits units)
  {
    intakeMotors[0]->spin(dir, velocity, units);
    
    if(usingSecondMotor)
    { intakeMotors[1]->spin(dir, velocity, units); }
  }

  void Intake::spin(directionType dir, double velocity, voltageUnits units)
  {
    intakeMotors[0]->spin(dir, velocity, units);
    
    if(usingSecondMotor)
    { intakeMotors[1]->spin(dir, velocity, units); }
  }

  void Intake::stop()
  {
    intakeMotors[0]->stop();
    
    if(usingSecondMotor)
    { intakeMotors[1]->stop(); }
  }

  void Intake::setMaxTorque(double value, percentUnits units)
  {
    intakeMotors[0]->setMaxTorque(value, units);
    
    if(usingSecondMotor)
    { intakeMotors[1]->setMaxTorque(value, units); }
  }

  void Intake::setMaxTorque(double value, torqueUnits units)
  {
    intakeMotors[0]->setMaxTorque(value, units);
    
    if(usingSecondMotor)
    { intakeMotors[1]->setMaxTorque(value, units); }
  }

  void Intake::setMaxTorque(double value, currentUnits units)
  {
    intakeMotors[0]->setMaxTorque(value, units);
    
    if(usingSecondMotor)
    { intakeMotors[1]->setMaxTorque(value, units); }
  }

  directionType Intake::direction()
  { return intakeMotors[0]->direction(); }

  double Intake::velocity(velocityUnits units)
  {
    if(usingSecondMotor)
    { return ((intakeMotors[0]->velocity(units) + intakeMotors[1]->velocity(units)) / 2); }

    return intakeMotors[0]->velocity(units);
  }

  double Intake::velocity(percentUnits units)
  {
    if(usingSecondMotor)
    { return ((intakeMotors[0]->velocity(units) + intakeMotors[1]->velocity(units)) / 2); }

    return intakeMotors[0]->velocity(units);
  }

  double Intake::current(currentUnits units)
  {
    if(usingSecondMotor)
    { return ((intakeMotors[0]->current(units) + intakeMotors[1]->current(units)) / 2); }

    return intakeMotors[0]->current(units);
  }

  double Intake::current(percentUnits units)
  {
    if(usingSecondMotor)
    { return ((intakeMotors[0]->current(units) + intakeMotors[1]->current(units)) / 2); }

    return intakeMotors[0]->current(units);
  }

  double Intake::voltage(voltageUnits units)
  {
    if(usingSecondMotor)
    { return ((intakeMotors[0]->voltage(units) + intakeMotors[1]->voltage(units)) / 2); }

    return intakeMotors[0]->voltage(units);
  }

  double Intake::power(powerUnits units)
  {
    if(usingSecondMotor)
    { return (intakeMotors[0]->power(units) + intakeMotors[1]->power(units)); }

    return intakeMotors[0]->power(units);
  }

  double Intake::torque(torqueUnits units)
  {
    if(usingSecondMotor)
    { return (intakeMotors[0]->torque(units) + intakeMotors[1]->torque(units)); }

    return intakeMotors[0]->torque(units);
  }

  double Intake::efficiency(percentUnits units)
  {
    if(usingSecondMotor)
    { return ((intakeMotors[0]->efficiency(units) + intakeMotors[1]->efficiency(units)) / 2); }

    return intakeMotors[0]->efficiency(units);
  }

  double Intake::temperature(temperatureUnits units)
  {
    if(usingSecondMotor)
    { return ((intakeMotors[0]->temperature(units) + intakeMotors[1]->temperature(units)) / 2); }

    return intakeMotors[0]->temperature(units);
  }

  double Intake::temperature(percentUnits units)
  {
    if(usingSecondMotor)
    { return ((intakeMotors[0]->temperature(units) + intakeMotors[1]->temperature(units)) / 2); }

    return intakeMotors[0]->temperature(units);
  }
}
