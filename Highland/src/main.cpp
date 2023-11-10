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

#define TURN_HANDICAP 0.8
#define DRIVE_HANDICAP 1

int leftSpeed;
int rightSpeed;

enum class cataStates
{
  HIGH_CATA = 0,
  LOW_CATA = 1
};

cataStates cataLaunchMode = cataStates::HIGH_CATA;

const int highCataAngle = 30;
const int lowCataAngle = 46;
int targetCataAngle;
double cataStartAngle;
double currentCataAngle;
int cataSpeed = 75;

int intakeSpeed = 100;

/**
 * @brief Toggles the state of the wings.
*/
void tglWings()
{
  wingPistons.set(!wingPistons.value());
}

/**
 * @brief Toggles the state of the intake piston.
*/
void tglIntake()
{
  intakePistons.set(!intakePistons.value());
}

/**
 * @brief Toggles the state of the catapult.
*/
void tglCataMode()
{
  if(cataLaunchMode == cataStates::HIGH_CATA)
  {
    cataLaunchMode = cataStates::LOW_CATA;
  }

  else
  {
    cataLaunchMode = cataStates::HIGH_CATA;
  }
}

/**
 * @brief Increments the catapult speed by 5.
*/
void cataInc()
{
  if(cataSpeed >= 100)
  {
    cataSpeed = 100;
  }

  else
  {
    cataSpeed += 5;
  }
}

/**
 * @brief Decrements the catapult speed by 5.
*/
void cataDec()
{
  if(cataSpeed <= 0)
  {
    cataSpeed = 0;
  }

  else
  {
    cataSpeed -= 5;
  }
}

//Percentage of the robot battery.
double robotBatteryCapacity = Brain.Battery.capacity();
double robotBatteryVolt = Brain.Battery.voltage();
double robotBatteryCurrent = Brain.Battery.current();

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

void pre_auton(void)
{
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  // Setup functions to be run when buttons on the controller are pressed
  primaryController.INTK_PST_BUTTON.pressed(tglIntake);
  primaryController.WINGS_BUTTON.pressed(tglWings);
  primaryController.CATA_SET_BUTTON.pressed(tglCataMode);
  primaryController.CATA_SPEED_INC.pressed(cataInc);
  primaryController.CATA_SPEED_DEC.pressed(cataDec);

  // Clear the screens and print the calibrating message for the inertial
  primaryController.Screen.clearScreen();
  primaryController.Screen.setCursor(1, 1);
  primaryController.Screen.print("Calibrating...");

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Calibrating Inertial...");

  // Calibrate the inertial
  Inertial.calibrate();

  // Wait for the inertial to finish calibrating
  /* while(Inertial.isCalibrating())
  {
    this_thread::sleep_for(10);
  } */

  //*Setup the UI
  //Add the buttons to the preauto
  UI.addBlank();
  UI.addBlank();
  UI.addButton(0xff10a0, "Skills", "Shoots all the match loads into the field.", UI.Icons.skills);
  UI.addButton(blue, "Push In", "Auto for pushing in a nugget in on either side.", UI.Icons.leftArrow);
  UI.addBlank();
  UI.addBlank();
  UI.addButton(ClrGray, "Do Nothing", "Auto that does nothing.", UI.Icons.exclamationMark);
  UI.addButton(blue, "Load", "Auto for a robot on the loading side of the field.", UI.Icons.number0);

  //Add the displays to the match UI
  UI.setDefaultReadOutColor(ClrDarkSlateBlue);

  UI.createBrainReadOut("Battery Info:", ClrDarkRed);
  UI.createBrainReadOut("Capacity: ", robotBatteryCapacity);
  UI.createBrainReadOut("Voltage: ", robotBatteryVolt);
  UI.createBrainReadOut("Current: ", robotBatteryCurrent);

  UI.createBrainReadOut("Catapult Info:", ClrDarkGreen);
  UI.createBrainReadOut("Motor Speed: ", cataSpeed);
  UI.createBrainReadOut("Target Angle: ", targetCataAngle);
  UI.createBrainReadOut("Cata Angle: ", currentCataAngle);

  //Add variables to the controller UI
  UI.primaryControllerUI.addData(0, "Catapult Speed: ", cataSpeed);
  UI.primaryControllerUI.addData(1, "Capacity: ", robotBatteryCapacity);
  UI.primaryControllerUI.addData(2, "Current: ", robotBatteryCurrent);

  //Setup auto selector
  UI.selectButton(6, true);
  UI.setDisplayTime(1500);

  //Start the UI
  UI.startUIThreads();

  //Setup the drivetrain for autonomous
  autoDrivetrain.setDriveVelocity(20, percent);
  autoDrivetrain.setTurnVelocity(20, percent);

  //Retract the wings
  wingPistons.set(true);

  cataStartAngle = cataSensor.angle(deg);
  currentCataAngle = cataSensor.angle(deg) - cataStartAngle;
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

void autonomous(void)
{
  // ..........................................................................
  // Insert autonomous user code here.

  // Select which auto to run based on what button is pressed
  switch (UI.getProgNumber())
  {
    case 2: // Skills
      cataMotor.spin(forward, 80, percent);
      break;

    case 3: // Push In
      // Ram the triball into the goal
      autoDrivetrain.drive(reverse, 100, velocityUnits::pct);
      vex::task::sleep(2000);

      // Stop moving and wait a bit
      autoDrivetrain.stop(coast);
      vex::task::sleep(1000);

      // Drive away from the goal
      autoDrivetrain.drive(forward, 25, velocityUnits::pct);
      vex::task::sleep(500);
      autoDrivetrain.stop(coast);
      break;

    case 7: // Match load side
      // Extend the wings
      intakePistons.set(true);
      this_thread::sleep_for(100);

      // Set speed parameters for the drivetrain
      autoDrivetrain.setDriveVelocity(10, percent);
      autoDrivetrain.setTurnVelocity(5, percent);
      autoDrivetrain.setTurnThreshold(5);

      // Remove nugget from match loading zone
      autoDrivetrain.driveFor(reverse, 4, distanceUnits::in);
      autoDrivetrain.turnFor(turnType::left, 45, rotationUnits::deg);

      /*
      //Push othe nugget in
      autoDrivetrain.setDriveVelocity(70, percent);
      autoDrivetrain.turnFor(turnType::right, 62, rotationUnits::deg);
      autoDrivetrain.driveFor(forward, 28, distanceUnits::in);

      //Go back and hi it again
      autoDrivetrain.setDriveVelocity(15, percent);
      autoDrivetrain.driveFor(reverse, 10, distanceUnits::in);
      autoDrivetrain.turnFor(turnType::right, 5, rotationUnits::deg);
      autoDrivetrain.setDriveVelocity(80, percent);
      autoDrivetrain.driveFor(forward, 10, distanceUnits::in);

      //Go back and realign
      autoDrivetrain.setDriveVelocity(15, percent);
      autoDrivetrain.driveFor(reverse, 24, distanceUnits::in);

      //Go and hit the pole
      autoDrivetrain.setDriveVelocity(8, percent);
      autoDrivetrain.driveFor(forward, 5, distanceUnits::in);
      autoDrivetrain.turnFor(turnType::right, 10, rotationUnits::deg);
      autoDrivetrain.driveFor(forward, 10, distanceUnits::in);
      autoDrivetrain.turnFor(turnType::right, 10, rotationUnits::deg);
      autoDrivetrain.driveFor(forward, 20, distanceUnits::in);
      autoDrivetrain.turnFor(turnType::right, 10, rotationUnits::deg);
      autoDrivetrain.setDriveVelocity(30, percent);
      autoDrivetrain.driveFor(forward, 20, distanceUnits::in);
      */

      break;

    case 6: //Do nothing auto
      //!NO CODE HERE
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

void usercontrol(void)
{
  //*User control start
  // Stores the previous speed of the catapult
  int cataSpeed_old = cataSpeed;

  // Print out catapult speed to the terminal
  //printf("Speed: %i\n", cataSpeed);

  // Set stopping modes for the base motors
  leftMotors.setStopping(brake);
  rightMotors.setStopping(brake);

  // User control code here, inside the loop
  while(true)
  {
    //! ------------------------- make it drive -----------------------
    //Get the speed for the left and right side motors
    leftSpeed = ((primaryController.Axis3.position() * DRIVE_HANDICAP)
               + (primaryController.Axis1.position() * TURN_HANDICAP));

    rightSpeed = ((primaryController.Axis3.position() * DRIVE_HANDICAP)
                - (primaryController.Axis1.position() * TURN_HANDICAP));

    //Set the speed of the left and right motors
    //leftMotors.spin(fwd, leftSpeed, pct);
    //rightMotors.spin(fwd, rightSpeed, pct);

    //! --------------------- control cata -------------------------
    //Keep track of the catapult speed and log when it changes
    if(cataSpeed != cataSpeed_old)
    {
      //printf("Speed: %i\n", cataSpeed);

      cataSpeed_old = cataSpeed;
    }

    //Get the angle of the catapult
    currentCataAngle = cataSensor.angle(deg) - cataStartAngle;

    //*Run cata control code if the stop button isn't pressed
    if(!primaryController.CATA_STOP_BUTTON.pressing())
    {
      //Lower the catapult if the fire button is pressed, or if the angle is less than the target angle
      if(primaryController.CATA_FIRE_BUTTON.pressing() || currentCataAngle < targetCataAngle)
      {
        cataMotor.spin(fwd, cataSpeed, pct);
      }

      //Stop and hold down the catapult
      else
      {
        cataMotor.stop(hold);
      }

      //Update the target angle when the launch mode changes
      if(cataLaunchMode == cataStates::HIGH_CATA)
      {
        targetCataAngle = highCataAngle;
      }

      else
      {
        targetCataAngle = lowCataAngle;
      }
    }

    //Stop the catapult if the stop button is pressed
    else
    {
      cataMotor.stop(coast);
    }

    // Print out the angle of the catapult
    //printf("\n%f\n\n", currentCataAngle);

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    //Store parameters to display on the screens
    robotBatteryCapacity = Brain.Battery.capacity();
    robotBatteryVolt = Brain.Battery.voltage();
    robotBatteryCurrent = Brain.Battery.current();

    // Wait to allow other threads to use the CPU
    wait(50, msec);
  }
}
