#include "../include/RobotConfig.h"
#include "../include/vex.h"

using namespace vex;

// A global instance of brian
brain Brain;

//* Motor and sensor setup
//Drive motors
motor leftMotor1 = motor(PORT9, gearSetting::ratio6_1, true);
motor leftMotor2 = motor(PORT8, gearSetting::ratio6_1, true);
motor leftMotor3 = motor(PORT7, gearSetting::ratio6_1, true);
motor rightMotor1 = motor(PORT2, gearSetting::ratio6_1, false);
motor rightMotor2 = motor(PORT14, gearSetting::ratio6_1, false);
motor rightMotor3 = motor(PORT4, gearSetting::ratio6_1, false);

//Inertial Sensor
inertial Inertial = inertial(PORT8);

//Drivetrain
motor_group leftMotors = motor_group(leftMotor1, leftMotor2, leftMotor3);
motor_group rightMotors = motor_group(rightMotor1, rightMotor2, rightMotor3);

smartdrive autoDrivetrain = smartdrive(leftMotors, rightMotors, Inertial, 319.19, 320, 40, mm, 0.6666666666666666);

//Catapult motor/sensors
motor cataMotor = motor(PORT20, gearSetting::ratio36_1, false);
rotation cataSensor = rotation(PORT9, true);

//Intake motor
motor intakeMotor = motor(PORT10, gearSetting::ratio6_1, true);

//Pistons
digital_out wingPistons = digital_out(Brain.ThreeWirePort.B);
digital_out intakePistons = digital_out(Brain.ThreeWirePort.A);