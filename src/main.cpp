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
#include "../evAPI/evAPIFiles.h"

// Select namespaces ------------------------------------------------------
using namespace vex;
using namespace evAPI;

// Setup global objects ---------------------------------------------------
Drive driveBase = Drive(blueGearBox);
DriverBaseControl driveControl = DriverBaseControl(&primaryController, RCControl, &driveBase);
vexUI UI;

// Setup vex component objects (motors, sensors, etc.) --------------------
motor puncherMotor = motor(PORT10, redGearBox, true);
motor intakeMotor = motor(PORT9, blueGearBox, false);
rotation puncherEncoder = rotation(PORT7, false);
digital_out *frontLeftWing;
digital_out *frontRightWing;
digital_out *backLeftWing;
digital_out *backRightWing;

// Controller callback function declarations ------------------------------
void setFrontWings(bool left, bool right); //Control the front wings
void setBackWings(bool left, bool right); //Control the back wings
void toggleFrontWings(); //Toggle the status of the front wings
void toggleBackWings(); //Toggle the status of the front wings
void toggleFrontLeft();
void toggleFrontRight();
void toggleBackLeft();
void toggleBackRight();
void puncherSpeedIncrement(void); //Increments the speed of the puncher by 5
void puncherSpeedDecrement(void); //Decrements the speed of the puncher by 5
void puncherManualToggle(void);   //Enables manual control of the puncher
void puncherModeToggle(void);     //Toggles the mode of the puncher

// Setup controller button names ------------------------------------------
#define PUNCHER_FIRE_BUTTON ButtonL1
#define PUNCHER_STOP_BUTTON ButtonL2
#define PUNCHER_MODE_BUTTON ButtonA
#define PUNCHER_MANUAL_BUTTON ButtonX
#define PUNCHER_SPEED_INC ButtonUp
#define PUNCHER_SPEED_DEC ButtonLeft

#define INTK_IN_BUTTON ButtonR1
#define INTK_OUT_BUTTON ButtonR2
#define FRONT_LEFT_WINGS_BUTTON ButtonRight
#define FRONT_RIGHT_WINGS_BUTTON ButtonY
#define BACK_LEFT_WINGS_BUTTON ButtonDown
#define BACK_RIGHT_WINGS_BUTTON ButtonB

// Speed and handicap variables -------------------------------------------
int intakeSpeed = 100;

//Setup Auto Button UI IDs
enum autoOptions {
  //*General
  //Page 1
  AUTO_SKILLS_1 = 0,
  AUTO_FOUR_BALL_GOAL_SIDE = 1,
  AUTO_DO_NOTHING = 4,
  AUTO_GOAL_SIDE = 3,
  AUTO_LOAD_SIDE = 7,

  //Page 2
  AUTO_BASIC_SKILLS = 8,
  AUTO_BASIC_GOAL_SIDE = 11,
  AUTO_BASIC_LOAD_SIDE = 15,

  //*Testing
  //Page 3
  AUTO_TEST_PID = 16
};

//Variables to display on the controller
uint32_t batteryLevel = Brain.Battery.capacity();
std::string puncherModeText = "Block";
std::string selectedAutoName = "";

//Setup controller UI IDs
enum controllerOptions
{
  //Match Screen
  MATCH_SCREEN = 0,
  PUNCHER_SPEED_DISPLAY,
  PUNCHER_MODE_TEXT,

  //Disabled / Auto Screen
  DISABLED_AUTO_SCREEN = 3,
  AUTO_MODE_LABEL,
  AUTO_MODE_TEXT,

  //Inertial Calibration Screen
  INERTIAL_CALIBRATE_SCREEN = 6,
  INERTIAL_CALIBRATING_TEXT

};

//Puncher control
enum puncherMode
{
  PUNCHER_LAUNCH = 0,
  PUNCHER_BLOCK = 1
};

const double puncherAngleLaunch = 285;
const double puncherAngleBlock = 240;
double cataStartAngle = 0;
#define CRNT_PUNCHER_ANGL (puncherEncoder.angle(deg) - cataStartAngle)
int puncherSpeed = 100;
puncherMode puncherLaunchMode = PUNCHER_BLOCK;
bool puncherAutoPrimeEnabled = true;

/*---------------------------------------------------------------------------------*/
/*                             Pre-Autonomous Functions                            */
/*---------------------------------------------------------------------------------*/
void pre_auton(void) {
  //* Set object pointers ====================================================
  frontRightWing = new digital_out(Brain.ThreeWirePort.A);
  frontLeftWing  = new digital_out(Brain.ThreeWirePort.B);
  backLeftWing   = new digital_out(Brain.ThreeWirePort.C);
  backRightWing  = new digital_out(Brain.ThreeWirePort.D);

  //* Setup for auto selection UI ============================================
  // Add all the buttons
  UI.autoSelectorUI.addButton(AUTO_SKILLS_1, 0xff, 0x10, 0xa0);  //color is 0xff10a0
  UI.autoSelectorUI.addButton(AUTO_FOUR_BALL_GOAL_SIDE, cyan);
  UI.autoSelectorUI.addButton(AUTO_GOAL_SIDE, blue);
  UI.autoSelectorUI.addButton(AUTO_LOAD_SIDE, blue);
  UI.autoSelectorUI.addButton(AUTO_DO_NOTHING, red);
  UI.autoSelectorUI.addButton(AUTO_BASIC_SKILLS, LightSlateGray);
  UI.autoSelectorUI.addButton(AUTO_BASIC_GOAL_SIDE, Lime);
  UI.autoSelectorUI.addButton(AUTO_BASIC_LOAD_SIDE, Lime);
  UI.autoSelectorUI.addButton(AUTO_TEST_PID, CadetBlue);

  // Set all the titles
  UI.autoSelectorUI.setButtonTitle(AUTO_SKILLS_1, "Skills Auto");
  UI.autoSelectorUI.setButtonTitle(AUTO_FOUR_BALL_GOAL_SIDE, "Four Ball Goal");
  UI.autoSelectorUI.setButtonTitle(AUTO_GOAL_SIDE, "Goal Side");
  UI.autoSelectorUI.setButtonTitle(AUTO_LOAD_SIDE, "Load Side");
  UI.autoSelectorUI.setButtonTitle(AUTO_DO_NOTHING, "DO NOTHING!");
  UI.autoSelectorUI.setButtonTitle(AUTO_BASIC_SKILLS, "Basic Skills");
  UI.autoSelectorUI.setButtonTitle(AUTO_BASIC_GOAL_SIDE, "Push in simple");
  UI.autoSelectorUI.setButtonTitle(AUTO_BASIC_LOAD_SIDE, "Descore Triball");
  UI.autoSelectorUI.setButtonTitle(AUTO_TEST_PID, "Test PID Control");

  // Set all the descriptions
  UI.autoSelectorUI.setButtonDescription(AUTO_SKILLS_1, "Shoots all the match loads into the field, then attempts to push them into the goal.");
  UI.autoSelectorUI.setButtonDescription(AUTO_FOUR_BALL_GOAL_SIDE, "Runs on goal side. Scores the colored ball and 3 green ones.");
  UI.autoSelectorUI.setButtonDescription(AUTO_GOAL_SIDE, "Scores three triballs, including the match load, and touches the bar.");
  UI.autoSelectorUI.setButtonDescription(AUTO_LOAD_SIDE, "Scores the match load, pushes two triballs to the other side, and touches the bar.");
  UI.autoSelectorUI.setButtonDescription(AUTO_DO_NOTHING, "The robot will do nothing.");
  UI.autoSelectorUI.setButtonDescription(AUTO_BASIC_SKILLS, "Launches all the match loads into the field.");;
  UI.autoSelectorUI.setButtonDescription(AUTO_BASIC_GOAL_SIDE, "Ram backward, then go forward.");
  UI.autoSelectorUI.setButtonDescription(AUTO_BASIC_LOAD_SIDE, "Descore the triball from the match load zone.");

  // Select all the icons
  UI.autoSelectorUI.setButtonIcon(AUTO_SKILLS_1, UI.autoSelectorUI.icons.skills);
  UI.autoSelectorUI.setButtonIcon(AUTO_FOUR_BALL_GOAL_SIDE, UI.autoSelectorUI.icons.number4);
  UI.autoSelectorUI.setButtonIcon(AUTO_GOAL_SIDE, UI.autoSelectorUI.icons.leftArrow);
  UI.autoSelectorUI.setButtonIcon(AUTO_LOAD_SIDE, UI.autoSelectorUI.icons.rightArrow);
  UI.autoSelectorUI.setButtonIcon(AUTO_DO_NOTHING, UI.autoSelectorUI.icons.exclamationMark);
  UI.autoSelectorUI.setButtonIcon(AUTO_BASIC_SKILLS, UI.autoSelectorUI.icons.skills);
  UI.autoSelectorUI.setButtonIcon(AUTO_BASIC_GOAL_SIDE, UI.autoSelectorUI.icons.leftArrow);
  UI.autoSelectorUI.setButtonIcon(AUTO_BASIC_LOAD_SIDE, UI.autoSelectorUI.icons.rightArrow);

  //Setup parameters for auto selector
  //UI.autoSelectorUI.setSelectedButton(AUTO_FOUR_BALL_GOAL_SIDE);
  UI.autoSelectorUI.setSelectedButton(AUTO_DO_NOTHING);
  UI.autoSelectorUI.setDataDisplayTime(1500);

  //*Setup controller UI
  //Driver Control Screen
  UI.primaryControllerUI.addData(MATCH_SCREEN, "Battery: ", batteryLevel);
  UI.primaryControllerUI.addData(PUNCHER_SPEED_DISPLAY, "Puncher Speed: ", puncherSpeed);
  UI.primaryControllerUI.addData(PUNCHER_MODE_TEXT, "Puncher ", puncherModeText);

  //Disabled Screen
  UI.primaryControllerUI.addData(DISABLED_AUTO_SCREEN, "Battery: ", batteryLevel);
  UI.primaryControllerUI.addData(AUTO_MODE_LABEL, "Selected Auto:");
  UI.primaryControllerUI.addData(AUTO_MODE_TEXT, "", selectedAutoName);

  //Calibrating Inertial Screen
  UI.primaryControllerUI.addData(INERTIAL_CALIBRATE_SCREEN, "Battery: ", batteryLevel);
  UI.primaryControllerUI.addData(INERTIAL_CALIBRATING_TEXT, "Calibrating...");

  //*Secondary Controller 
  UI.secondaryControllerUI.addData(0, "Battery: ", batteryLevel);

  //Start the threads
  UI.startThreads();

  //* Setup for smart drive ==================================================
  driveBase.setDebugState(true);

  // Setup motor settings
  driveBase.leftPortSetup(11, 12, 13);
  driveBase.rightPortSetup(18, 19, 20);
  driveBase.leftReverseSetup(true, true, true);
  driveBase.rightReverseSetup(false, false, false);
  driveBase.geartrainSetup(3.25, 36, 60);
  driveBase.setDriveBaseWidth(11.625);
  
  // Setup inertial sensor settings
  driveBase.setupInertialSensor(6);

  // Set default speeds
  driveBase.setDriveSpeed(100);
  driveBase.setTurnSpeed(100);
  driveBase.setArcTurnSpeed(40);

  //Set stopping mode
  driveBase.setStoppingMode(brake);

  // Setup PID
  driveBase.setupDrivePID(0.12, 0.10, 0.05, 20, 2, 100);
  driveBase.setupTurnPID(0.54, 0.2, 0.1, 3, 1, 100);
  driveBase.setupDriftPID(0.15, 0, 0, 1, 0, 0);
  driveBase.setupArcPID(0.1, 5, 0, 10, 2, 200);
  driveBase.setupArcDriftPID(0.2, 0, 0, 1, 0, 0);

  //* Setup for base driver contorl ==========================================
  driveControl.setPrimaryStick(leftStick);
  driveControl.setHandicaps(1, 0.6);  // main drive, turning

  //* Setup controller callbacks =============================================
  primaryController.FRONT_LEFT_WINGS_BUTTON.pressed(toggleFrontLeft);
  primaryController.FRONT_RIGHT_WINGS_BUTTON.pressed(toggleFrontRight);
  primaryController.BACK_LEFT_WINGS_BUTTON.pressed(toggleBackLeft);
  primaryController.BACK_RIGHT_WINGS_BUTTON.pressed(toggleBackRight);
  primaryController.PUNCHER_SPEED_INC.pressed(puncherSpeedIncrement);
  primaryController.PUNCHER_SPEED_DEC.pressed(puncherSpeedDecrement);
  primaryController.PUNCHER_MANUAL_BUTTON.pressed(puncherManualToggle);
  primaryController.PUNCHER_MODE_BUTTON.pressed(puncherModeToggle);

  //*Catapult
  puncherEncoder.resetPosition();

  //*Display calibrating information
  UI.primaryControllerUI.setScreenLine(INERTIAL_CALIBRATE_SCREEN);
  driveBase.calibrateInertial();
  while(driveBase.isInertialCalibrating())
  {
    this_thread::sleep_for(5);
  }
}


/*---------------------------------------------------------------------------------*/
/*                                 Autonomous Task                                 */
/*---------------------------------------------------------------------------------*/
void autonomous(void) {

  //Times how long auto takes
  timer autoTimer;

  switch (UI.autoSelectorUI.getSelectedButton()) {
    case AUTO_SKILLS_1:
      driveBase.setTurnSpeed(80);

      //Turn to proper heading
      driveBase.setDriveHeading(133);
      driveBase.turnFor(24, left);
      driveBase.stopRobot(hold);
      this_thread::sleep_for(500);

      //Launch triballs for 30 seconds
      puncherMotor.spin(fwd, 12, voltageUnits::volt);
      //this_thread::sleep_for(30000);
      this_thread::sleep_for(10000);
      puncherMotor.stop(coast);
      this_thread::sleep_for(100);

      //Reset the heading after launching
      driveBase.calibrateInertial();
      while(driveBase.isInertialCalibrating())
      {
        this_thread::sleep_for(5);
      }
      driveBase.setDriveHeading(109);

      //Spin the intake to prevent triballs from getting stuck
      intakeMotor.spin(reverse, 100, percent);

      //Drive to other side of the field
      driveBase.driveBackward(8);
      driveBase.turnFor(121, right);
      driveBase.arcTurn(34, right, 32);
      driveBase.driveForward(65);

      //Realign with the wall
      driveBase.turnFor(90, right);
      driveBase.spinBase(-20, -20);
      vex::task::sleep(800);

      //Runs the motors until it has runs into the goal and can't move
      while((driveBase.getMotorSpeed(left) < -15) && (driveBase.getMotorSpeed(right) < -15)) {
        vex::task::sleep(5);
      }

      vex::task::sleep(50);
      driveBase.stopRobot();
      driveBase.setDriveHeading(0);
      vex::task::sleep(50);
      driveBase.driveForward(14);
      driveBase.arcTurn(12, right, 90);
      //break;
      
      //First push into goal
      driveBase.driveForward(14);
      driveBase.turnFor(90, left);
      driveBase.driveForward(23);
      driveBase.turnFor(90, left);
      //driveBase.turnToHeading(270);
      setFrontWings(false, true);
      driveBase.spinBase(100, 100);
      vex::task::sleep(800);

      //Runs the motors until it has runs into the goal and can't move
      while((driveBase.getMotorSpeed(left) > 50) && (driveBase.getMotorSpeed(right) > 50)) {
        vex::task::sleep(5);
      }

      vex::task::sleep(200);
      driveBase.stopRobot();
      setFrontWings(false, false);
      driveBase.driveBackward(35);

      //Second push into goal
      driveBase.turnFor(90, right);
      driveBase.driveForward(30);
      driveBase.turnFor(90, left);
      setFrontWings(true, false);
      driveBase.spinBase(100, 100);
      vex::task::sleep(800);

      //Runs the motors until it has runs into the goal and can't move
      while((driveBase.getMotorSpeed(left) > 50) && (driveBase.getMotorSpeed(right) > 50)) {
        vex::task::sleep(5);
      }

      vex::task::sleep(200);
      driveBase.stopRobot();
      setFrontWings(false, false);
      driveBase.driveBackward(35);

      intakeMotor.stop();

      break;

    case AUTO_FOUR_BALL_GOAL_SIDE:
      //Set speeds
      driveBase.setDriveSpeed(100);
      driveBase.setTurnSpeed(95);

      //Drop intake and grab first ball
      puncherMotor.spin(fwd, puncherSpeed, pct);
      //this_thread::sleep_for(800);
      while(CRNT_PUNCHER_ANGL < puncherAngleBlock)
      {
        this_thread::sleep_for(5);
      }
      puncherMotor.stop(hold);
      intakeMotor.spin(fwd, 100, pct);
      vex::task::sleep(500);
      intakeMotor.stop();

      //First drive move before dropping match load ball
      driveBase.driveForward(40);
      driveBase.turnToHeading(63);

      //Drop match load ball
      intakeMotor.spin(reverse, 100, pct);
      vex::task::sleep(450);
      intakeMotor.stop();

      //Aim and grab second ball
      driveBase.turnToHeading(306);
      intakeMotor.spin(fwd, 100, pct);
      driveBase.driveForward(27);

      //Align with goal and ram in first two triballs
      driveBase.turnToHeading(270);
      this_thread::sleep_for(400);
      intakeMotor.stop();

      //Change tuning values to allow the robot to move smoothly
      driveBase.setupDrivePID(0.12, 0.07, 0.05, 10, 2, 100);  // p, i, d, error, error time, timeout
      driveBase.setupTurnPID(0.6, 1, 0.125, 6, 2, 100);  // p, i, d, error, error time, timeout

      intakeMotor.spin(fwd, 20, pct);
      driveBase.driveBackward(12);
      driveBase.driveForward(8);
      driveBase.turnToHeading(90);
      setFrontWings(false, true);
      intakeMotor.spin(reverse, 100, percent);
      vex::task::sleep(400);

      //Push triballs into goal
      driveBase.spinBase(100, 100);
      vex::task::sleep(800);

      //Runs the motors until it has runs into the goal and can't move
      while((driveBase.getMotorSpeed(left) > 80) && (driveBase.getMotorSpeed(right) > 80)) {
        vex::task::sleep(5);
      }

      intakeMotor.stop();
      vex::task::sleep(200);
      driveBase.stopRobot();
      driveBase.driveBackward(12);

      //grab ball 4
      setFrontWings(false, false);
      driveBase.turnToHeading(180);
      driveBase.driveForward(20);
      driveBase.turnToHeading(270);
      intakeMotor.spin(fwd, 100, pct);
      driveBase.driveForward(22);

      //score ball 4
      driveBase.driveBackward(12);
      driveBase.turnToHeading(60);
      intakeMotor.spin(reverse, 100, pct);
      puncherMotor.spin(fwd, 20, pct);

      driveBase.spinBase(100, 100);
      vex::task::sleep(600);
      //Runs the motors until it has runs into the goal and can't move
      while((driveBase.getMotorSpeed(left) > 80) && (driveBase.getMotorSpeed(right) > 80)) {
        vex::task::sleep(5);
      }
      intakeMotor.stop(coast);
      driveBase.stopRobot();
      puncherMotor.stop(hold);

      //leave the goal
      driveBase.driveBackward(24);

      break;

    case AUTO_GOAL_SIDE:
      //Set speeds
      driveBase.setDriveSpeed(100);
      driveBase.setTurnSpeed(95);

      //Drop intake and grab first ball
      puncherMotor.spin(fwd, puncherSpeed, pct);
      //this_thread::sleep_for(800);

      thread ([]() {
        while(CRNT_PUNCHER_ANGL < puncherAngleBlock)
        {
          this_thread::sleep_for(5);
        }
        puncherMotor.stop(hold);
        intakeMotor.spin(fwd, 100, pct);
        vex::task::sleep(500);
        intakeMotor.stop();
      }).detach();

      //First drive move before dropping match load ball
      driveBase.driveForward(40);
      driveBase.turnToHeading(60);

      //Drop match load ball
      intakeMotor.spin(reverse, 100, pct);
      vex::task::sleep(450);
      intakeMotor.stop();

      //Aim and grab second ball
      driveBase.turnToHeading(302);
      intakeMotor.spin(fwd, 100, pct);
      driveBase.driveForward(27);

      //Align with goal and ram in first two triballs
      driveBase.turnToHeading(93);
      this_thread::sleep_for(400);
      intakeMotor.stop();

      //Change tuning values to allow the robot to move smoothly
      /* driveBase.setupDrivePID(0.12, 0.07, 0.05, 10, 2, 100);  // p, i, d, error, error time, timeout
      driveBase.setupTurnPID(0.6, 1, 0.125, 6, 2, 100);  // p, i, d, error, error time, timeout */

      intakeMotor.spin(fwd, 20, pct);
      driveBase.turnToHeading(90);
      setFrontWings(true, true);
      intakeMotor.spin(reverse, 100, percent);
      vex::task::sleep(400);

      //Push triballs into goal
      driveBase.spinBase(100, 100);
      vex::task::sleep(800);

      //Runs the motors until it has runs into the goal and can't move
      while((driveBase.getMotorSpeed(left) > 90) && (driveBase.getMotorSpeed(right) > 90)) {
        vex::task::sleep(5);
      }

      intakeMotor.stop();
      vex::task::sleep(200);
      driveBase.stopRobot();
      setFrontWings(false, false);
      driveBase.driveBackward(15);

      //Go touch the bar
      driveBase.turnToHeading(25);
      driveBase.driveBackward(36);
      //driveBase.setTurnSpeed(20);
      driveBase.turnToHeading(95);
      driveBase.spinBase(-50, -50);
      vex::task::sleep(100);
      while((driveBase.getMotorSpeed(left) < -10) && (driveBase.getMotorSpeed(right) < -10)) {
      vex::task::sleep(10);
      }
      setBackWings(false, true);
      driveBase.turnToHeading(105);
      break;

    case AUTO_LOAD_SIDE:
      //Set drive base parameters
      driveBase.setDriveSpeed(100);
      driveBase.setTurnSpeed(100);

      driveBase.setDriveHeading(300);

      //Push triball in
      driveBase.spinBase(-100, -100);
      this_thread::sleep_for(1200);
      driveBase.stopRobot(brake);

      //Go remove other triball
      driveBase.arcTurn(20, left, 40);
      driveBase.driveForward(8);
      setBackWings(false, true);
      driveBase.arcTurn(22, left, 50);
      setBackWings(false, false);

      //Lower intake
      //Drop intake and grab first ball
      puncherMotor.spin(fwd, puncherSpeed, pct);
      this_thread::sleep_for(900);
      puncherMotor.stop(coast);
      vex::task::sleep(500);
      intakeMotor.stop();

      //Push triballs over
      intakeMotor.spin(reverse, 100, percent);
      driveBase.driveForward(27);



      /* //Drop intake and grab first ball
      puncherMotor.spin(fwd, puncherSpeed, pct);
      this_thread::sleep_for(770);
      intakeMotor.spin(fwd, 100, pct);
      puncherMotor.stop(hold);
      vex::task::sleep(200);
      intakeMotor.stop();

      //Put the match load triball in front of the goal
      driveBase.driveForward(49);
      driveBase.turnToHeading(270);
      intakeMotor.spin(reverse, 100, pct);
      this_thread::sleep_for(200);
      intakeMotor.stop();

      //Push triballs into goal
      driveBase.spinBase(100, 100);
      vex::task::sleep(100);

      //Runs the motors until it has runs into the goal and can't move
      while((driveBase.getMotorSpeed(left) > 20) && (driveBase.getMotorSpeed(right) > 20)) {
        vex::task::sleep(5);
      }

      vex::task::sleep(200);
      driveBase.stopRobot();
      driveBase.driveBackward(20);

      //Change tuning values to allow the robot to move smoothly

      //Drive to match load triball
      driveBase.turnToHeading(185);
      driveBase.driveForward(28);
      driveBase.turnToHeading(90);
      driveBase.driveBackward(23);
      driveBase.turnToHeading(143);

      //Puh the triball out
      //wingPistons->set(true);
      driveBase.driveForward(15);
      driveBase.turnToHeading(70);
      //wingPistons->set(false);

      //Push triballs to other side
      driveBase.turnToHeading(125);
      intakeMotor.spin(reverse, 100, percent);
      driveBase.driveForward(20);
      driveBase.turnToHeading(85);
      driveBase.driveForward(21);
      driveBase.driveBackward(3);
      driveBase.turnToHeading(120);
      //wingPistons->set(true);
      intakeMotor.stop(); */

      break;

    //*Basic skills auto the spins the catapult
    case AUTO_BASIC_SKILLS:
      puncherMotor.spin(fwd, 80, percent);
      break;

    //*Scores the prelaod triball in the goal

    //*Descores the triball in the match load zone 
    case AUTO_BASIC_LOAD_SIDE:
      //!UNTESTED
      //Set speeds
      driveBase.setDriveSpeed(100);
      driveBase.setTurnSpeed(75);

      //Descore the triball
      driveBase.driveForward(14);
      //wingPistons->set(true);
      driveBase.driveForward(20);
      driveBase.turnToHeading(40);
      this_thread::sleep_for(500);
      driveBase.turnToHeading(115);
      //wingPistons->set(false);
      driveBase.turnToHeading(325); //!VALUE NEEDS TO BE CONFIRMED
      break;

    //*TEST AUTOS
    case AUTO_TEST_PID:
      /* driveBase.driveForward(39.5);
      this_thread::sleep_for(3000);
      driveBase.driveBackward(39.5); */

      driveBase.setupTurnPID(0.54, 0.2, 0.1, 3, 1, 100);
      driveBase.turnToHeading(90);
      this_thread::sleep_for(500);
      driveBase.turnToHeading(0);

      /* driveBase.arcTurn(-12, right, -45, 40);
      this_thread::sleep_for(1500);
      driveBase.arcTurn(12, left, 90, 100); */

      break;

    //*Do nothing auto
    case AUTO_DO_NOTHING:
    //!DO NOTHING HERE

    //!UNTESTED

    puncherMotor.spin(fwd, puncherSpeed, pct);
    thread ([]() {
      while(CRNT_PUNCHER_ANGL < puncherAngleBlock)
      {
        this_thread::sleep_for(5);
      }
      puncherMotor.stop(hold);
    }).detach();

    thread ([]() {
      frontLeftWing->set(true);
      this_thread::sleep_for(400);
      frontLeftWing->set(false);
    }).detach();

    driveBase.setDriveSpeed(100);
    intakeMotor.spin(fwd, 100, pct);
    driveBase.driveForward(50);

    driveBase.driveBackward(5);
    driveBase.turnFor(70, right);
    frontLeftWing->set(true);

    driveBase.spinBase(50, 50);
    intakeMotor.spin(reverse, 100, pct);
    this_thread::sleep_for(1000);
    driveBase.stopRobot();
    frontLeftWing->set(false);

 
    driveBase.driveBackward(18);
    driveBase.turnFor(60, left);
    driveBase.driveBackward(48);

    // add back in once turn to heading is implemented
    // driveBase.turnFor(105, right);

    // driveBase.spinBase(-100, -100);
    // this_thread::sleep_for(2000);
    // driveBase.stopRobot();

    // driveBase.driveForward(6);

    // driveBase.spinBase(-100, -100);
    // this_thread::sleep_for(1000);
    // driveBase.stopRobot();

    // driveBase.driveForward(3);

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
  double puncherAngle;
  int puncherSpeedOld = -5;

  UI.primaryControllerUI.setScreenLine(MATCH_SCREEN);

  //Make sure the stopping mode for the base is correct
  driveBase.setStoppingMode(brake);

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
    if(puncherSpeed != puncherSpeedOld)
    {
      printf("Speed: %i\n", puncherSpeed);
      puncherSpeedOld = puncherSpeed;
    }

    //Motor control from either the user or robot
    if(primaryController.PUNCHER_STOP_BUTTON.pressing())
    {
      puncherMotor.stop(coast);
    }

    else if(primaryController.PUNCHER_FIRE_BUTTON.pressing() 
            || (puncherAutoPrimeEnabled && (CRNT_PUNCHER_ANGL < puncherAngle))
    )
    {
      puncherMotor.spin(fwd, puncherSpeed, pct);
    }

    else
    {
      puncherMotor.stop(hold);
    }

    //Control the target angle
    if(puncherLaunchMode == PUNCHER_LAUNCH)
    {
      puncherAngle = puncherAngleLaunch;
    }
    
    else
    {
      puncherAngle = puncherAngleBlock;
    }

    //Print out the angle of the catapult
    //printf("\n%f\n\n", CRNT_PUNCHER_ANGL);

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

  UI.primaryControllerUI.setScreenLine(DISABLED_AUTO_SCREEN);

  // Prevent main from exiting with an infinite loop.
  while (true) {
    //*Update controller UI data
    batteryLevel = Brain.Battery.capacity();

    //Update catapult mode text
    if(puncherAutoPrimeEnabled)
    {
      if(puncherLaunchMode == PUNCHER_LAUNCH)
      {
        puncherModeText = "Launch";
      }

      else
      {
        puncherModeText = "Block";
      }
    }

    else
    {
      puncherModeText = "Manual";
    }

    //Update auto name
    selectedAutoName = UI.autoSelectorUI.getSelectedButtonTitle();

    vex::task::sleep(20);
  }
}

//*Controller callback definitions
void setFrontWings(bool left, bool right)
{
  frontLeftWing->set(left);
  frontRightWing->set(right);
}

void setBackWings(bool left, bool right)
{
  backLeftWing->set(left);
  backRightWing->set(right);
}

void toggleFrontWings()
{
  bool newWingStatus = !frontLeftWing->value();
  frontLeftWing->set(newWingStatus);
  frontRightWing->set(newWingStatus);
}

void toggleBackWings()
{
  bool newWingStatus = !backLeftWing->value();
  backLeftWing->set(newWingStatus);
  backRightWing->set(newWingStatus);
}

void toggleFrontLeft()
{
  frontLeftWing->set(!frontLeftWing->value());
}

void toggleFrontRight()
{
  frontRightWing->set(!frontRightWing->value());
}

void toggleBackLeft()
{
  backLeftWing->set(!backLeftWing->value());
}

void toggleBackRight()
{
  backRightWing->set(!backRightWing->value());
}

void puncherSpeedIncrement(void)
{
  if(puncherSpeed < 100)
  {
    puncherSpeed += 5;
  }

  else
  {
    puncherSpeed = 100;
  }
}

void puncherSpeedDecrement(void)
{
  if(puncherSpeed > 0)
  {
    puncherSpeed -= 5;
  }

  else
  {
    puncherSpeed = 0;
  }
}

void puncherManualToggle(void)
{
  puncherAutoPrimeEnabled = !puncherAutoPrimeEnabled;
}

void puncherModeToggle(void)
{
  if(puncherLaunchMode == PUNCHER_BLOCK)
  {
    puncherLaunchMode = PUNCHER_LAUNCH;
  }

  else
  {
    puncherLaunchMode = PUNCHER_BLOCK;
  }
}