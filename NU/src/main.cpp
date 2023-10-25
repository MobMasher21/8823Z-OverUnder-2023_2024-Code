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

// Driver control settings and variables -------------------------------------
// contorl buttons
#define CATA_FIRE_BUTTON ButtonR2
#define CATA_SET_BUTTON ButtonA
#define CATA_STOP_BUTTON ButtonX
#define CATA_SPEED_INC ButtonUp
#define CATA_SPEED_DEC ButtonDown
#define INTK_IN_BUTTON ButtonL1
#define INTK_OUT_BUTTON ButtonL2
#define INTK_PST_BUTTON ButtonR1
#define WINGS_BUTTON ButtonB

int leftSpeed;
int rightSpeed;

enum {
    HIGH_CATA = 0,
    LOW_CATA = 1
};

int highCataAngle = 30;
int lowCataAngle = 45;
int cataAngle;
int cataStartAngle;
#define CRNT_CATA_ANGL (cataSensor.angle(deg) - cataStartAngle)
int cataSpeed = 75;
int intakeSpeed = 100;
bool cataLaunchMode = HIGH_CATA;

bool intakeBounce = false;
bool intakeState;

bool wingBounce = false;
bool wingState;

void tglWings() {
    wingState = !wingState;
}
void tglIntake() {
    intakeState = !intakeState;
}
void tglCataMode() {
    if (cataLaunchMode == HIGH_CATA) {
        cataLaunchMode = LOW_CATA;
    } else if (cataLaunchMode == LOW_CATA) {
        cataLaunchMode = HIGH_CATA;
    }
}
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
    intakePistons.set(true);
    intakeState = true;
    Controller1.INTK_PST_BUTTON.pressed(tglIntake);
    Controller1.WINGS_BUTTON.pressed(tglWings);
    Controller1.CATA_SET_BUTTON.pressed(tglCataMode);
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
    leftMotor1.spin(reverse, 100, pct);
    leftMotor2.spin(reverse, 100, pct);
    leftMotor3.spin(reverse, 100, pct);
    rightMotor1.spin(reverse, 100, pct);
    rightMotor2.spin(reverse, 100, pct);
    rightMotor3.spin(reverse, 100, pct);
    vex::task::sleep(2000);
    leftMotor1.stop(coast);
    leftMotor2.stop(coast);
    leftMotor3.stop(coast);
    rightMotor1.stop(coast);
    rightMotor2.stop(coast);
    rightMotor3.stop(coast);
    vex::task::sleep(1000);
    leftMotor1.spin(forward, 25, pct);
    leftMotor2.spin(forward, 25, pct);
    leftMotor3.spin(forward, 25, pct);
    rightMotor1.spin(forward, 25, pct);
    rightMotor2.spin(forward, 25, pct);
    rightMotor3.spin(forward, 25, pct);
    vex::task::sleep(500);
    leftMotor1.stop(coast);
    leftMotor2.stop(coast);
    leftMotor3.stop(coast);
    rightMotor1.stop(coast);
    rightMotor2.stop(coast);
    rightMotor3.stop(coast);
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
    int cataSpeed_old = cataSpeed;

    printf("Speed: %i\n", cataSpeed);

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(cataSpeed);


    leftMotor1.setStopping(brake);
    leftMotor2.setStopping(brake);
    leftMotor3.setStopping(brake);
    rightMotor1.setStopping(brake);
    rightMotor2.setStopping(brake);
    rightMotor3.setStopping(brake);

    // User control code here, inside the loop
    cataStartAngle = cataSensor.angle(deg);
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
        if (Controller1.CATA_SPEED_INC.pressing()) {
            if (cataSpeed >= 100) {
                cataSpeed = 100;
            } else {
                cataSpeed++;
            }
        }

        if (Controller1.CATA_SPEED_DEC.pressing()) {
            if (cataSpeed <= 0) {
                cataSpeed = 0;
            } else {
                cataSpeed--;
            }
        }

        if (cataSpeed != cataSpeed_old) {
            printf("Speed: %i\n", cataSpeed);

            Controller1.Screen.clearScreen();
            Controller1.Screen.setCursor(1, 1);
            Controller1.Screen.print(cataSpeed);
            
            cataSpeed_old = cataSpeed;
        }
        
        if (!Controller1.CATA_STOP_BUTTON.pressing()) {
            if (Controller1.CATA_FIRE_BUTTON.pressing() || CRNT_CATA_ANGL < cataAngle) {
                cataMotor.spin(fwd, cataSpeed, pct);
            } else {
                cataMotor.stop(hold);
            }
            if (cataLaunchMode == HIGH_CATA) {
                cataAngle = highCataAngle;
            } else if (cataLaunchMode == LOW_CATA) {
                cataAngle = lowCataAngle;
            }
        } else {
            cataMotor.stop(coast);
        }

        // --------------------- control intake -----------------------
        if (Controller1.INTK_IN_BUTTON.pressing()) {
            intakeMotor.spin(fwd, intakeSpeed, pct);
        } else if (Controller1.INTK_OUT_BUTTON.pressing()) {
            intakeMotor.spin(reverse, intakeSpeed, pct);
        } else {
            intakeMotor.stop();
        }

        /*
        if(intakeBounce != Controller1.INTK_PST_BUTTON.pressing()) {
          intakeState = Controller1.INTK_PST_BUTTON.pressing();
        }
        intakeBounce = Controller1.INTK_PST_BUTTON.pressing();
        */
        intakePistons.set(intakeState);

        // -------------------- control wings ------------------------
        /*
        if(wingBounce != Controller1.WINGS_BUTTON.pressing()) {
          wingState = Controller1.WINGS_BUTTON.pressing();
        }
        wingBounce = Controller1.WINGS_BUTTON.pressing();
        */
        wingPistons.set(wingState);

        wait(20, msec);  // Sleep the task for a short amount of time to
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
