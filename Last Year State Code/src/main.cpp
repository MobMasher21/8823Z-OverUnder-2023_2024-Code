// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// trigger              digital_out   B               
// stringLauncher       digital_out   A               
// rollerDistance       distance      17              
// ---- END VEXCODE CONFIGURED DEVICES ----

// --- Start EVAPI CONFIGURED DEVICES -------
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// primaryController    Controller
// secondaryController  Controller             
// ---- END EVAPI CONFIGURED DEVICES ------

/** code ideas
* write automatic controller debouncing code as a class
*/

#include "vex.h"
#include "Robot.h"
#include "robotMonitoring.h"
#include "evAPI.h"

using namespace evAPI;

void printProgName();

goodUI UI(printProgName);

#define HANDICAP 1
#define TURN_HANDICAP .8
#define SHOOTING_HANDICAP .3

#define SHORTRANGE_FLYWHEEL_SPEED 70
#define LONGRANGE_FLYWHEEL_SPEED 95
#define SHORTRANGE_FLYWHEEL_SPEED_VOLT  (12 * (.01 * SHORTRANGE_FLYWHEEL_SPEED))
#define LONGRANGE_FLYWHEEL_SPEED_VOLT (12 * (.01 * LONGRANGE_FLYWHEEL_SPEED))

#define DIRECTIONAL_TURNING_DEGREES 40
#define Turning_P 0.2

#define MIN_ROLLER_DISTANCE 33
 
int leftSpeed;
int rightSpeed;
double shootModeSpeed;
bool tglKickFlip;
bool kickFlipBounce;

bool TEST_MODE = false;

bool tglFlywheel;
bool tglLongRange;
bool flywheelBounce;
bool longRangeBounce;

bool rollerBounce;

void rollerCheckingFunc()
{
  bool prevRollerState;

  while (1)
  {
    robot.rollers.rollerCheckLoop();

    //Rumbles the controller once the roller has been changed
    if(!robot.rollers.isChangingRoller() && prevRollerState) 
    { primaryController.rumble("."); }

    prevRollerState = robot.rollers.isChangingRoller();
    this_thread::sleep_for(10);
  }
}

void printProgName() {
  switch(UI.getProgNumber()) {
    case 0:
      Brain.Screen.print("High Goal");
      Brain.Screen.newLine();
      Brain.Screen.print("Left Roller");
      Brain.Screen.newLine();
      Brain.Screen.print("Blue");
      robotInfo.setAlliance(blueAlliance);
      printf("Blue Alliance\n");
      break;

    case 1:
      Brain.Screen.print("Low Goal");
      Brain.Screen.newLine();
      Brain.Screen.print("Right Roller");
      Brain.Screen.newLine();
      Brain.Screen.print("Blue");
      robotInfo.setAlliance(blueAlliance);
      printf("Blue Alliance\n");
      break;

    case 3:
      Brain.Screen.print("Skills Auto 1");
      robotInfo.setAlliance(redAlliance);
      printf("Red Alliance\n");
      break;

    case 4:
      Brain.Screen.print("High Goal");
      Brain.Screen.newLine();
      Brain.Screen.print("Left Roller");
      Brain.Screen.newLine();
      Brain.Screen.print("Red");
      robotInfo.setAlliance(redAlliance);
      printf("Red Alliance\n");
      break;

    case 5:
      Brain.Screen.print("Low Goal");
      Brain.Screen.newLine();
      Brain.Screen.print("Right Roller");
      Brain.Screen.newLine();
      Brain.Screen.print("Red");
      robotInfo.setAlliance(redAlliance);
      printf("Red Alliance\n");
      break;

    case 7:
      Brain.Screen.print("Skills Auto 2");
      robotInfo.setAlliance(redAlliance);
      printf("Red Alliance\n");
      break;

    case 8:
      Brain.Screen.print("!! TEST MODE !!");
      TEST_MODE = true;
      Brain.Screen.newLine();
      Brain.Screen.print("Red Alliance");
      robotInfo.setAlliance(redAlliance);
      printf("Red Alliance\n");
      break;

    case 9:
      Brain.Screen.print("2 preloads");
      robot.rollers.setDiskCount(2);
      Brain.Screen.newLine();
      Brain.Screen.print("Blue");
      robotInfo.setAlliance(blueAlliance);
      printf("Blue Alliance\n");
      break;

    case 10:
      Brain.Screen.print("1 preloads");
      robot.rollers.setDiskCount(1);
      Brain.Screen.newLine();
      Brain.Screen.print("Blue");
      robotInfo.setAlliance(blueAlliance);
      printf("Blue Alliance\n");
      break;

    case 11:
      Brain.Screen.print("0 preloads");
      robot.rollers.setDiskCount(0);
      Brain.Screen.newLine();
      Brain.Screen.print("Blue");
      robotInfo.setAlliance(blueAlliance);
      printf("Blue Alliance\n");
      break;

    case 12:
      Brain.Screen.print("Calibrating");
      Brain.Screen.newLine();
      Brain.Screen.print("Inertial!");

      Odometry.Inertial.calibrate();
      while(Odometry.Inertial.isCalibrating())
      { task::sleep(10); }

      break;

    case 13:
      Brain.Screen.print("2 preloads");
      robot.rollers.setDiskCount(2);
      Brain.Screen.newLine();
      Brain.Screen.print("Red");
      robotInfo.setAlliance(redAlliance);
      printf("Red Alliance\n");
      break;

    case 14:
      Brain.Screen.print("1 preloads");
      robot.rollers.setDiskCount(1);
      Brain.Screen.newLine();
      Brain.Screen.print("Red");
      robotInfo.setAlliance(redAlliance);
      printf("Red Alliance\n");
      break;

    case 15:
      Brain.Screen.print("0 preloads");
      robot.rollers.setDiskCount(0);
      Brain.Screen.newLine();
      Brain.Screen.print("Red");
      robotInfo.setAlliance(redAlliance);
      printf("Red Alliance\n");
      break;

    default:
      Brain.Screen.print("INVALID!");
      printf("Invalid icon ID!\n");
      break;
  }
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

void pre_auton(void) {

  primaryController.rumble(".."); //Doot! Doot!

  //================= drivetrain setup =======================

  robot.drive.setDebugState(false);
  robot.drive.setGearbox(robot.blue);
  robot.drive.leftPortSetup(12, 13);
  robot.drive.rightPortSetup(19, 20);
  robot.drive.leftReverseSetup(false, true);
  robot.drive.rightReverseSetup(false, true);
  robot.drive.geartrainSetup(3.25, 48, 72);

  //=============== roller setup code ========================

  robot.rollers.setDebugState(true);
  robot.rollers.setupIntakeMotor(16, false, robot.green);
  robot.rollers.setupRollerMotor(7, true, robot.red);
  robot.rollers.setupRollerSensors(8, 9);

  //================= flywheel setup code ====================
  
  robot.flywheel.setGearbox(robot.blue);
  robot.flywheel.setupMotors(2, false);

  //======================= Odometry Setup ============================

  Odometry.Inertial.createInertial(1);
  Odometry.Inertial.calibrate();

  Odometry.Core.useInertial(true);

  Odometry.Core.createEncoders(14, false, 15, true, 18, true);
  Odometry.Core.configureEncoderWheels(2.5, 2.5, 4.5, 3.25);

  //====================== UI setup ==========================

  Brain.Screen.print("Calibrating Inertial!");
  while(Odometry.Inertial.isCalibrating())
  { task::sleep(5); }


  Brain.Screen.clearScreen();

  UI.addButton(blue, UI.Icons.leftArrow); //Left Auto Blue
  UI.addButton(blue, UI.Icons.rightArrow); //Right Auto Blue
  UI.addBlank();
  UI.addButton(0xFF, 0x10, 0xA0, UI.Icons.skills); //Skills 1
  UI.addButton(red, UI.Icons.leftArrow); //Left Auto Red
  UI.addButton(red, UI.Icons.rightArrow); //Right Auto Red
  UI.addBlank();
  UI.addButton(cyan, UI.Icons.skills); //Skills 2
  //New Page
  UI.addButton(cyan, UI.Icons.exclamationMark); //Test
  UI.addButton(blue, UI.Icons.number2); //Blue 2 preloads
  UI.addButton(blue, UI.Icons.number1); //Blue 1 preload
  UI.addButton(blue, UI.Icons.number0); //Blue 0 preloads
  UI.addButton(cyan, UI.Icons.inertialReset); //Reset Inertial
  UI.addButton(red, UI.Icons.number2); //Red 2 preloads
  UI.addButton(red, UI.Icons.number1); //Red 1 preload
  UI.addButton(red, UI.Icons.number0); //Red 0 preloads
  //New Page

  primaryController.rumble("."); //Doot!

  UI.selectButton(7);

  
  //====================== Other ==========================

  //robotInfo.Competition.bStopAllTasksBetweenModes = false;
  //robotInfo.Competition.bStopTasksBetweenModes = false;
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

  robotInfo.autonStart();
  robot.rollers.rollerAssistStatus(false);

  printf("\n\nStarted Auton!\n\n");

  switch(UI.getProgNumber())
  {
    case 0: //High Goal and Roller Red
      robot.rollers.setDiskCount(2);
      robot.drive.setDriveSpeed(70);
      robot.drive.setTurnSpeed(10);

      //Odometry.Core.startingParameters(0, 0, 0);
      //Odometry.Core.startOdometry();

      robot.flywheel.spinFlywheel(11);
      vex::task::sleep(3200);
      robot.rollers.diskFire();
      vex::task::sleep(800);
      robot.rollers.diskFire();
      vex::task::sleep(50);
      robot.rollers.diskFire();
      robot.flywheel.stopFlywheel();

      robot.drive.spinBase(-15, 15);
      vex::task::sleep(1000);
      robot.drive.stopRobot();

      robot.drive.spinBase(30, 30);
      vex::task::sleep(200);
      robot.drive.stopRobot();

      robot.drive.spinBase(-15, 15);
      vex::task::sleep(1000);
      robot.drive.stopRobot();
      vex::task::sleep(200);

      robot.rollers.spinRoller(60);
      robot.drive.spinBase(30, 30);
      vex::task::sleep(250);
      robot.drive.stopRobot();
      vex::task::sleep(200);
      robot.rollers.stopRoller();
      break;

    case 1: //Low Goal and Roller Red
      robot.rollers.setDiskCount(2);
      robot.drive.setDriveSpeed(30);
      robot.drive.setTurnSpeed(15);

      //Odometry.Core.startingParameters(0, 0, 0);
      //Odometry.Core.startOdometry();

      robot.flywheel.spinFlywheel(5);
      vex::task::sleep(1000);
      robot.rollers.diskFire();
      task::sleep(250);
      robot.rollers.diskFire();
      task::sleep(250);
      robot.rollers.diskFire();
      robot.flywheel.stopFlywheel();

      robot.drive.spinBase(-30, -29);
      vex::task::sleep(2600);
      robot.drive.stopRobot();
      
      robot.drive.spinBase(-15, 15);
      vex::task::sleep(1000);
      robot.drive.stopRobot();

      robot.rollers.spinRoller(60);

      robot.drive.spinBase(30, 30);
      vex::task::sleep(600);
      robot.drive.stopRobot();
      robot.rollers.stopRoller();
      
      break;

    case 3: //Skills 1
      robot.rollers.setDiskCount(2); //Setup autonomous
      robot.drive.setDriveSpeed(45);
      robot.drive.setTurnSpeed(15);

      //Odometry.Core.startingParameters(0, 0, 0);
      //Odometry.Core.startOdometry();

      robot.flywheel.spinFlywheel(70);
      task::sleep(2000);
      robot.rollers.diskFire();
      robot.rollers.diskFire();
      task::sleep(500);
      robot.rollers.diskFire();
      robot.flywheel.stopFlywheel();

      robot.rollers.spinIntake(100);

      robot.drive.spinBase(-20, -20);
      task::sleep(850);
      robot.drive.spinBase(10, -10);
      task::sleep(1500);
      robot.drive.spinBase(20, 20);
      task::sleep(1200);

      robot.drive.spinBase(1, 1);
      robot.rollers.spinRoller(60);
      task::sleep(500);
      robot.rollers.stopRoller();

      robot.drive.spinBase(-20, -20);
      task::sleep(1000);
      robot.drive.spinBase(10, -10);
      task::sleep(6900);
      robot.drive.stopRobot();
      stringLauncher.set(true);
      break;
      
    case 4: //High Goal and Roller Blue
      robot.rollers.setDiskCount(2);
      robot.drive.setDriveSpeed(70);
      robot.drive.setTurnSpeed(10);

      //Odometry.Core.startingParameters(0, 0, 0);
      //Odometry.Core.startOdometry();

      robot.flywheel.spinFlywheel(11);
      vex::task::sleep(3200);
      robot.rollers.diskFire();
      vex::task::sleep(800);
      robot.rollers.diskFire();
      vex::task::sleep(50);
      robot.rollers.diskFire();
      robot.flywheel.stopFlywheel();

      robot.drive.spinBase(-15, 15);
      vex::task::sleep(1000);
      robot.drive.stopRobot();

      robot.drive.spinBase(30, 30);
      vex::task::sleep(200);
      robot.drive.stopRobot();

      robot.drive.spinBase(-15, 15);
      vex::task::sleep(1000);
      robot.drive.stopRobot();
      vex::task::sleep(200);

      robot.rollers.spinRoller(60);
      robot.drive.spinBase(30, 30);
      vex::task::sleep(250);
      robot.drive.stopRobot();
      vex::task::sleep(200);
      robot.rollers.stopRoller();

      break;

    case 5: //Low Goal and Roller Blue
      robot.rollers.setDiskCount(2);
      robot.drive.setDriveSpeed(30);
      robot.drive.setTurnSpeed(15);

      //Odometry.Core.startingParameters(0, 0, 0);
      //Odometry.Core.startOdometry();

      robot.flywheel.spinFlywheel(5);
      vex::task::sleep(1000);
      robot.rollers.diskFire();
      task::sleep(250);
      robot.rollers.diskFire();
      task::sleep(250);
      robot.rollers.diskFire();
      robot.flywheel.stopFlywheel();

      robot.drive.spinBase(-30, -29);
      vex::task::sleep(2600);
      robot.drive.stopRobot();
      
      robot.drive.spinBase(-15, 15);
      vex::task::sleep(1000);
      robot.drive.stopRobot();

      robot.rollers.spinRoller(60);

      robot.drive.spinBase(30, 30);
      vex::task::sleep(600);
      robot.drive.stopRobot();
      robot.rollers.stopRoller();
      
      break;

    case 7: //Skills 2

      robot.drive.setDriveSpeed(50);
      robot.drive.setTurnSpeed(50);

      robotInfo.setAlliance(redAlliance);

      robot.rollers.rollerAssistStatus(true);

      robot.drive.driveForward(20); //Drive to roller.
      task::sleep(20);
      robot.drive.turnToHeading(275, 25);
      task::sleep(20);
      robot.drive.driveForward(24.5);

      robot.drive.spinBase(5, 5); //Roll Roller.
      while(rollerDistance.objectDistance(mm) >= MIN_ROLLER_DISTANCE)
      { task::sleep(10); }
      robot.drive.spinBase(1, 1);
      task::sleep(50);
      while(!robot.rollers.isChangingRoller()) task::sleep(20);
      task::sleep(20);
      robot.drive.stopRobot();

      robot.drive.driveBackward(12.5); //Drive roller and get disk
      robot.rollers.spinIntake(-60);
      robot.drive.turnToHeading(185, 30);
      robot.drive.driveForward(26.4);

      robot.drive.spinBase(5, 5); //Roll Roller.
      while(rollerDistance.objectDistance(mm) >= MIN_ROLLER_DISTANCE)
      { task::sleep(10); }
      robot.drive.spinBase(1, 1);
      task::sleep(50);
      while(!robot.rollers.isChangingRoller()) task::sleep(20);
      task::sleep(20);
      robot.drive.stopRobot();

      robot.flywheel.spinFlywheel(9.3); //Turn on flywheel.
      
      robot.rollers.spinIntake(60); //Pull down disk to prevent jams
      task::sleep(550);
      robot.rollers.stopIntake();

      robot.drive.driveBackward(10); //Turn to goal
      task::sleep(20);
      robot.drive.turnToHeading(95);

      task::sleep(600);             //Shoot 3 disks. 1 Extra Shot.
      robot.rollers.diskFire();
      task::sleep(1200);
      robot.rollers.diskFire();
      robot.rollers.spinIntake(-100);
      task::sleep(1600);
      robot.rollers.diskFire();
      task::sleep(1200);
      robot.rollers.diskFire();
      robot.rollers.stopIntake();
      robot.flywheel.stopFlywheel();

      /* robot.drive.turnToHeading(50); //Pick up 3 disks
      task::sleep(80);
      robot.rollers.spinIntake(-100);
      robot.drive.driveForward(50, 55);
      task::sleep(20);
      robot.drive.turnToHeading(90);
      task::sleep(20);
      robot.drive.driveForward(24);
      robot.flywheel.spinFlywheel(8); //Turn on flywheel.
      task::sleep(20);

      robot.drive.turnToHeading(136); //Turn to Goal

      robot.rollers.spinIntake(60); //Pull down disk to prevent jams
      task::sleep(550);
      robot.rollers.stopIntake();

      task::sleep(500);             //Shoot 3 disks. 1 Extra Shot.
      robot.rollers.diskFire();
      task::sleep(1200);
      robot.rollers.diskFire();
      robot.rollers.spinIntake(-100);
      task::sleep(1600);
      robot.rollers.diskFire();
      task::sleep(1200);
      robot.rollers.diskFire();
      robot.rollers.stopIntake();
      robot.flywheel.stopFlywheel();

      robot.drive.turnToHeading(60); //Get 3 disks
      robot.rollers.spinIntake(-100);
      task::sleep(20);
      robot.drive.driveForward(56, 40);
      task::sleep(20);
      robot.drive.turnToHeading(1);
      task::sleep(20);
      robot.drive.driveForward(25, 40);
      task::sleep(20);

      robot.drive.driveBackward(12.5); //Get to roller
      task::sleep(20);
      robot.drive.turnToHeading(96);
      task::sleep(20);
      robot.drive.driveForward(10.8); */
      
      robot.drive.turnToHeading(50, 30); //Go across the feild
      task::sleep(20);
      robot.drive.driveForward(145);
      task::sleep(20);
      robot.drive.driveBackward(23);
      task::sleep(20);
      robot.drive.turnToHeading(96);
      robot.rollers.spinIntake(-100);
      robot.drive.driveForward(22);

      robot.drive.spinBase(5, 5); //Roll Roller.
      while(rollerDistance.objectDistance(mm) >= MIN_ROLLER_DISTANCE)
      { task::sleep(10); }
      robot.drive.spinBase(1, 1);
      task::sleep(50);
      while(!robot.rollers.isChangingRoller()) task::sleep(20);
      task::sleep(20);
      robot.drive.stopRobot();
      robot.rollers.stopIntake();

      robot.drive.driveBackward(17);
      task::sleep(20);
      robot.drive.turnToHeading(10);
      task::sleep(20);
      robot.drive.driveForward(24);

      robot.drive.spinBase(5, 5); //Roll Roller.
      while(rollerDistance.objectDistance(mm) >= MIN_ROLLER_DISTANCE)
      { task::sleep(10); }
      robot.drive.spinBase(1, 1);
      task::sleep(50);
      while(!robot.rollers.isChangingRoller()) task::sleep(20);
      task::sleep(20);
      robot.drive.stopRobot();
      robot.rollers.stopIntake();

      robot.drive.driveBackward(8);
      task::sleep(20);

      /* robot.drive.stopRobot(coast);
      break; */

      robot.drive.turnToHeading(50);

      /* robot.rollers.setDiskCount(2); //Setup autonomous
      robot.drive.setDriveSpeed(70);
      robot.drive.setTurnSpeed(15);

      //Odometry.Core.startingParameters(0, 0, 0);
      //Odometry.Core.startOdometry();

      robotInfo.setAlliance(redAlliance);

      robot.rollers.rollerAssistStatus(true);

      robot.drive.spinBase(30, 30); //Drive Forward.
      task::sleep(1100);
      robot.drive.stopRobot();

      robot.drive.spinBase(-15, 15); //Turn Left.
      task::sleep(1000);
      robot.drive.stopRobot();

      robot.drive.spinBase(30, 30); //Go to roller.
      task::sleep(1340);

      robot.drive.spinBase(1, 1); //Roll Roller.
      task::sleep(1500);
      robot.drive.stopRobot();
      
      robot.drive.spinBase(-30, -30); //Back Up.
      task::sleep(700);
      robot.drive.stopRobot();

      robot.rollers.spinIntake(-60); //Turn on intake.

      robot.drive.spinBase(-15, 15); //Turn left.
      task::sleep(1050);
      robot.drive.stopRobot();

      robot.drive.spinBase(30, 30); //Go to roller.
      task::sleep(1350);
      robot.rollers.stopIntake();

      robot.flywheel.spinFlywheel(9.4); //Turn on flywheel.

      robot.drive.spinBase(1, 1); //Roll roller.
      task::sleep(1500);
      robot.drive.stopRobot();

      robot.drive.spinBase(-30, -30); //Back Up.
      task::sleep(700);
      robot.drive.stopRobot();

      robot.drive.spinBase(-15, 15); //Turn left.
      task::sleep(1100);
      robot.drive.stopRobot();

      task::sleep(500);             //Shoot 3 disks. 1 Extra Shot.
      robot.rollers.diskFire();
      task::sleep(1200);
      robot.rollers.diskFire();
      robot.rollers.spinIntake(-100);
      task::sleep(1600);
      robot.rollers.diskFire();
      task::sleep(1200);
      robot.rollers.diskFire();
      robot.rollers.stopIntake();
      robot.flywheel.stopFlywheel();

      robot.drive.spinBase(-15, 15); //Turn left
      task::sleep(500);
      robot.drive.stopRobot();
      
      robot.rollers.spinIntake(-100); //Intake disks.

      robot.drive.spinBase(30, 30); //Drive forward across the feild.
      task::sleep(4500);
      robot.rollers.stopIntake();
      task::sleep(1700);
      robot.drive.stopRobot();
      robot.drive.spinBase(-30, -30);
      task::sleep(350);
      robot.drive.stopRobot();

      robot.drive.spinBase(15, -15); //Turn right.
      task::sleep(580);
      robot.drive.stopRobot();

      robot.drive.spinBase(30, 30); //Roll roller.
      task::sleep(1500);
      robot.drive.spinBase(1, 1);
      task::sleep(1000);
      robot.drive.stopRobot();

      robot.drive.spinBase(-30, -30); //Back up.
      task::sleep(1800);
      robot.drive.stopRobot();

      robot.drive.spinBase(-15, 15); //Turn left.
      task::sleep(450);
      robot.drive.stopRobot();

      robot.drive.spinBase(30, 30); //Go forward.
      task::sleep(1200);
      robot.drive.stopRobot();

      robot.drive.spinBase(-15, 15); //Turn left.
      task::sleep(650);
      robot.drive.stopRobot();

      robot.flywheel.spinFlywheel(9.2);
      robot.drive.spinBase(30, 30); //Roll roller.
      task::sleep(650);
      robot.drive.spinBase(1, 1);
      task::sleep(1000);

      robot.drive.spinBase(-30, -30); //Back Up.
      task::sleep(350);

      robot.drive.spinBase(-15, 15); //Turn left.
      task::sleep(1190);
      robot.drive.stopRobot();

      robot.rollers.spinIntake(100); //Prevent Disk from stopping the shooter
      task::sleep(200);
      robot.rollers.stopIntake();

      task::sleep(500);             //Shoot 3 disks. 1 Extra Shot.
      robot.rollers.diskFire();
      task::sleep(1200);
      robot.rollers.diskFire();
      robot.rollers.spinIntake(-100);
      task::sleep(1600);
      robot.rollers.diskFire();
      task::sleep(1200);
      robot.rollers.diskFire();
      robot.rollers.stopIntake();
      robot.flywheel.stopFlywheel();

      robot.drive.spinBase(15, -15); //Turn Right.
      task::sleep(1600);
      robot.drive.stopRobot(); */

      stringLauncher.set(true); //Launch String
      task::sleep(500);
      stringLauncher.set(false); 
      task::sleep(500);
      stringLauncher.set(true); 

      break;
      
    case 8: //TESTING
      robot.drive.setDriveSpeed(50); //Setup testing auto
      robot.drive.setTurnSpeed(40);

      robot.drive.driveForward(24);

      /* Odometry.Core.startingParameters(0, 0, 90);
      Odometry.Core.startOdometry();

      robot.drive.driveToPlace(60, 0);
      robot.drive.driveToPlace(60, 10);
      robot.drive.driveToPlace(0, 10);
      robot.drive.driveToPlace(0, 0); */
      
      break;

    case 9: //Used for setting disk count for blue
      robot.rollers.setDiskCount(2);
      robotInfo.setAlliance(blueAlliance);
      break;
    case 10:
      robot.rollers.setDiskCount(1);
      robotInfo.setAlliance(blueAlliance);
      break;
    case 11:
      robot.rollers.setDiskCount(0);
      robotInfo.setAlliance(blueAlliance);
      break;

    case 13: //Used for setting disk count for red
      robot.rollers.setDiskCount(2);
      robotInfo.setAlliance(redAlliance);
      break;
    case 14:
      robot.rollers.setDiskCount(1);
      robotInfo.setAlliance(redAlliance);
      break;
    case 15:
      robot.rollers.setDiskCount(0);
      robotInfo.setAlliance(redAlliance);
      break;

    default:
      break;
  }
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
  if(robot.rollers.getAutomatic() != 1) { //Turns on the rollers
    robot.rollers.toggleAutomatic();
  }

  bool enableRollerAssist = true;

  robotInfo.driverStart();

  robot.rollers.rollerAssistStatus(enableRollerAssist);

  /* bool startedTurn = false;
  bool canTurn = true;

  double startingRobotAngle;
  double stickPosition;
  double turningAmountRadians;
  double targetPointXPos;
  double targetPointYPos;
  //double angleToPoint;
  double turningSpeed; */

  while (1) {

    //-------------------------------------- base drive code -------------------------------

    /* if(!primaryController.ButtonR2.pressing())
    { //Normal Driving

      if(canTurn)
      {
        leftSpeed = (primaryController.Axis3.position(pct) + primaryController.Axis1.position(pct) 
          * TURN_HANDICAP) * HANDICAP;
        rightSpeed = (primaryController.Axis3.position(pct) - primaryController.Axis1.position(pct) 
          * TURN_HANDICAP) * HANDICAP;
      }

      else
      {
        leftSpeed = primaryController.Axis3.position(pct) * HANDICAP;
        rightSpeed = primaryController.Axis3.position(pct) * HANDICAP;
      }

      if(absf(primaryController.Axis1.position(pct) <= 5))
      { canTurn = true; }
    
      startedTurn = false;
      robot.drive.spinBase(leftSpeed, rightSpeed);
    }

    else //Servo Steering
    {
      if(!startedTurn)
      { startingRobotAngle = radians(Odometry.Inertial.angle()); }

      startedTurn = true;
      canTurn = false;

      stickPosition = (primaryController.Axis1.position(percent) / 100);
      turningAmountRadians = radians(DIRECTIONAL_TURNING_DEGREES);
      targetPointXPos = cos(startingRobotAngle + (turningAmountRadians * stickPosition));
      targetPointYPos = sin(startingRobotAngle + (turningAmountRadians * stickPosition));

      double robotPointDistance = 1; //The distance to the target point.

      double robotAngle;

      if(Odometry.Core.usingInertial()) //Converts robot angle to radians
      { robotAngle = radians(Odometry.Inertial.heading()); }

      else
      { robotAngle = radians(Odometry.Core.angle()); }

      double turningAngle;

      //Facing direction point
      double facingPointXPos = cos(robotAngle); 
      double facingPointYPos = sin(robotAngle);

      //A form of the law of cosines is used to return the angle between the direction the robot is facing.
      turningAngle = degrees(acos(((sq((targetPointXPos - facingPointXPos)) + sq((targetPointYPos - facingPointYPos)))
        - 1 - sq(robotPointDistance)) / (-2 * robotPointDistance)));

      //double xValue;
      double yValue;

      //xValue = targetPointXPos*cos(turningAngle) - targetPointYPos*sin(turningAngle);
      yValue = targetPointXPos*sin(turningAngle) + targetPointYPos*cos(turningAngle);

      if(yValue >= 0) //Needs to turn left
      { turningAngle = -turningAngle; }

      printf("turningAngle: %f\n", turningAngle);
      printf("startingRobotAngle: %f\n", startingRobotAngle);
      printf("stickPosition: %f\n", stickPosition);
      printf("targetPointX: %f\n", targetPointXPos);
      printf("targetPointY: %f\n", targetPointYPos);
      printf("yValue : %f\n\n", yValue);

      turningSpeed = turningAngle * Turning_P;

      if(absf(turningSpeed) <= 1)
      { turningSpeed = 0; }

      robot.drive.spinBase(-turningSpeed, turningSpeed);
    } */

    if(primaryController.ButtonR2.pressing()) {
      leftSpeed = (primaryController.Axis3.position(pct) + primaryController.Axis4.position(pct) * TURN_HANDICAP);
      rightSpeed = (primaryController.Axis3.position(pct) - primaryController.Axis4.position(pct) * TURN_HANDICAP);
      shootModeSpeed = SHOOTING_HANDICAP;
    } else {
      leftSpeed = (primaryController.Axis3.position(pct) + primaryController.Axis1.position(pct) * TURN_HANDICAP);
      rightSpeed = (primaryController.Axis3.position(pct) - primaryController.Axis1.position(pct) * TURN_HANDICAP);
      shootModeSpeed = 1;
    }

    leftSpeed = leftSpeed * HANDICAP * shootModeSpeed;
    rightSpeed = rightSpeed * HANDICAP * shootModeSpeed;
    
    robot.drive.spinBase(leftSpeed, rightSpeed);

    //-------------------------------------- roller drive code -----------------------------
    if(primaryController.ButtonL1.pressing() && robot.rollers.getAutomatic() == 0 && rollerBounce == 0) {  //turns on automatic mode
      robot.rollers.toggleAutomatic();
      rollerBounce = 1;
    }
    if(primaryController.ButtonL1.pressing() && robot.rollers.getAutomatic() == 1 && rollerBounce == 0) {  //turns off automatic mode
      robot.rollers.toggleAutomatic();
      robot.rollers.stopIntake();
      rollerBounce = 1;
    }
    if(primaryController.ButtonL1.pressing() == 0) {  //roller de-bouncing code
      rollerBounce = 0;
    }
    if(primaryController.ButtonB.pressing() && robot.rollers.getDrain() == 0) {  //allows you to reverse the rollers
      robot.rollers.toggleDrain();

      if(!(enableRollerAssist && primaryController.ButtonX.pressing()))
      { robot.rollers.spinRoller(-60); }
      
    } else if (primaryController.ButtonB.pressing() == 0 && robot.rollers.getDrain() == 1) {
      robot.rollers.toggleDrain();

      if(!(enableRollerAssist && primaryController.ButtonX.pressing()))
      { robot.rollers.spinRoller(60); }
    }
    
    if(primaryController.ButtonDown.pressing() || UI.getProgNumber() == TEST_MODE) {  //resets the disk count to 0
      robot.rollers.setDiskCount(0);
    }

    if(primaryController.ButtonX.pressing())
    { robot.rollers.spinRoller(40); }

    robot.rollers.automaticLoop();  //loop code for disk counts

    //---------------------------------------- flywheel code -------------------------------

    if(tglFlywheel) {
      if(!tglLongRange) {
        robot.flywheel.spinFlywheel(SHORTRANGE_FLYWHEEL_SPEED_VOLT);
      } else if(tglLongRange) {
        robot.flywheel.spinFlywheel(LONGRANGE_FLYWHEEL_SPEED_VOLT);
      }
    }

    if(primaryController.ButtonL2.pressing() && tglFlywheel == 0 && flywheelBounce == 0) {  //start flywheel
      flywheelBounce = 1;
      tglFlywheel = 1;
    } else if(primaryController.ButtonL2.pressing() && tglFlywheel == 1 && flywheelBounce == 0) {  //stop flywheel
      robot.flywheel.stopFlywheel();
      flywheelBounce = 1;
      tglFlywheel = 0;
    }
    if(primaryController.ButtonL2.pressing() == 0) {  //flywheel de-bouncing code
      flywheelBounce = 0;
    }

    if(primaryController.ButtonA.pressing() == 1 && longRangeBounce == 0 && tglLongRange == 0) {
      tglLongRange = 1;
      longRangeBounce = 1;
    } else if(primaryController.ButtonA.pressing() == 1 && longRangeBounce == 0 && tglLongRange == 1) {
      tglLongRange = 0;
      longRangeBounce = 1;
    } else if(!primaryController.ButtonA.pressing() && longRangeBounce == 1) {
      longRangeBounce = 0;
    }
    if(tglLongRange) {
      primaryController.rumble("-");
    }

    if(robot.flywheel.velocity() >= 20) //Fire the disk only if the Flywheel is on.
    { trigger.set(primaryController.ButtonR1.pressing()); }

    else
    { trigger.set(false); }

    //============================== string launch ====================================
    if( primaryController.ButtonDown.pressing()   && 
        primaryController.ButtonLeft.pressing()   && 
        primaryController.ButtonRight.pressing()  && 
        primaryController.ButtonUp.pressing()        ) {
      stringLauncher.set(true);
      if(robot.rollers.getAutomatic()) {
        robot.rollers.toggleAutomatic();
        robot.rollers.stopIntake();
      }
      primaryController.rumble("...-");
    } else {
      stringLauncher.set(false);
    }

    //=================================================================================

    vex::task::sleep(20); // Sleep the task for a short amount of time to
                          // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  //! Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Set up callbacks for autonomous and driver control periods.
  robotInfo.Competition.autonomous(autonomous);
  robotInfo.Competition.drivercontrol(usercontrol);

  thread robotCheck(robotMonitoring); //Displays info on the controllers.

  // Run the pre-autonomous function.
  pre_auton();

  robotInfo.disabledStart();

  thread rollerCheck(rollerCheckingFunc); //Controls the roller roller.

  while (true) {
    if(!robotInfo.Competition.isEnabled())
    {
      UI.pressCheck();
      robotInfo.disabledStart();
    }

    this_thread::sleep_for(50);
  }
}