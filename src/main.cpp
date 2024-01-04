/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Cameron Barclay, Jayden Liffick, Teo Carrion              */
/*    Created:      12/6/2023, 10:45:31 PM                                    */
/*    Description:  All code for team 8823Z robot.                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

//$ To keep things clean, declare functions at the top and write what they do at the bottom

// Include library files
#include "vex.h"
#include "../evAPI/evAPIFiles.h"

// Select namespaces ------------------------------------------------------
using namespace vex;
using namespace evAPI;

// Setup global objects ---------------------------------------------------
Drive driveBase = Drive(blueGearBox);
DriverBaseControl driveControl = DriverBaseControl(&primaryController, RCControl, &driveBase);

// Setup vex component objects (motors, sensors, etc.) --------------------
digital_out *wingPistons;
motor cataMotor = motor(PORT8, redGearBox, true);
motor intakeMotor = motor(PORT5, blueGearBox, false);

// Controller callback function declarations ------------------------------
void tglWings( void );  // Toggles the state of the wing pistons

// Setup controller button names ------------------------------------------
#define CATA_FIRE_BUTTON ButtonR2
#define CATA_SET_BUTTON ButtonA
#define CATA_STOP_BUTTON ButtonX
#define CATA_SPEED_INC ButtonUp
#define CATA_SPEED_DEC ButtonDown
#define INTK_IN_BUTTON ButtonL1
#define INTK_OUT_BUTTON ButtonL2
#define WINGS_BUTTON ButtonR1

// Speed and handicap variables -------------------------------------------
int intakeSpeed = 100;
int cataSpeed = 75;

//Setup Auto Button UI IDs
enum autoOptions {
  AUTO_DO_NOTHING = 4,
  PID_TEST = 0,
  AUTO_GOAL_SIDE = 3,
  AUTO_LOAD_SIDE = 7,
  AUTO_BASIC_SKILLS = 8,
  AUTO_BASIC_GOAL_SIDE = 11,
  AUTO_BASIC_LOAD_SIDE = 15
};

//Variables to display on the controller
uint32_t batteryLevel = Brain.Battery.capacity();
double batteryCurrent = Brain.Battery.current();

//Setup controller UI IDs
#define CONTROLLER_BATTERY_CAPACITY 0
#define CONTROLLER_BATTERY_CURRENT 1

/*---------------------------------------------------------------------------------*/
/*                             Pre-Autonomous Functions                            */
/*---------------------------------------------------------------------------------*/
void pre_auton(void) {
  //* Set object pointers ====================================================
  wingPistons = new digital_out(Brain.ThreeWirePort.A);

  //* Setup for auto selection UI ============================================
  // Add all the buttons
  UI.autoSelectorUI.addButton(PID_TEST, 0xff, 0x10, 0xa0);  //color is 0xff10a0
  UI.autoSelectorUI.addButton(AUTO_GOAL_SIDE, blue);
  UI.autoSelectorUI.addButton(AUTO_LOAD_SIDE, blue);
  UI.autoSelectorUI.addButton(AUTO_DO_NOTHING, red);
  UI.autoSelectorUI.addButton(AUTO_BASIC_SKILLS, LightSlateGray);
  UI.autoSelectorUI.addButton(AUTO_BASIC_GOAL_SIDE, Lime);
  UI.autoSelectorUI.addButton(AUTO_BASIC_LOAD_SIDE, Lime);

  // Set all the titles
  UI.autoSelectorUI.setButtonTitle(PID_TEST, "PID TEST");
  UI.autoSelectorUI.setButtonTitle(AUTO_GOAL_SIDE, "Goal Side");
  UI.autoSelectorUI.setButtonTitle(AUTO_LOAD_SIDE, "Load Side");
  UI.autoSelectorUI.setButtonTitle(AUTO_DO_NOTHING, "DO NOTHING!");
  UI.autoSelectorUI.setButtonTitle(AUTO_BASIC_SKILLS, "Basic Skills");
  UI.autoSelectorUI.setButtonTitle(AUTO_BASIC_GOAL_SIDE, "Push in simple");
  UI.autoSelectorUI.setButtonTitle(AUTO_BASIC_LOAD_SIDE, "Descore Triball");

  // Set all the descriptions
  UI.autoSelectorUI.setButtonDescription(PID_TEST, "Simple movements to test PID settings");
  UI.autoSelectorUI.setButtonDescription(AUTO_GOAL_SIDE, "Scores three triballs, including the match load, and touches the bar.");
  UI.autoSelectorUI.setButtonDescription(AUTO_LOAD_SIDE, "Scores the match load, pushes two triballs to the other side, and touches the bar.");
  UI.autoSelectorUI.setButtonDescription(AUTO_DO_NOTHING, "The robot will do nothing.");
  UI.autoSelectorUI.setButtonDescription(AUTO_BASIC_SKILLS, "Launches all the match loads into the field.");;
  UI.autoSelectorUI.setButtonDescription(AUTO_BASIC_GOAL_SIDE, "Ram backward, then go forward.");
  UI.autoSelectorUI.setButtonDescription(AUTO_BASIC_LOAD_SIDE, "Descore the triball from the match load zone.");

  // Select all the icons
  UI.autoSelectorUI.setButtonIcon(PID_TEST, UI.autoSelectorUI.icons.skills);
  UI.autoSelectorUI.setButtonIcon(AUTO_GOAL_SIDE, UI.autoSelectorUI.icons.leftArrow);
  UI.autoSelectorUI.setButtonIcon(AUTO_LOAD_SIDE, UI.autoSelectorUI.icons.rightArrow);
  UI.autoSelectorUI.setButtonIcon(AUTO_DO_NOTHING, UI.autoSelectorUI.icons.exclamationMark);
  UI.autoSelectorUI.setButtonIcon(AUTO_BASIC_SKILLS, UI.autoSelectorUI.icons.skills);
  UI.autoSelectorUI.setButtonIcon(AUTO_BASIC_GOAL_SIDE, UI.autoSelectorUI.icons.leftArrow);
  UI.autoSelectorUI.setButtonIcon(AUTO_BASIC_LOAD_SIDE, UI.autoSelectorUI.icons.rightArrow);

  //Setup parameters for auto selector 
  UI.autoSelectorUI.setSelectedButton(PID_TEST);
  UI.autoSelectorUI.setDataDisplayTime(1500);

  //*Setup controller UI
  UI.primaryControllerUI.addData(CONTROLLER_BATTERY_CAPACITY, "Battery: ", batteryLevel);
  UI.primaryControllerUI.addData(CONTROLLER_BATTERY_CURRENT, "Battery Amps: ", batteryCurrent);

  //Start the threads
  UI.startThreads();

  //* Setup for smart drive ==================================================
  driveBase.setDebugState(true);
  // Setup motor settings
  driveBase.leftPortSetup(7, 9, 16);
  driveBase.rightPortSetup(1, 4, 14);
  driveBase.leftReverseSetup(true, true, true);
  driveBase.rightReverseSetup(false, false, false);
  driveBase.geartrainSetup(3.25, 36, 60);
  
  // Setup inertial sensor settings
  driveBase.setupInertialSensor(17);
  driveBase.calibrateInertial();

  // Set default speeds
  driveBase.setDriveSpeed(100);
  driveBase.setTurnSpeed(100);

  // Setup PID
  driveBase.setupDrivePID(.22, .040, .5, 5, 2, 100);  // p, i, d, error, error time, timeout
  driveBase.setupTurnPID(.6, 10, 0, 2, 2, 100);  // p, i, d, error, error time, timeout

  //* Setup for base driver contorl ==========================================
  driveControl.setPrimaryStick(leftStick);
  driveControl.setHandicaps(1, 1);  // main drive, turning

  //* Setup controller callbacks =============================================
  primaryController.WINGS_BUTTON.pressed(tglWings);
}


/*---------------------------------------------------------------------------------*/
/*                                 Autonomous Task                                 */
/*---------------------------------------------------------------------------------*/
void autonomous(void) {

  //Times how long auto takes
  timer autoTimer;

  switch (UI.autoSelectorUI.getSelectedButton()) {
    case PID_TEST:
      //.driveForward(24);
      //driveBase.driveBackward(24);
      driveBase.turnToHeading(90);
      driveBase.turnToHeading(0);
      break;
    case AUTO_GOAL_SIDE:
      /* //Set speeds
      autoDrivetrain.setDriveVelocity(57, percent);
      autoDrivetrain.setTurnVelocity(10, percent);
      autoDrivetrain.setTurnThreshold(2);
      autoDrivetrain.setTurnConstant(.5);

      //Drop intake and grab first ball
      cataMotor.spin(fwd, 80, pct);
      intakeMotor.spin(fwd, 100, pct);
      vex::task::sleep(750);
      cataMotor.stop(coast);
      intakeMotor.stop();

      //First drive move before dropping match load ball
      autoDrivetrain.driveFor(50, inches);
      autoDrivetrain.turnFor(right, 65, deg);

      //Drop match load ball
      intakeMotor.spin(reverse, 100, pct);
      vex::task::sleep(750);
      intakeMotor.stop();

      //Aim and grab second ball
      autoDrivetrain.setDriveVelocity(30, pct);
      autoDrivetrain.turnToHeading(302, deg);
      intakeMotor.spin(fwd, 100, pct);
      autoDrivetrain.driveFor(31, inches);
     
      //Align with goal and ram in first two triballs
      autoDrivetrain.turnToHeading(270, rotationUnits::deg);
      autoDrivetrain.setDriveVelocity(100, pct);
      wingPistons.set(true);
      autoDrivetrain.driveFor(-19, inches);
      intakeMotor.stop();
      autoDrivetrain.driveFor(-19, inches);
      autoDrivetrain.driveFor(6, inches);
      wingPistons.set(false);
      //Turn to face the goal and drop 3rd triball
      autoDrivetrain.turnFor(right, 180, deg);
      intakeMotor.spin(reverse, 100, pct);
      vex::task::sleep(750);

      //Start to push in final triball
      autoDrivetrain.driveFor(7, inches, false);

      //Lets the robot get up to speed
      vex::task::sleep(500);

      //Runs the motors until it has driven 7 inches or the velocity of the robot is less then 5
      //which occurs when the robot has ran into something and cannot move further
      while (autoDrivetrain.velocity(pct) > 5) {
        vex::task::sleep(5);
      }

      //Turn to face bar
      autoDrivetrain.driveFor(-6, inches);
      intakeMotor.stop();
      // autoDrivetrain.turnToHeading(90, deg);
      // autoDrivetrain.turnToHeading(180, deg);

      //Drive to bar
      // autoDrivetrain.driveFor(35, inches);
      // autoDrivetrain.turnFor(right, 54, deg);
      // autoDrivetrain.driveFor(24.5, inches);
      // autoDrivetrain.driveFor(3, inches, 10, velocityUnits::pct); */
      break;

    case AUTO_LOAD_SIDE:
      /* //Set drive base parameters
      autoDrivetrain.setDriveVelocity(50, percent);
      autoDrivetrain.setTurnVelocity(6, percent);
      autoDrivetrain.setTurnThreshold(2);
      autoDrivetrain.setTurnConstant(.5);
     
      //Drop intake and grab first ball
      cataMotor.spin(fwd, 80, pct);
      intakeMotor.spin(fwd, 100, pct);
      vex::task::sleep(750);
      cataMotor.stop(coast);
      intakeMotor.stop();

      //Put the match load triball into te goal
      autoDrivetrain.driveFor(55, inches);
      autoDrivetrain.turnToHeading(275, deg);
      intakeMotor.spin(reverse, 100, pct);
      vex::task::sleep(750);
      autoDrivetrain.driveFor(8, inches);
      autoDrivetrain.driveFor(-5, inches);

      //Drive to triball in match load zone
      autoDrivetrain.turnToHeading(185, deg);
      intakeMotor.stop();
      autoDrivetrain.driveFor(30, inches);
      autoDrivetrain.turnToHeading(95, deg);
      autoDrivetrain.driveFor(-35, inches);
      autoDrivetrain.turnToHeading(140, deg);

      //Remove the triball from teh load side
      autoDrivetrain.driveFor(4, inches);
      wingPistons.set(true);
      autoDrivetrain.driveFor(20, inches);
      autoDrivetrain.turnToHeading(40, deg);
      vex::task::sleep(500);
      autoDrivetrain.turnToHeading(115, deg);
      wingPistons.set(false);

      //Push the triballs onto the other side and touch the bar
      autoDrivetrain.setDriveVelocity(30, pct);
      autoDrivetrain.driveFor(12, inches);
      autoDrivetrain.turnToHeading(105, deg);
      intakeMotor.spin(fwd, 100, pct);
      autoDrivetrain.driveFor(34, inches);
      intakeMotor.spin(reverse, 100, pct); */
      break;

    //*Basic skills auto the spins the catapult
    case AUTO_BASIC_SKILLS:
      cataMotor.spin(fwd, 96, percent);
      break;

    //*Scores the prelaod triball in the goal
    case AUTO_BASIC_GOAL_SIDE:
      /* autoDrivetrain.setDriveVelocity(100, pct);
      autoDrivetrain.driveFor(directionType::rev, 42, distanceUnits::in);
      autoDrivetrain.driveFor(directionType::fwd, 12, distanceUnits::in); */
      break;

    //*Descores the triball in the match load zone 
    case AUTO_BASIC_LOAD_SIDE:
      /* autoDrivetrain.setDriveVelocity(20, percent);
      autoDrivetrain.setTurnVelocity(5, percent);
      autoDrivetrain.setTurnThreshold(1);

      autoDrivetrain.driveFor(directionType::fwd, 14, distanceUnits::in);
      wingPistons.set(true);
      autoDrivetrain.driveFor(20, inches);
      autoDrivetrain.turnToHeading(40, deg);
      vex::task::sleep(500);
      autoDrivetrain.turnToHeading(115, deg);
      wingPistons.set(false);
      autoDrivetrain.turnFor(turnType::left, 150, rotationUnits::deg); */
      break;

    //*Do nothing auto
    case AUTO_DO_NOTHING:
      //!DO NOTHING HERE
      break;

    //*Default auto that runs if an unknown ID is selected
    default:
      printf("Invalid Auto Selected.\n");
      primaryController.rumble("---");
      break;
  }

  //Print out how long the auto took
  printf("Auto Time: %f\n", autoTimer.value());
}

/*---------------------------------------------------------------------------------*/
/*                                 User Control Task                               */
/*---------------------------------------------------------------------------------*/
void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    //=========== All drivercontrol code goes between the lines ==============

    //* Control the base code -----------------------------
    driveControl.driverLoop();

    //* Control the intake code ---------------------------
    if(primaryController.INTK_IN_BUTTON.pressing()) {
      intakeMotor.spin(fwd, intakeSpeed, pct);
    } else if(primaryController.INTK_OUT_BUTTON.pressing()) {
      intakeMotor.spin(reverse, intakeSpeed, pct);
    } else {
      intakeMotor.stop(coast);
    }

    //* Control the catapult code -------------------------
    if(primaryController.CATA_FIRE_BUTTON.pressing()) {
      cataMotor.spin(fwd, cataSpeed, pct);
    } else if(primaryController.CATA_STOP_BUTTON.pressing()) {
      cataMotor.stop(coast);
    } else {
      cataMotor.stop(hold);
    }

    //========================================================================

    vex::task::sleep(20); // Sleep the task for a short amount of time to prevent wasted resources.
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
    //Update controller UI data
    batteryLevel = Brain.Battery.capacity();
    batteryCurrent = Brain.Battery.current();
    vex::task::sleep(20);
  }
}

// Controller callback definitions
void tglWings( void ) {  // Toggles the state of the wing pistons
  wingPistons->set(!wingPistons->value());
}