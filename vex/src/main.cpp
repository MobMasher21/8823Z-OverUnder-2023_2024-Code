// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// triballSensor        distance      8               
// ArmDown              digital_out   G               
// ArmUp                digital_out   H               
// Inertial             inertial      17              
// ---- END VEXCODE CONFIGURED DEVICES ----

/** code ideas
* write automatic controller debouncing code as a class
*/

#include "vex.h"
#include "evAPI.h"

using namespace evAPI;

intake Intake; //Setup code objects
flywheel Flywheel;
drive driveBase;
competition Competition;

//Custom type to store the mode of the flywheel.
enum class flywheelMode 
{
  flywheelDisabled,
  flywheelShooting,
  flywheelIntaking
};
flywheelMode flywheelShootingMode = flywheelMode::flywheelShooting;

bool hasTriball = false;

int batteryCapacity = 0; //Variables that store info about the battery
double batteryVolt = 0;
double batteryCurrent = 0;
double batteryTemp = 0;

int UIIndex = UI.getProgNumber() + 1;

//Controls for the robot arm.
void TriballArmDown()
{
  ArmUp.set(false);
  ArmDown.set(true);
}

void TriballArmUp()
{
  ArmUp.set(true);
  ArmDown.set(false);
}

/* int leftSpeed;
int rightSpeed; */

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
  //Setup Base
  driveBase.setGearbox(blueGearBox);
  driveBase.leftPortSetup(19, 10);
  driveBase.rightPortSetup(9, 20);
  driveBase.leftReverseSetup(true, true);
  driveBase.rightReverseSetup(false, false);
  driveBase.setBaseType(HDriveStandard);
  driveBase.setControlType(RCControl, leftStick);
  driveBase.setGeneralHandicap(0.9);
  driveBase.setTurningHandicap(0.65);

  /* driveBase.leftEncoderSetup(1, 2.75, false);
  driveBase.rightEncoderSetup(2, 2.75, false);
  driveBase.backEncoderSetup(6, 2.75, false); */

  //Setup Flywheel
  Flywheel.flywheelSetup(2, 3, false, true);
  Flywheel.setMaxTorque(100, percent);
  Flywheel.setVelocity(100, percent);

  //Setup Intake
  Intake.intakeSetup(6, 7, false, true);
  Intake.setMaxTorque(100, percent);
  Intake.setVelocity(45, percent);

  //Setup Preauto UI
  UI.setDebugMode(false);

  UI.addButton(blue, "Scoring", "A auto for the scoring side.", UI.Icons.number1);
  UI.addButton(blue, "Load", "A auto for the scoring side.", UI.Icons.number2);
  UI.addBlank();
  UI.addButton(vexClrSnow, "Snow!", "A nice icon of snow.\nThis serves no other purpose.", UI.Icons.snow);
  
  UI.addBlank();
  UI.addBlank();
  UI.addBlank();
  UI.addButton(0xff, 0x10, 0xa0, "Skills 1", "Shoots all match loads into the field.", UI.Icons.skills);
  UI.setDisplayTime(2000);

  //Setup Match UI
  UI.setDefaultReadOutColor(blue);
  UI.createBrainReadOut("Battery: ", batteryCapacity);
  UI.createBrainReadOut("Battery Volt: ", batteryVolt);
  UI.createBrainReadOut("Battery Amps: ", batteryCurrent);
  UI.createBrainReadOut("Bat Degrees F: ", batteryTemp, red);

  //Setup Controller UI
  UI.createControllerReadOut("Battery: ", batteryCapacity);
  UI.createControllerReadOut("Auto: ", UIIndex);
  UI.createControllerReadOut("MOA Comp");

  /* UI.createFieldDisplay(left);
  UI.setTileColor(0, red);
  UI.setTileColor(30, red);
  UI.setTileColor(17, red);
  UI.setTileColor(23, red);
  UI.setTileColor(5, blue);
  UI.setTileColor(35, blue);
  UI.setTileColor(12, blue);
  UI.setTileColor(18, blue); */

  //Start UI
  Inertial.calibrate();

  Inertial.setRotation(5, degrees);

  while(Inertial.isCalibrating())
  { this_thread::sleep_for(10); }

  UI.selectButton(0, true);
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
  switch(UI.getProgNumber())
  {
    case 0: //Blue Scoring
      Inertial.setRotation(5, degrees);
      driveBase.spinBase(-100, -100);
      this_thread::sleep_for(1000);
      driveBase.stopRobot(brake);

      driveBase.spinBase(20, 20);
      this_thread::sleep_for(400);
      driveBase.stopRobot(brake);

      driveBase.spinBase(5, -5);
      while(Inertial.rotation(degrees) <= 10)
      { this_thread::sleep_for(10); }
      driveBase.stopRobot(brake);

      driveBase.spinBase(20, 20);
      this_thread::sleep_for(1850);
      driveBase.stopRobot(brake);

      driveBase.spinBase(5, -5);
      while(Inertial.rotation(degrees) <= 65)
      { this_thread::sleep_for(10); }
      driveBase.stopRobot(brake);

      driveBase.spinBase(20, 20);
      this_thread::sleep_for(1750);
      driveBase.stopRobot(brake);

      Flywheel.spin(fwd, 100, percent);
      TriballArmDown();

      this_thread::sleep_for(500);
      Flywheel.stop();
      break;

    case 1: //Blue Away
      Inertial.setRotation(5, degrees);
      TriballArmDown();
      Flywheel.spin(fwd, 100, percent);
      this_thread::sleep_for(100);
      driveBase.spinBase(20, -20);

      while(Inertial.rotation(degrees) <= 210)
      { this_thread::sleep_for(10); }

      driveBase.stopRobot(brake);
      TriballArmUp();

      driveBase.spinBase(20, 20);
      this_thread::sleep_for(2200);
      driveBase.stopRobot(brake);

      /* driveBase.spinBase(-2, 2);

      while(Inertial.rotation(degrees) >= 200)
      { this_thread::sleep_for(10); }

      driveBase.stopRobot(brake); */

      /* driveBase.spinBase(20, 20);
      this_thread::sleep_for(300);
      driveBase.stopRobot(brake); */

      TriballArmDown();
      break;

    /* case 4: //Red Scoring
      
      break;
    
    case 5: //Red Away

      break; */

    case 7: //Skills 1
    
      //Put the arm down to make contact with the match load zone
      TriballArmDown();
      
      //Activate flywheel and intake for shooting.
      Flywheel.spin(fwd, 90, percent);
      Intake.spin(fwd, 100, percent);

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
  bool intakeOverride = false;
  TriballArmUp();

  while(1) {
    if(!primaryController.ButtonA.pressing()) //Base controls
    { driveBase.controllerDrive(); }

    else
    { driveBase.stopRobot(hold); }

    if(triballSensor.objectDistance(mm) <= 140) //Detects if the robot has a triball in the intake.
    { hasTriball = true; }

    else
    { hasTriball = false; }

    if(primaryController.ButtonR1.pressing() || primaryController.ButtonR2.pressing())
    { intakeOverride = true; }

    else
    { intakeOverride = false; }

    if(primaryController.ButtonL1.pressing()) //Controls the flywheel mode
    { flywheelShootingMode = flywheelMode::flywheelShooting; }

    else if(primaryController.ButtonL2.pressing())
    { flywheelShootingMode = flywheelMode::flywheelIntaking; }

    //If the flywheel is configured to shoot triballs.
    if(flywheelShootingMode == flywheelMode::flywheelShooting) 
    {
      if(!intakeOverride) //Standard operation with no user input
      {
        if(!hasTriball)
        { Intake.spin(fwd, 45, percent); }

        else
        { Intake.stop(); }
      }

      else //Controls over override
      {
        if(primaryController.ButtonR1.pressing())
        { Intake.spin(fwd, 100, percent); }

        else if(primaryController.ButtonR2.pressing())
        { Intake.spin(reverse, 100, percent); }
      }

      Flywheel.spin(fwd, 100, percent);
    }

    else //If the flywheel is configured to intake triballs.
    {
      if(!intakeOverride) //Standard operation with no user input
      {
        if(!hasTriball)
        { Intake.spin(reverse, 75, percent); }

        else
        { Intake.stop(); }
      }

      else //Controls over override
      {
        if(primaryController.ButtonR1.pressing())
        { Intake.spin(fwd, 80, percent); }

        else if(primaryController.ButtonR2.pressing())
        { Intake.spin(reverse, 100, percent); }
      }

      Flywheel.spin(reverse, 45, percent);
    }

    if(primaryController.ButtonUp.pressing())
    { TriballArmUp(); }

    else if(primaryController.ButtonDown.pressing())
    { TriballArmDown(); }

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
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  TriballArmUp();

  // Run the pre-autonomous function.
  pre_auton();

  while (true) {
    batteryCapacity = Brain.Battery.capacity();
    batteryVolt = Brain.Battery.voltage(volt);
    batteryCurrent = Brain.Battery.current(amp);
    batteryTemp = Brain.Battery.temperature(temperatureUnits::fahrenheit);
    UIIndex = UI.getProgNumber() + 1;

    this_thread::sleep_for(10);
  }
}