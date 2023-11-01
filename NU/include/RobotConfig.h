#ifndef ROBOTCONFIG_H_
#define ROBOTCONFIG_H_

#include "vex.h"

using namespace vex;

// A global instance of brian
extern brain Brain;

// A global instance of competition
extern competition Competition;

// Motor and sensor setup ----------------------------------------------------
// drive motors
extern motor leftMotor1;
extern motor leftMotor2;
extern motor leftMotor3;
extern motor rightMotor1;
extern motor rightMotor2;
extern motor rightMotor3;

//Inertial Sensor
extern inertial Inertial;

//Drivetrain
extern motor_group leftMotors;
extern motor_group rightMotors;

extern smartdrive Drivetrain;

// catapult motor/sensors
extern motor cataMotor;
extern rotation cataSensor;

// intake motor
extern motor intakeMotor;

// controllers
extern controller Controller1;

// pistons
extern digital_out wingPistons;
extern digital_out intakePistons;
// ---------------------------------------------------------------------------

#endif // ROBOTCONFIG_H_