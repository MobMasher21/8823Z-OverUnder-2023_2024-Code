#include "../include/RobotConfig.h"
#include "../include/vex.h"

using namespace vex;

// A global instance of brian
brain Brain;

// A global instance of competition
competition Competition;

// Motor and sensor setup ----------------------------------------------------
// drive motors
motor leftMotor1 = motor(PORT15, gearSetting::ratio6_1, true);
motor leftMotor2 = motor(PORT14, gearSetting::ratio6_1, true);
motor leftMotor3 = motor(PORT13, gearSetting::ratio6_1, true);
motor rightMotor1 = motor(PORT19, gearSetting::ratio6_1, false);
motor rightMotor2 = motor(PORT17, gearSetting::ratio6_1, false);
motor rightMotor3 = motor(PORT16, gearSetting::ratio6_1, false);

// catapult motor/sensors
motor cataMotor = motor(PORT20, gearSetting::ratio36_1, true);
rotation cataSensor = rotation(PORT9, true);

// intake motor
motor intakeMotor = motor(PORT2, gearSetting::ratio6_1, false);

// controllers
controller Controller1 = controller(controllerType::primary);

// pistons
digital_out wingPistons = digital_out(Brain.ThreeWirePort.A);
digital_out intakePistons = digital_out(Brain.ThreeWirePort.B);
// ---------------------------------------------------------------------------

