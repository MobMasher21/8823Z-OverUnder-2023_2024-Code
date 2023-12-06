/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Authors:      Cameron Barclay, Jayden Liffick, Teo Carrion              */
/*    Created:      9/30/2023, 12:45:32 AM                                    */
/*    Description:  Main code for 8823Z robot.                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "../evAPI/evAPIFiles.h"
#include "RobotConfig.h"
#include "GlobalDeclarations.h"

/**
 * ! A note to anyone that will be writing code here 
 * ! All function and variable declaration are now in GlobalDeclarations.handicap
 * ! To keep things organized group together functions in their own .cpp files
 * ! Each auto should be its own function, but driver contorl can be written in main
 * 
 * ! All unused code was removed to clean up files and it can be seen in old branches
 */



/// @brief sets the turn handicap based on wether left or right is pressed
void setTurnHandicap() {
  primaryController.Screen.clearScreen();
  primaryController.Screen.setCursor(0, 0);
  primaryController.Screen.print("Set turn handicap:");
  primaryController.Screen.newLine();
  primaryController.Screen.print("Left = 0.75");
  primaryController.Screen.newLine();
  primaryController.Screen.print("Right = 0.5");

  while (!primaryController.ButtonLeft.pressing() && !primaryController.ButtonRight.pressing()) {
    this_thread::sleep_for(10);
  }

  if (primaryController.ButtonLeft.pressing()) {
    turnHandicap = LOGAN_TURNS;
  } else if (primaryController.ButtonRight.pressing()) {
    turnHandicap = ELI_TURNS;
  }

  primaryController.Screen.clearScreen();

}

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
  //*Controller button callback setup =====================================================
  primaryController.WINGS_BUTTON.pressed(tglWings);
  primaryController.CATA_SET_BUTTON.pressed(tglCataMode);
  primaryController.CATA_SPEED_INC.pressed(cataInc);
  primaryController.CATA_SPEED_DEC.pressed(cataDec);

  //*Run calibration for inertial sensor ==================================================
  //Clear the screens and print the calibrating message for the inertial
  primaryController.Screen.clearScreen();
  primaryController.Screen.setCursor(1, 1);
  primaryController.Screen.print("Calibrating...");

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Calibrating Inertial...");

  //Calibrate the inertial
  driveBase.calibrateInertial();

  //Wait for the inertial to finish calibrating
  while(driveBase.isInertialCalibrating()) {
    this_thread::sleep_for(10);
  }

  //*Run driver set turn handicap stuff ====================================================
  if(!Competition.isEnabled()) {
    printf("Run handicap config\n");
    setTurnHandicap();
  } else {
    turnHandicap = (LOGAN_TURNS + ELI_TURNS) / 2;
  }

  //*Drivetrain setup =====================================================================
  //Set speeds
  driveBase.setDriveSpeed(20);
  driveBase.setTurnSpeed(20);

  //*Set piston starting states ===========================================================
  wingPistons.set(false);  //retract wings

  //*Automatic driver control setup =======================================================
  driveControl.setHandicaps(DRIVE_HANDICAP, turnHandicap);
  driveControl.setPrimaryStick(leftStick);

  //*Setup the UI =========================================================================
  UI.addButton(0, green);
  UI.addButton(2, 0xff, 0x10, 0xa0);
  UI.addButton(3, blue);
  UI.addButton(6, Gray);
  UI.addButton(7, blue);

  UI.setButtonTitle(0, "Push In Simp");
  UI.setButtonTitle(2, "Skills");
  UI.setButtonTitle(3, "Push In");
  UI.setButtonTitle(6, "Do Nothing");
  UI.setButtonTitle(7, "Load");

  UI.setButtonDescription(0, "Goes back then forward");
  UI.setButtonDescription(2, "Shoots all the match loads into the field.");
  UI.setButtonDescription(3, "Auto for pushing in a nugget in on either side.");
  UI.setButtonDescription(6, "Auto that does nothing.");
  UI.setButtonDescription(7, "Auto for a robot on the loading side of the field.");

  UI.setButtonIcon(0, UI.icons.number0);
  UI.setButtonIcon(2, UI.icons.skills);
  UI.setButtonIcon(3, UI.icons.rightArrow);
  UI.setButtonIcon(6, UI.icons.exclamationMark);
  UI.setButtonIcon(7, UI.icons.leftArrow);

  //Setup default selection
  UI.setSelectedButton(7);

  //Set time that button data will be on screen
  UI.setDataDisplayTime(2000);

  //Start the UI
  UI.startThread();

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
  switch (UI.getSelectedButton())
  {
    case 0:
      autoDrivetrain.setDriveVelocity(100, pct);
      autoDrivetrain.driveFor(directionType::rev, 42, distanceUnits::in);
      autoDrivetrain.driveFor(directionType::fwd, 12, distanceUnits::in);

      break;
    case 2: // Skills
      cataMotor.spin(forward, 80, percent);

      break;
    case 3: // Push in
      // Extend the wings
      /* wingPistons.set(true);
      this_thread::sleep_for(100);

      // Set speed parameters for the drivetrain
      autoDrivetrain.setDriveVelocity(10, percent);
      autoDrivetrain.setTurnVelocity(5, percent);
      autoDrivetrain.setTurnThreshold(5);

      // Remove nugget from match loading zone
      autoDrivetrain.driveFor(reverse, 4, distanceUnits::in);
      autoDrivetrain.turnFor(turnType::left, 45, rotationUnits::deg); */

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
      autoDrivetrain.driveFor(directionType::fwd, 15, distanceUnits::in);

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

  // User control code here, inside the loop
  while(true)
  {
    //! ------------------------- make it drive -----------------------
    driveControl.driverLoop();

    //! --------------------- control cata -------------------------
    if(primaryController.CATA_FIRE_BUTTON.pressing()) {
      cataMotor.spin(fwd, cataSpeed, pct);
    } else if(primaryController.CATA_STOP_BUTTON.pressing()) {
      cataMotor.stop(coast);
    } else {
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