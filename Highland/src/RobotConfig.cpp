#include "../include/RobotConfig.h"
#include "../include/vex.h"

using namespace vex;

// A global instance of brian
brain Brain;

//* Motor and sensor setup
//Drive motors
motor leftMotor1 = motor(PORT9, gearSetting::ratio6_1, true);
motor leftMotor2 = motor(PORT16, gearSetting::ratio6_1, true);
motor leftMotor3 = motor(PORT7, gearSetting::ratio6_1, true);
motor rightMotor1 = motor(PORT2, gearSetting::ratio6_1, false);
motor rightMotor2 = motor(PORT14, gearSetting::ratio6_1, false);
motor rightMotor3 = motor(PORT4, gearSetting::ratio6_1, false);

//Inertial Sensor
inertial Inertial = inertial(PORT17);

//Drivetrain
motor_group leftMotors = motor_group(leftMotor1, leftMotor2, leftMotor3);
motor_group rightMotors = motor_group(rightMotor1, rightMotor2, rightMotor3);

smartdrive autoDrivetrain = smartdrive(leftMotors, rightMotors, Inertial, 299.24, 320, 40, mm, 0.75);

//Catapult motor/sensors
motor cataMotor = motor(PORT6, gearSetting::ratio36_1, true);
rotation cataSensor = rotation(PORT20, true);

//Intake motor
motor intakeMotor = motor(PORT5, gearSetting::ratio6_1, true);

//Pistons
digital_out wingPistons = digital_out(Brain.ThreeWirePort.A);