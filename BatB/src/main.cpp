/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Cameron Barclay                                           */
/*    Created:      9/30/2023, 12:45:32 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of brian
brain Brain;

// A global instance of competition
competition Competition;

// Motor and sensor setup ----------------------------------------------------
// drive motors
motor leftMotor1 = motor(PORT1, gearSetting::ratio6_1, true);
motor leftMotor2 = motor(PORT2, gearSetting::ratio6_1, true);
motor leftMotor3 = motor(PORT3, gearSetting::ratio6_1, true);
motor rightMotor1 = motor(PORT4, gearSetting::ratio6_1, false);
motor rightMotor2 = motor(PORT5, gearSetting::ratio6_1, false);
motor rightMotor3 = motor(PORT6, gearSetting::ratio6_1, false);

// catapult motor/sensors
motor cataMotor = motor(PORT7, gearSetting::ratio36_1, false);
rotation cataSensor = rotation(PORT9, false);

// intake motor
motor intakeMotor = motor(PORT8, gearSetting::ratio6_1, false);

// controllers
controller Controller1 = controller(controllerType::primary);

//pistons
digital_out intakePistons = digital_out(Brain.ThreeWirePort.A);
digital_out wingPistons = digital_out(Brain.ThreeWirePort.B);
// ---------------------------------------------------------------------------

// Driver control settings and variables -------------------------------------
// contorl buttons
#define CATA_BUTTON ButtonR1
#define INTK_IN_BUTTON ButtonL1
#define INTK_OUT_BUTTON ButtonL2
#define INTK_PST_BUTTON ButtonR2
#define WINGS_BUTTON ButtonA

int leftSpeed;
int rightSpeed;

int cataSpeed = 75;
int intakeSpeed = 100;

bool intakeBounce;
bool intakeState;

bool wingBounce;
bool wingState;
// ---------------------------------------------------------------------------


// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // ------------------------- make it drive -----------------------
    leftSpeed = (Controller1.Axis3.position() + Controller1.Axis1.position());
    rightSpeed = (Controller1.Axis3.position() - Controller1.Axis1.position());
    leftMotor1.spin(fwd, leftSpeed, pct);
    leftMotor2.spin(fwd, leftSpeed, pct);
    leftMotor3.spin(fwd, leftSpeed, pct);
    rightMotor1.spin(fwd, rightSpeed, pct);
    rightMotor2.spin(fwd, rightSpeed, pct);
    rightMotor3.spin(fwd, rightSpeed, pct);

    // --------------------- control cata -------------------------
    if(Controller1.CATA_BUTTON.pressing()) {
      cataMotor.spin(fwd, cataSpeed, pct);
    } else {
      cataMotor.stop(hold);
    }

    // --------------------- control intake -----------------------
    if(Controller1.INTK_IN_BUTTON.pressing()) {
      intakeMotor.spin(fwd, intakeSpeed, pct);
    } else if(Controller1.INTK_OUT_BUTTON.pressing()) {
      intakeMotor.spin(reverse, intakeSpeed, pct);
    } else {
      intakeMotor.stop();
    }

    if(intakeBounce != Controller1.INTK_PST_BUTTON.pressing()) {
      intakeState = Controller1.INTK_PST_BUTTON.pressing();
    }
    intakeBounce = Controller1.INTK_PST_BUTTON.pressing();
    intakePistons.set(intakeState);

    // -------------------- control wings ------------------------
    if(wingBounce != Controller1.WINGS_BUTTON.pressing()) {
      wingState = Controller1.WINGS_BUTTON.pressing();
    }
    wingBounce = Controller1.WINGS_BUTTON.pressing();
    intakePistons.set(wingState);


    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
