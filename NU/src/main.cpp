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

using namespace evAPI;

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

//Inertial Sensor
inertial Inertial = inertial(PORT8);

//Drivetrain
motor_group leftMotors = motor_group(leftMotor1, leftMotor2, leftMotor3);
motor_group rightMotors = motor_group(rightMotor1, rightMotor2, rightMotor3);

smartdrive Drivetrain = smartdrive(leftMotors, rightMotors, Inertial, 319.19, 320, 40, mm, 0.6666666666666666);

// catapult motor/sensors
motor cataMotor = motor(PORT20, gearSetting::ratio36_1, true);
rotation cataSensor = rotation(PORT9, true);

// intake motor
motor intakeMotor = motor(PORT2, gearSetting::ratio6_1, false);

// controllers
//controller Controller1 = controller(controllerType::primary);

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
    primaryController.INTK_PST_BUTTON.pressed(tglIntake);
    primaryController.WINGS_BUTTON.pressed(tglWings);
    primaryController.CATA_SET_BUTTON.pressed(tglCataMode);

    Drivetrain.setDriveVelocity(20, percent);
    Drivetrain.setTurnVelocity(20, percent);

    Inertial.calibrate();

    while(Inertial.isCalibrating())
    {
        this_thread::sleep_for(10);
    }

    /* UI.addAutoTab("Auto");
    UI.addButton(BLUE_SCORING_AUTO, ClrGray);
    UI.addTitle(BLUE_SCORING_AUTO, "Push In");
    UI.addDescription(BLUE_SCORING_AUTO, "Auto for pushing in a nugget in on either side.");
    UI.addIcon(BLUE_SCORING_AUTO, RIGHT_ARROW);
    UI.addAlliance(BLUE_SCORING_AUTO, allianceType::noAlliance);

    UI.addButton(BLUE_LOADING_AUTO, blue);
    UI.addTitle(BLUE_LOADING_AUTO, "Load");
    UI.addDescription(BLUE_LOADING_AUTO, "Auto for a blue alliance robot on the match loading side.");
    //UI.addIcon(BLUE_LOADING_AUTO, RIGHT_ARROW);
    UI.changeIconColor(BLUE_LOADING_AUTO, black);

    UI.setDisplayTime(1500);

    UI.startUIThreads();
    UI.selectButton(BLUE_LOADING_AUTO, true);

    UI.enableManualUIControl(true);
    UI.setUIMode(UIStates::Preauto_UI); */

    UI.addBlank();
    UI.addBlank();
    UI.addButton(0xff10a0, "Skills", "Shoots all the match loads into the field.", UI.Icons.skills);
    UI.addButton(blue, "Push In", "Auto for pushing in a nugget in on either side.", UI.Icons.number0);
    UI.addBlank();
    UI.addBlank();
    UI.addBlank();
    UI.addButton(blue, "Load", "Auto for a robot on the loading side of the field.", UI.Icons.number0);

    UI.selectButton(3, true);
    UI.setDisplayTime(1500);
    UI.startUIThreads();
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

    switch (UI.getProgNumber())
    {
        case 2: //Skills
            cataMotor.spin(forward, 80, percent);
            break;

        case 3: //Push In
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
            break;

        case 7: //Match load side
            intakePistons.set(true);
            intakeState = true;
            this_thread::sleep_for(100);

            Drivetrain.setDriveVelocity(10, percent);
            Drivetrain.setTurnVelocity(5, percent);

            Drivetrain.setTurnThreshold(5);

            //Remove nugget
            Drivetrain.driveFor(reverse, 4, distanceUnits::in);
            Drivetrain.turnFor(turnType::left, 45, rotationUnits::deg);

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

            break;
    
        default:
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
    int cataSpeed_old = cataSpeed;

    printf("Speed: %i\n", cataSpeed);

    primaryController.Screen.clearScreen();
    primaryController.Screen.setCursor(1, 1);
    primaryController.Screen.print(cataSpeed);

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
        leftSpeed = (primaryController.Axis3.position() + primaryController.Axis1.position());
        rightSpeed = (primaryController.Axis3.position() - primaryController.Axis1.position());
        leftMotor1.spin(fwd, leftSpeed, pct);
        leftMotor2.spin(fwd, leftSpeed, pct);
        leftMotor3.spin(fwd, leftSpeed, pct);
        rightMotor1.spin(fwd, rightSpeed, pct);
        rightMotor2.spin(fwd, rightSpeed, pct);
        rightMotor3.spin(fwd, rightSpeed, pct);

        // --------------------- control cata -------------------------
        if (primaryController.CATA_SPEED_INC.pressing()) {
            if (cataSpeed >= 100) {
                cataSpeed = 100;
            } else {
                cataSpeed++;
            }
        }

        if (primaryController.CATA_SPEED_DEC.pressing()) {
            if (cataSpeed <= 0) {
                cataSpeed = 0;
            } else {
                cataSpeed--;
            }
        }

        if (cataSpeed != cataSpeed_old) {
            printf("Speed: %i\n", cataSpeed);

            primaryController.Screen.clearScreen();
            primaryController.Screen.setCursor(1, 1);
            primaryController.Screen.print(cataSpeed);
            
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

        // --------------------- control intake -----------------------
        if (primaryController.INTK_IN_BUTTON.pressing()) {
            intakeMotor.spin(fwd, intakeSpeed, pct);
        } else if (primaryController.INTK_OUT_BUTTON.pressing()) {
            intakeMotor.spin(reverse, intakeSpeed, pct);
        } else {
            intakeMotor.stop();
        }

        /*
        if(intakeBounce != primaryController.INTK_PST_BUTTON.pressing()) {
          intakeState = primaryController.INTK_PST_BUTTON.pressing();
        }
        intakeBounce = primaryController.INTK_PST_BUTTON.pressing();
        */
        intakePistons.set(intakeState);

        // -------------------- control wings ------------------------
        /*
        if(wingBounce != primaryController.WINGS_BUTTON.pressing()) {
          wingState = primaryController.WINGS_BUTTON.pressing();
        }
        wingBounce = primaryController.WINGS_BUTTON.pressing();
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
