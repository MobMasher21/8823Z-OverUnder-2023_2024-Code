#ifndef ROBOTCONFIG_H_
#define ROBOTCONFIG_H_

#include "vex.h"

using namespace vex;

// A global instance of brian
extern brain Brain;

//*Motor and sensor setup
//Drive motors
/* extern motor leftMotor1;
extern motor leftMotor2;
extern motor leftMotor3;
extern motor rightMotor1;
extern motor rightMotor2;
extern motor rightMotor3; */

//Inertial Sensor
extern inertial Inertial;

//Drivetrain
extern motor_group leftMotors;
extern motor_group rightMotors;

extern smartdrive autoDrivetrain;

//Catapult motor/sensors
extern motor cataMotor;
extern rotation cataSensor;

//Intake motor
extern motor intakeMotor;

//Pistons
extern digital_out wingPistons;
extern digital_out intakePistons;

#endif // ROBOTCONFIG_H_