/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Authors:      Cameron Barclay, Jayden Liffick, Teo Carrion              */
/*    Created:      9/30/2023, 12:45:32 AM                                    */
/*    Description:  Main code for 8823Z robot.                                */
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
#define WINGS_BUTTON ButtonR1

//Limiters for controller driving
// #define TURN_HANDICAP 0.5 // made this a variable so that it can be set to different values depending on the driver
#define DRIVE_HANDICAP 1

int leftSpeed;
int rightSpeed;

enum class cataStates
{
  HIGH_CATA = 0,
  LOW_CATA = 1
};

cataStates cataLaunchMode = cataStates::HIGH_CATA;

//const int16_t highCataAngle = 30;
//const int16_t lowCataAngle = 46;
int targetCataAngle;
double cataStartAngle;
double currentCataAngle;
int cataSpeed = 75;

int intakeSpeed = 100;
float turnHandicap;

/**
 * @brief Toggles the state of the wings.
*/
void tglWings()
{
  wingPistons.set(!wingPistons.value());
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


/// @brief sets the turn handicap based on wether left or right is pressed
void setTurnHandicap() {
  primaryController.Screen.clearScreen();
  primaryController.Screen.setCursor(0, 0);
  primaryController.Screen.print("Set turn handicap:");
  primaryController.Screen.newLine();
  primaryController.Screen.print("Left = 0.75");
  primaryController.Screen.newLine();
  primaryController.Screen.print("Right = 0.5");

  while (!primaryController.ButtonLeft.pressing() && !primaryController.ButtonRight.pressing())
  {
    this_thread::sleep_for(10);
  }

  if (primaryController.ButtonLeft.pressing())
  {
    turnHandicap = 0.75;
  }
  else if (primaryController.ButtonRight.pressing()) 
  {
    turnHandicap = 0.5;
  } 
  else
  {
    turnHandicap = (0.75 + 0.5) / 2;
  }

  primaryController.Screen.clearScreen();
}

//Information about the robot battery
int robotBatteryCapacity = (int)Brain.Battery.capacity();
double robotBatteryVolt = Brain.Battery.voltage();
double robotBatteryCurrent = Brain.Battery.current();

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
  //All activities that occur before the competition starts
  //Example: clearing encoders, setting servo positions, ...
  //Setup functions to be run when buttons on the controller are pressed
  primaryController.WINGS_BUTTON.pressed(tglWings);
  primaryController.CATA_SET_BUTTON.pressed(tglCataMode);
  primaryController.CATA_SPEED_INC.pressed(cataInc);
  primaryController.CATA_SPEED_DEC.pressed(cataDec);

  //Clear the screens and print the calibrating message for the inertial
  primaryController.Screen.clearScreen();
  primaryController.Screen.setCursor(1, 1);
  primaryController.Screen.print("Calibrating...");

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Calibrating Inertial...");

  //Calibrate the inertial
  Inertial.calibrate();

  //Allow the driver to select which handicap speed they want to use
  if(getCompetitionStatus() != disabled)
  {
    printf("Run handicap config\n");
    setTurnHandicap();
  }

  //Wait for the inertial to finish calibrating
  while(Inertial.isCalibrating())
  {
    this_thread::sleep_for(10);
  }

  //Setup the drivetrain for autonomous
  autoDrivetrain.setDriveVelocity(20, percent);
  autoDrivetrain.setTurnVelocity(20, percent);

  //Retract the wings
  wingPistons.set(false);

  //Configure the starting values for the catapult
  cataStartAngle = cataSensor.angle(deg);
  currentCataAngle = cataSensor.angle(deg) - cataStartAngle;

  printf("Start UI Setup\n");

  //*Setup the UI
  //Add the buttons to the preauto
  UI.addButton(green, "Goal Side Simp", "Goes back then forward", UI.Icons.number0);
  UI.addBlank();
  UI.addButton(0xff10a0, "Skills", "Shoots all the match loads into the field.", UI.Icons.skills);
  UI.addButton(blue, "Goal Side", "Auto for pushing in a nugget in on either side.", UI.Icons.rightArrow);
  UI.addBlank();
  UI.addBlank();
  UI.addButton(ClrGray, "Do Nothing", "Auto that does nothing.", UI.Icons.exclamationMark);
  UI.addButton(blue, "Load", "Auto for a robot on the loading side of the field.", UI.Icons.leftArrow);

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
  UI.selectButton(3, true);
  UI.setDisplayTime(1500);

  //Start the UI
  UI.startUIThreads();

  printf("Done with preauto\n");
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
  //Times how long the auto runs
  timer autoTimer = timer();

  // Select which auto to run based on what button is pressed
  switch (UI.getProgNumber())
  {
    case 0: // Goal side simp
      autoDrivetrain.setDriveVelocity(100, pct);
      autoDrivetrain.driveFor(directionType::rev, 42, distanceUnits::in);
      autoDrivetrain.driveFor(directionType::fwd, 12, distanceUnits::in);

      break;
    case 2: // Skills
      cataMotor.spin(forward, 80, percent);

      break;
    case 3: // Goal Side
      //set speeds
      autoDrivetrain.setDriveVelocity(50, percent);
      autoDrivetrain.setTurnVelocity(6, percent);
      autoDrivetrain.setTurnThreshold(2);
      autoDrivetrain.setTurnConstant(.5);

      //drop intake and grab first ball
      cataMotor.spin(fwd, 80, pct);
      intakeMotor.spin(fwd, 100, pct);
      vex::task::sleep(750);
      cataMotor.stop(coast);
      intakeMotor.stop();

      //first drive move before dropping match load ball
      autoDrivetrain.driveFor(50, inches);
      autoDrivetrain.turnFor(right, 60, deg);

      //drop match load ball
      intakeMotor.spin(reverse, 100, pct);
      vex::task::sleep(750);
      intakeMotor.stop();

      //aim and grab second ball
      autoDrivetrain.setDriveVelocity(30, pct);
      autoDrivetrain.turnFor(left, 85, deg);
      intakeMotor.spin(fwd, 100, pct);
      autoDrivetrain.driveFor(18, inches);
      intakeMotor.stop();

      //drop second ball
      autoDrivetrain.turnToHeading(90, deg);
      autoDrivetrain.driveFor(12, inches);
      intakeMotor.spin(reverse, 100, pct);
      vex::task::sleep(750);
      intakeMotor.stop();

      //grab ball 3
      autoDrivetrain.driveFor(-6, inches);
      autoDrivetrain.turnFor(right, 180, deg);
      intakeMotor.spin(fwd, 100, pct);
      autoDrivetrain.driveFor(16, inches);

      //goal Ram
      autoDrivetrain.driveFor(-32, inches);
      autoDrivetrain.driveFor(12, inches);
      autoDrivetrain.turnFor(left, 180, deg);

      //drop last ball
      autoDrivetrain.setDriveVelocity(100, pct);
      intakeMotor.spin(reverse, 100, pct);
      vex::task::sleep(100);
      autoDrivetrain.driveFor(6, inches);
      autoDrivetrain.driveFor(-6, inches);

      /* old code
        //Set base speeds
        autoDrivetrain.setDriveVelocity(20, percent);
        autoDrivetrain.setTurnVelocity(5, percent);
        autoDrivetrain.setTurnThreshold(1);

        //Turn and remove triball
        wingPistons.set(true);
        autoDrivetrain.driveFor(directionType::rev, 4, distanceUnits::in);
        autoDrivetrain.turnFor(turnType::left, 45, rotationUnits::deg);
        autoDrivetrain.turnFor(turnType::right, 5, rotationUnits::deg);

        //Wait for triballs to calm down
        //wait(100, msec);

        //Ram the triballs into the goal.
        autoDrivetrain.drive(directionType::rev, 100, velocityUnits::pct);
        wait(1000, msec);
        autoDrivetrain.setDriveVelocity(20, percent);
        autoDrivetrain.driveFor(directionType::fwd, 15, distanceUnits::in);
        wingPistons.set(false);
        autoDrivetrain.turnFor(turnType::right, 30, rotationUnits::deg);
        autoDrivetrain.drive(directionType::rev, 100, velocityUnits::pct);
        wait(1000, msec);
        autoDrivetrain.driveFor(directionType::fwd, 15, distanceUnits::in); */

      break;

    case 7: // Load side
      autoDrivetrain.setDriveVelocity(20, percent);
      autoDrivetrain.setTurnVelocity(5, percent);
      autoDrivetrain.setTurnThreshold(1);

      autoDrivetrain.driveFor(directionType::fwd, 14, distanceUnits::in);
      wingPistons.set(true);
      autoDrivetrain.turnFor(turnType::left, 45, rotationUnits::deg);
      wingPistons.set(false);
      autoDrivetrain.turnFor(turnType::left, 150, rotationUnits::deg);

      break;

    case 6: //Do nothing auto
      //! NO CODE HERE
      break;

    default:
      break;
  }

  printf("Auto Time: %f seconds.\n", autoTimer.value());
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
  //Stores the previous speed of the catapult
  //int cataSpeed_old = cataSpeed;

  //Print out catapult speed to the terminal
  printf("Speed: %i\n", cataSpeed);

  // Set stopping modes for the base motors
  leftMotors.setStopping(brake);
  rightMotors.setStopping(brake);

  // User control code here, inside the loop
  while(true)
  {
    //! ------------------------- make it drive -----------------------
    //Get the speed for the left and right side motors
    leftSpeed = ((primaryController.Axis3.position() * DRIVE_HANDICAP)
               + (primaryController.Axis1.position() * turnHandicap));

    rightSpeed = ((primaryController.Axis3.position() * DRIVE_HANDICAP)
                - (primaryController.Axis1.position() * turnHandicap));

    //Set the speed of the left and right motors
    leftMotors.spin(fwd, leftSpeed, pct);
    rightMotors.spin(fwd, rightSpeed, pct);

    //! --------------------- control cata -------------------------
    //Keep track of the catapult speed and log when it changes
    /* if(cataSpeed != cataSpeed_old)
    {
      //printf("Speed: %i\n", cataSpeed);

      cataSpeed_old = cataSpeed;
    }

    //Get the angle of the catapult
    currentCataAngle = cataSensor.angle(deg) - cataStartAngle;

    //Run cata control code if the stop button isn't pressed
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

    //Print out the angle of the catapult
    printf("\n%f\n\n", currentCataAngle); */

    if(primaryController.CATA_FIRE_BUTTON.pressing())
    {
      cataMotor.spin(fwd, cataSpeed, pct);
    }

    else if(primaryController.CATA_STOP_BUTTON.pressing())
    {
      cataMotor.stop(coast);
    }

    else
    {
      cataMotor.stop(hold);
    }

    //! --------------------- control intake -------------------------
    if(primaryController.INTK_IN_BUTTON.pressing()) {
      intakeMotor.spin(fwd, intakeSpeed, pct);
    } else if(primaryController.INTK_OUT_BUTTON.pressing()) {
      intakeMotor.spin(reverse, intakeSpeed, pct);
    } else {
      intakeMotor.stop();
    }

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
  while(true)
  {
    //Store parameters to display on the screens
    robotBatteryCapacity = (int)Brain.Battery.capacity();
    robotBatteryVolt = Brain.Battery.voltage();
    robotBatteryCurrent = Brain.Battery.current();

    // Wait to allow other threads to use the CPU
    wait(50, msec);
  }
}