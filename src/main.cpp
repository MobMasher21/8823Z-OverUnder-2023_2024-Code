/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Authors:      Cameron Barclay, Jayden Liffick, Teo Carrion              */
/*    Created:      12/6/2023, 10:45:31 PM                                    */
/*    Description:  Main code for team 8823Z robot.                           */
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
motor puncherMotor = motor(PORT12, redGearBox, true);
motor intakeMotor = motor(PORT11, blueGearBox, false);
rotation puncherEncoder = rotation(PORT13, false);
digital_out *leftWing;
digital_out *rightWing;
digital_out *PTOPistons;

// Controller callback function declarations ------------------------------
void setWings(bool left, bool right); //Control the front wings
void toggleWings(); //Toggle the status of the front wings
void toggleLeftWing();
void toggleRightWing();
void enablePTO();
void puncherSpeedIncrement(void); //Increments the speed of the puncher by 5
void puncherSpeedDecrement(void); //Decrements the speed of the puncher by 5
void puncherManualToggle(void);   //Enables manual control of the puncher

// Setup controller button names ------------------------------------------
#define PUNCHER_FIRE_BUTTON ButtonL1
#define PUNCHER_STOP_BUTTON ButtonL2
#define PUNCHER_MODE_BUTTON ButtonA
#define PUNCHER_MANUAL_BUTTON ButtonX
#define PUNCHER_SPEED_INC ButtonUp
#define PUNCHER_SPEED_DEC ButtonLeft

#define INTAKE_IN_BUTTON ButtonR1
#define INTAKE_OUT_BUTTON ButtonR2
#define LEFT_WINGS_BUTTON ButtonRight
#define RIGHT_WINGS_BUTTON ButtonY
#define PTO_TRIGGER_BUTTON ButtonA

// Speed and handicap variables -------------------------------------------
int intakeSpeed = 100;

//Setup Auto Button UI IDs
enum autoOptions {
  //*General
  //Page 1
  AUTO_SKILLS_1 = 0,
  AUTO_FOUR_BALL_GOAL_SIDE = 1,
  AUTO_GOAL_SIDE = 3,
  AUTO_DO_NOTHING = 4,
  AUTO_ELIMINATION_LOAD_SIDE = 5,
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
std::string PTOModeText = "Disabled";
std::string selectedAutoName = "";

//Setup controller UI IDs
enum controllerOptions
{
  //Match Screen
  MATCH_SCREEN = 0,
  PUNCHER_SPEED_DISPLAY,
  PTO_STATUS,

  //Disabled / Auto Screen
  DISABLED_AUTO_SCREEN = 3,
  AUTO_MODE_LABEL,
  AUTO_MODE_TEXT,

  //Inertial Calibration Screen
  INERTIAL_CALIBRATE_SCREEN = 6,
  INERTIAL_CALIBRATING_TEXT
};

//Puncher control
const double puncherAngleLaunch = 315;
double puncherStartAngle = puncherEncoder.angle(deg);
#define CURRENT_PUNCHER_ANGLE (puncherEncoder.angle(deg) - puncherStartAngle)
int puncherSpeed = 53;
bool puncherAutoPrimeEnabled = true;

/*---------------------------------------------------------------------------------*/
/*                             Pre-Autonomous Functions                            */
/*---------------------------------------------------------------------------------*/
void pre_auton(void) {
  //* Set object pointers ====================================================
  rightWing  = new digital_out(Brain.ThreeWirePort.A);
  leftWing   = new digital_out(Brain.ThreeWirePort.B);
  PTOPistons = new digital_out(Brain.ThreeWirePort.D);

  //* Setup for auto selection UI ============================================
  // Add all the buttons
  UI.autoSelectorUI.addButton(AUTO_SKILLS_1, 0xff10a0);
  UI.autoSelectorUI.addButton(AUTO_FOUR_BALL_GOAL_SIDE, cyan);
  UI.autoSelectorUI.addButton(AUTO_ELIMINATION_LOAD_SIDE, DodgerBlue);
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
  UI.autoSelectorUI.setButtonTitle(AUTO_ELIMINATION_LOAD_SIDE, "Bracket Load");
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
  UI.autoSelectorUI.setButtonDescription(AUTO_ELIMINATION_LOAD_SIDE, "Runs on load side. Pushes the colored triball out and 2 triballs to the other side.");
  UI.autoSelectorUI.setButtonDescription(AUTO_GOAL_SIDE, "Scores three triballs, including the match load, and touches the bar.");
  UI.autoSelectorUI.setButtonDescription(AUTO_LOAD_SIDE, "Scores the match load, pushes two triballs to the other side, and touches the bar.");
  UI.autoSelectorUI.setButtonDescription(AUTO_DO_NOTHING, "The robot will do nothing.");
  UI.autoSelectorUI.setButtonDescription(AUTO_BASIC_SKILLS, "Launches all the match loads into the field.");;
  UI.autoSelectorUI.setButtonDescription(AUTO_BASIC_GOAL_SIDE, "Ram backward, then go forward.");
  UI.autoSelectorUI.setButtonDescription(AUTO_BASIC_LOAD_SIDE, "Descore the triball from the match load zone.");

  // Select all the icons
  UI.autoSelectorUI.setButtonIcon(AUTO_SKILLS_1, UI.autoSelectorUI.icons.skills);
  UI.autoSelectorUI.setButtonIcon(AUTO_FOUR_BALL_GOAL_SIDE, UI.autoSelectorUI.icons.number4);
  UI.autoSelectorUI.setButtonIcon(AUTO_ELIMINATION_LOAD_SIDE, UI.autoSelectorUI.icons.number2);
  UI.autoSelectorUI.setButtonIcon(AUTO_GOAL_SIDE, UI.autoSelectorUI.icons.leftArrow);
  UI.autoSelectorUI.setButtonIcon(AUTO_LOAD_SIDE, UI.autoSelectorUI.icons.rightArrow);
  UI.autoSelectorUI.setButtonIcon(AUTO_DO_NOTHING, UI.autoSelectorUI.icons.exclamationMark);
  UI.autoSelectorUI.setButtonIcon(AUTO_BASIC_SKILLS, UI.autoSelectorUI.icons.skills);
  UI.autoSelectorUI.setButtonIcon(AUTO_BASIC_GOAL_SIDE, UI.autoSelectorUI.icons.leftArrow);
  UI.autoSelectorUI.setButtonIcon(AUTO_BASIC_LOAD_SIDE, UI.autoSelectorUI.icons.rightArrow);

  //Setup parameters for auto selector
  UI.autoSelectorUI.setSelectedButton(AUTO_SKILLS_1);
  UI.autoSelectorUI.setSelectedPage(0);
  UI.autoSelectorUI.setDataDisplayTime(1500);

  //*Setup controller UI
  //Driver Control Screen
  UI.primaryControllerUI.addData(MATCH_SCREEN, "Battery: ", batteryLevel);
  UI.primaryControllerUI.addData(PUNCHER_SPEED_DISPLAY, "Puncher Speed: ", puncherSpeed);
  UI.primaryControllerUI.addData(PTO_STATUS, "PTO: ", PTOModeText);

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
  driveBase.leftPortSetup(14, 15, 16);
  driveBase.rightPortSetup(2, 9, 3);
  driveBase.leftReverseSetup(true, true, true);
  driveBase.rightReverseSetup(false, false, false);
  driveBase.geartrainSetup(3.25, 36, 60);
  driveBase.setDriveBaseWidth(12);
  
  // Setup inertial sensor settings
  driveBase.setupInertialSensor(17);

  // Set default speeds
  driveBase.setDriveSpeed(100);
  driveBase.setTurnSpeed(100);
  driveBase.setArcTurnSpeed(40);

  //Set stopping mode
  driveBase.setStoppingMode(brake);

  // Setup PID
  driveBase.setupDrivePID(0.087, 10, 0.005, 16, 2, 125);
  driveBase.setupDriftPID(0.015, 0, 0, 1, 0, 0);
  driveBase.setupTurnPID(0.65, 0, 0.5, 3, 1, 100);
  driveBase.setupArcPID(0.1, 5, 0, 3, 2, 200);
  driveBase.setupArcDriftPID(0.2, 0, 0, 1, 0, 0);

  //* Setup for base driver contorl ==========================================
  driveControl.setPrimaryStick(leftStick);
  driveControl.setHandicaps(1, 0.6);  // main drive, turning

  //* Setup controller callbacks =============================================
  primaryController.LEFT_WINGS_BUTTON.pressed(toggleLeftWing);
  primaryController.RIGHT_WINGS_BUTTON.pressed(toggleRightWing);
  primaryController.PUNCHER_SPEED_INC.pressed(puncherSpeedIncrement);
  primaryController.PUNCHER_SPEED_DEC.pressed(puncherSpeedDecrement);
  primaryController.PUNCHER_MANUAL_BUTTON.pressed(puncherManualToggle);
  primaryController.PTO_TRIGGER_BUTTON.pressed(enablePTO);

  puncherMotor.setBrake(coast);

  //*Puncher
  puncherEncoder.resetPosition();
  puncherStartAngle = puncherEncoder.position(deg);

  //*Display calibrating and autonomous information if connected to a field or comp switch
  if(isConnectToField()) UI.primaryControllerUI.setScreenLine(INERTIAL_CALIBRATE_SCREEN);

  //Calibrate inertial.
  driveBase.calibrateInertial();
  while(driveBase.isInertialCalibrating())
  {
    this_thread::sleep_for(5);
  }

  if(isConnectToField()) UI.primaryControllerUI.setScreenLine(DISABLED_AUTO_SCREEN);
}



/*---------------------------------------------------------------------------------*/
/*                                 Autonomous Task                                 */
/*---------------------------------------------------------------------------------*/
void autonomous(void) {

  //Times how long auto takes
  timer autoTimer;

  switch (UI.autoSelectorUI.getSelectedButton()) {
    case AUTO_SKILLS_1:
      //Hold intake triball
      intakeMotor.spin(fwd, 50, percent);

      //Launch triballs to other side of field
      puncherMotor.spin(forward, puncherSpeed, pct);
      this_thread::sleep_for(27000);
      puncherMotor.stop();

      //Recalibrate inertial
      driveBase.calibrateInertial();
      while (driveBase.isInertialCalibrating()) {
        this_thread::sleep_for(10);
      }
      this_thread::sleep_for(100);

      //Turn to face goal
      driveBase.turnToHeading(90);

      //Shove triballs into goal twice
      driveBase.spinBase(-100, -100);
      this_thread::sleep_for(1000);
      // while (((driveBase.getMotorSpeed(left) < -20) && (driveBase.getMotorSpeed(right) < -20)) ) {
      //   vex::task::sleep(5);
      // }
      this_thread::sleep_for(100);
      driveBase.stopRobot();

      /* driveBase.driveForward(6);

      driveBase.spinBase(-100, -100);
      this_thread::sleep_for(1000);
      // while (((driveBase.getMotorSpeed(left) < -20) && (driveBase.getMotorSpeed(right) < -20)) ) {
      //   vex::task::sleep(5);
      // }
      this_thread::sleep_for(100);
      driveBase.stopRobot(); */

      driveBase.driveForward(8);
      driveBase.turnFor(90, left);
      driveBase.spinBase(-100, -100);
      this_thread::sleep_for(350);
      driveBase.stopRobot();

      this_thread::sleep_for(750);
      //Reset heading
      driveBase.setDriveHeading(90);

      //Drive under bar
      driveBase.driveForward(10);
      driveBase.turnToHeading(135);
      driveBase.driveForward(30);
      driveBase.turnToHeading(90);
      intakeMotor.spin(reverse, 100, percent);
      this_thread::sleep_for(100);
      driveBase.driveForward(65);

      //First push
      driveBase.turnToHeading(225);
      driveBase.spinBase(-100, -100);
      this_thread::sleep_for(1500);
      driveBase.driveForward(10);

      //Go to other triballs
      driveBase.turnToHeading(270);
      driveBase.driveForward(18);
      driveBase.turnToHeading(315);
      driveBase.driveForward(20);
      driveBase.turnToHeading(45);
      
      //Second push
      setWings(true, true);
      driveBase.spinBase(100, 100);
      this_thread::sleep_for(2000);
      setWings(false, false);
      driveBase.driveBackward(20);

      break;

    case AUTO_FOUR_BALL_GOAL_SIDE:
      //Set speeds
      driveBase.setDriveSpeed(100);
      driveBase.setTurnSpeed(95);

      //Drop intake and grab first ball
      puncherMotor.spin(fwd, puncherSpeed, pct);
      //this_thread::sleep_for(800);
      while(CURRENT_PUNCHER_ANGLE < puncherAngleLaunch)
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
      setWings(false, true);
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
      setWings(false, false);
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

    case AUTO_ELIMINATION_LOAD_SIDE:
      thread ([]() {
        // setWings(false, true);
        this_thread::sleep_for(200);
        setWings(false, false);
      }).detach();

      intakeMotor.spin(forward, 100, pct);
      // drive to triball
      driveBase.driveForward(50.5);
      // drive back
      driveBase.driveBackward(32);

      // turn to face wall
      driveBase.turnToHeading(77);
      // 
      driveBase.driveBackward(38);

      driveBase.setDriveHeading(90);


      /*
      driveBase.setDriveSpeed(100);
      intakeMotor.spin(fwd, 100, pct);
      driveBase.driveForward(50);

      driveBase.driveBackward(5);
      driveBase.turnFor(70, right);
      setWings(true, false);

      driveBase.spinBase(50, 50);
      intakeMotor.spin(reverse, 100, pct);
      this_thread::sleep_for(1000);
      driveBase.stopRobot();
      setWings(false, false);

      driveBase.driveBackward(18);
      driveBase.turnFor(60, left);
      driveBase.driveBackward(48);
      */
      //Add back in once turn to heading is implemented
      /* driveBase.turnFor(105, right);

      driveBase.spinBase(-100, -100);
      this_thread::sleep_for(2000);
      driveBase.stopRobot();

      driveBase.driveForward(6);

      driveBase.spinBase(-100, -100);
      this_thread::sleep_for(1000);
      driveBase.stopRobot();

      driveBase.driveForward(3); */

      break;

    case AUTO_GOAL_SIDE:
      //Set speeds
      driveBase.setDriveSpeed(100);
      driveBase.setTurnSpeed(95);

      //Drop intake and grab first ball
      puncherMotor.spin(fwd, puncherSpeed, pct);
      thread ([]() {
        while(CURRENT_PUNCHER_ANGLE < puncherAngleLaunch)
        {
          this_thread::sleep_for(5);
        }
        puncherMotor.stop(hold);
        intakeMotor.spin(fwd, 100, pct);
        vex::task::sleep(500);
        intakeMotor.stop();
        //vex::this_thread::yield();
      }).detach();

      //First drive move before dropping match load ball
      driveBase.driveForward(40);
      driveBase.turnToHeading(60);

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
      intakeMotor.spin(fwd, 20, pct);
      driveBase.driveBackward(12);
      driveBase.driveForward(8);
      driveBase.turnToHeading(90);
      setWings(true, true);
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
      setWings(false, false);
      driveBase.driveBackward(15);

      //Go touch the bar
      driveBase.turnToHeading(25);
      driveBase.driveBackward(35);
      //setBackWings(false, true);
      //driveBase.setTurnSpeed(20);
      driveBase.turnToHeading(100);
      driveBase.driveBackward(10);
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
      //setBackWings(false, true);
      driveBase.arcTurn(21, left, 50);
      //setBackWings(false, false);

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

      break;

    //*Basic skills auto that launches triballs
    case AUTO_BASIC_SKILLS:
      driveBase.setTurnSpeed(80);

      //Turn to proper heading
      driveBase.setDriveHeading(133);
      driveBase.turnFor(24, left);
      driveBase.stopRobot(hold);
      this_thread::sleep_for(500);

      //Launch triballs
      puncherMotor.spin(fwd, puncherSpeed, pct);
      break;

    //*Scores the prelaod triball in the goal
    case AUTO_BASIC_GOAL_SIDE:
      driveBase.setDriveSpeed(100);

      driveBase.spinBase(-100, -100);
      vex::task::sleep(800);

      //Runs the motors until it has runs into the goal and can't move
      while((driveBase.getMotorSpeed(left) < -20) && (driveBase.getMotorSpeed(right) < -20)) {
        vex::task::sleep(5);
      }

      vex::task::sleep(250);
      driveBase.stopRobot();
      driveBase.driveForward(12);
      break;

    //*Descores the triball in the match load zone 
    case AUTO_BASIC_LOAD_SIDE:
      //!UNTESTED
      //Set speeds
      setWings(true, false);
      driveBase.turnFor(200, left);
      setWings(false, false);
      break;

    //*TEST AUTOS
    case AUTO_TEST_PID:
      driveBase.setupDrivePID(0.087, 10, 0.005, 12, 2, 125);
      driveBase.setupDriftPID(0.015, 0, 0, 1, 0, 0);

      driveBase.setupTurnPID(0.65, 0, 0.5, 3, 1, 100);
      
      driveBase.setupArcPID(0.3, 5, 0, 6, 2, 2000);
      driveBase.setupArcDriftPID(0, 0, 0, 1, 0, 0);
      driveBase.setArcTurnSpeed(70);
      driveBase.setDriveBaseWidth(12);

      // driveBase.driveForward(48); 

      // driveBase.turnFor(120, left);
      driveBase.arcTurn(20, right, 50);

      /* this_thread::sleep_for(3000);
      driveBase.driveBackward(48); */

      /* driveBase.turnToHeading(90);
      this_thread::sleep_for(500);
      driveBase.turnToHeading(0); */

      /* driveBase.arcTurn(12, right, 45, 40); */

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
  UI.primaryControllerUI.setScreenLine(MATCH_SCREEN);

  //Make sure the stopping mode for the base is correct
  driveBase.setStoppingMode(brake);

  // User control code here, inside the loop
  while (1) {
    //=========== All drivercontrol code goes between the lines ==============

    //* Control the base code -----------------------------
    driveControl.driverLoop();

    //* Control the intake code ---------------------------
    if(primaryController.INTAKE_IN_BUTTON.pressing()) {
      intakeMotor.spin(fwd, intakeSpeed, pct);
    } else if(primaryController.INTAKE_OUT_BUTTON.pressing()) {
      intakeMotor.spin(reverse, intakeSpeed, pct);
    } else {
      intakeMotor.stop(coast);
    }

    //* Control the puncher code -------------------------
    //Motor control from either the user or robot
    if(primaryController.PUNCHER_STOP_BUTTON.pressing())
    {
      puncherMotor.stop(coast);
    }

    else if(primaryController.PUNCHER_FIRE_BUTTON.pressing())
    {
      puncherMotor.spin(fwd, puncherSpeed, pct);
    }

    else
    {
      puncherMotor.stop(coast);
    }

    //Print out the angle of the puncher
    // printf("\n%f\n\n", CURRENT_PUNCHER_ANGLE);

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
    //*Update controller UI data
    batteryLevel = Brain.Battery.capacity();

    //Update PTO Status
    if(PTOPistons->value())
    {
      PTOModeText = "Enabled";
    }

    else
    {
      PTOModeText = "Disabled";
    }

    //Update auto name
    selectedAutoName = UI.autoSelectorUI.getSelectedButtonTitle();

    vex::task::sleep(20);
  }
}

//*Controller callback definitions
void setWings(bool left, bool right)
{
  leftWing->set(left);
  rightWing->set(right);
}

void toggleWings()
{
  bool newWingStatus = !leftWing->value();
  leftWing->set(newWingStatus);
  rightWing->set(newWingStatus);
}

void toggleLeftWing()
{
  leftWing->set(!leftWing->value());
}

void toggleRightWing()
{
  rightWing->set(!rightWing->value());
}

void enablePTO()
{
  PTOPistons->set(true);
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