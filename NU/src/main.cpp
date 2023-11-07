/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Cameron Barclay                                           */
/*    Created:      9/30/2023, 12:45:32 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "evAPI.h"
#include "RobotConfig.h"

using namespace evAPI;

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
int lowCataAngle = 46;
int cataAngle;
double cataStartAngle;
#define CRNT_CATA_ANGL (cataSensor.angle(deg) - cataStartAngle)
int cataSpeed = 75;
bool cataLaunchMode = HIGH_CATA;

int intakeSpeed = 100;

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
void cataInc() {
    if (cataSpeed >= 100) {
        cataSpeed = 100;
    } else {
        cataSpeed += 5;
    }
}
void cataDec() {
    if (cataSpeed <= 0) {
        cataSpeed = 0;
    } else {
        cataSpeed -= 5;
    }
}

double robotBattery = Brain.Battery.capacity();

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
    //Setup functions to be run when buttons on the controller are pressed
    primaryController.INTK_PST_BUTTON.pressed(tglIntake);
    primaryController.WINGS_BUTTON.pressed(tglWings);
    primaryController.CATA_SET_BUTTON.pressed(tglCataMode);
    primaryController.CATA_SPEED_INC.pressed(cataInc);
    primaryController.CATA_SPEED_DEC.pressed(cataDec);

    //Clear the screen and print the calibrating message for the inertial
    primaryController.Screen.clearScreen();
    primaryController.Screen.setCursor(1, 1);
    primaryController.Screen.print("Calibrating...");

    //Calibrate the inertial
    Inertial.calibrate();

    //Wait for the inertial to finish calibrating
    while(Inertial.isCalibrating())
    {
        this_thread::sleep_for(10);
    }

    //*Setup the UI
    //Add the buttons
    UI.addBlank();
    UI.addBlank();
    UI.addButton(0xff10a0, "Skills", "Shoots all the match loads into the field.", UI.Icons.skills);
    UI.addButton(blue, "Push In", "Auto for pushing in a nugget in on either side.", UI.Icons.leftArrow);
    UI.addBlank();
    UI.addBlank();
    UI.addBlank();
    UI.addButton(blue, "Load", "Auto for a robot on the loading side of the field.", UI.Icons.number0);

    //Add variables to the controller UI
    UI.createControllerReadOut("Speed: ", cataSpeed);
    UI.createControllerReadOut("Battery: ", robotBattery);

    //Setup auto selector
    UI.selectButton(3, true);
    UI.setDisplayTime(1500);

    //Start the UI
    UI.startUIThreads();

    //Setup the drivetrain for autonomous
    Drivetrain.setDriveVelocity(20, percent);
    Drivetrain.setTurnVelocity(20, percent);
   
    intakePistons.set(true);
    intakeState = true;
    cataStartAngle = cataSensor.angle(deg);
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

    //Select which auto to run based on what button is pressed
    switch (UI.getProgNumber())
    {
        case 2: //Skills
            cataMotor.spin(forward, 80, percent);
            break;

        case 3: //Push In
            //Ram the triball into the goal
            Drivetrain.drive(reverse, 100, velocityUnits::pct);
            vex::task::sleep(2000);

            //Stop moving and wait a bit
            Drivetrain.stop(coast);
            vex::task::sleep(1000);

            //Drive away from the goal
            Drivetrain.drive(forward, 25, velocityUnits::pct);
            vex::task::sleep(500);
            Drivetrain.stop(coast);
            break;

        case 7: //Match load side
            //Extend the wings
            intakePistons.set(true);
            intakeState = true;
            this_thread::sleep_for(100);

            //Set speed parameters for the drivetrain
            Drivetrain.setDriveVelocity(10, percent);
            Drivetrain.setTurnVelocity(5, percent);
            Drivetrain.setTurnThreshold(5);

            //Remove nugget from match loading zone
            Drivetrain.driveFor(reverse, 4, distanceUnits::in);
            Drivetrain.turnFor(turnType::left, 45, rotationUnits::deg);

            /*
            //Push othe nugget in
            Drivetrain.setDriveVelocity(70, percent);
            Drivetrain.turnFor(turnType::right, 62, rotationUnits::deg);
            Drivetrain.driveFor(forward, 28, distanceUnits::in);

            //Go back and hi it again
            Drivetrain.setDriveVelocity(15, percent);
            Drivetrain.driveFor(reverse, 10, distanceUnits::in);
            Drivetrain.turnFor(turnType::right, 5, rotationUnits::deg);
            Drivetrain.setDriveVelocity(80, percent);
            Drivetrain.driveFor(forward, 10, distanceUnits::in);

            //Go back and realign
            Drivetrain.setDriveVelocity(15, percent);
            Drivetrain.driveFor(reverse, 24, distanceUnits::in);

            //Go and hit the pole
            Drivetrain.setDriveVelocity(8, percent);
            Drivetrain.driveFor(forward, 5, distanceUnits::in);
            Drivetrain.turnFor(turnType::right, 10, rotationUnits::deg);
            Drivetrain.driveFor(forward, 10, distanceUnits::in);
            Drivetrain.turnFor(turnType::right, 10, rotationUnits::deg);
            Drivetrain.driveFor(forward, 20, distanceUnits::in);
            Drivetrain.turnFor(turnType::right, 10, rotationUnits::deg);
            Drivetrain.setDriveVelocity(30, percent);
            Drivetrain.driveFor(forward, 20, distanceUnits::in);
            */

            break;
    
        default: //Do Nothing
            break;
    }
    
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
    //*User control start
    //Stores the previous speed of the catapult
    int cataSpeed_old = cataSpeed;

    //Print out catapult speed to the terminal
    printf("Speed: %i\n", cataSpeed);

    //Set stopping modes for the base motors
    leftMotor1.setStopping(brake);
    leftMotor2.setStopping(brake);
    leftMotor3.setStopping(brake);
    rightMotor1.setStopping(brake);
    rightMotor2.setStopping(brake);
    rightMotor3.setStopping(brake);

    // User control code here, inside the loop
    while (1) {
        // ------------------------- make it drive -----------------------
        leftSpeed = (primaryController.Axis3.position() + (primaryController.Axis1.position() * .8));
        rightSpeed = (primaryController.Axis3.position() - (primaryController.Axis1.position() * .8));
        leftMotor1.spin(fwd, leftSpeed, pct);
        leftMotor2.spin(fwd, leftSpeed, pct);
        leftMotor3.spin(fwd, leftSpeed, pct);
        rightMotor1.spin(fwd, rightSpeed, pct);
        rightMotor2.spin(fwd, rightSpeed, pct);
        rightMotor3.spin(fwd, rightSpeed, pct);

        // --------------------- control cata -------------------------
        if (cataSpeed != cataSpeed_old) {
            printf("Speed: %i\n", cataSpeed);
            
            cataSpeed_old = cataSpeed;
        }
        
        if (!primaryController.CATA_STOP_BUTTON.pressing()) {
            if (primaryController.CATA_FIRE_BUTTON.pressing() || CRNT_CATA_ANGL < cataAngle) {
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
        
        //Print out the angle of the catapult
        printf("\n%f\n\n", CRNT_CATA_ANGL);

        // --------------------- control intake -----------------------
        intakePistons.set(intakeState);

        // -------------------- control wings ------------------------
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
        //Store the percentage of the battery to display on te controller.
        robotBattery = Brain.Battery.capacity();

        //Wait to allow other threads to use the CPU
        wait(50, msec);
    }
}
