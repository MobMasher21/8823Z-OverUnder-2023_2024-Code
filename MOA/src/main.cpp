// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          Controller    
// ---- END VEXCODE CONFIGURED DEVICES ----

/** code ideas
* write automatic controller debouncing code as a class
*/

#include "vex.h"
#include "../include/evAPI.h"

using namespace evAPI;

Drive driveBase;
competition Competition;

int leftSpeed;
int rightSpeed;

//Temp UI Testing

int batteryCapacity = 0;
double batteryVolt = 0;
double batteryCurrent = 0;
double batteryTemp = 0;

int axis1 = 0;
int axis2 = 0;
int axis3 = 0;
int axis4 = 0;

int counter = 0;
double brainTimer = 0;

void countUp()
{ 
  if(counter == 256)
  { counter = 0; }

  else
  { counter++; }
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
  driveBase.leftPortSetup(7, 8);
  driveBase.rightPortSetup(9, 10);
  driveBase.leftReverseSetup(true, true);
  driveBase.rightReverseSetup(false, false);
  driveBase.leftEncoderSetup(1, 2.75, false);
  driveBase.rightEncoderSetup(2, 2.75, false);
  driveBase.backEncoderSetup(6, 2.75, false);

  //Setup Preauto UI
  UI.setDebugMode(false);
  UI.addButton(blue, "Blue Button", "A blue button that does absolutely nothing because this program is for testing and not driving an actual robot around on a field. I'm not really sure what I am doing at this point, but I guess this helps with testing my line breaking code.", UI.Icons.leftArrow);
  UI.addButton(red, "Red Button", "A red button.\n\nNot much else.\n\nStop reading.", UI.Icons.rightArrow);
  UI.addButton(green, "ToManyCharacters", "HiThisIsTestingWhatGoesDownIfThereAreTooManyCharactersWithoutAnySpacesOrPunctuationMarks!", UI.Icons.exclamationMark);
  UI.addButton(vexClrDarkTurquoise);
  UI.addButton(cyan, "Program 0", UI.Icons.number0);
  UI.addButton(vexClrForestGreen,"Program 1", UI.Icons.number1);
  UI.addButton(yellow,"Program 2", UI.Icons.number2);
  UI.addButton(vexClrSnow, "Snow!", "A nice icon of snow.\nThis serves no other purpose.", UI.Icons.snow);
  UI.addButton(orange);
  UI.addBlank();
  UI.addBlank();
  UI.addButton(purple);
  UI.setDisplayTime(2000);

  //Setup Match UI
  UI.createFieldDisplay(left);
  UI.setTileColor(0, red);
  UI.setTileColor(30, red);
  UI.setTileColor(17, red);
  UI.setTileColor(23, red);
  UI.setTileColor(5, blue);
  UI.setTileColor(35, blue);
  UI.setTileColor(12, blue);
  UI.setTileColor(18, blue);

  UI.setDefaultReadOutColor(blue);

  UI.createBrainReadOut("Battery: ", batteryCapacity);
  UI.createBrainReadOut("Battery Volt: ", batteryVolt);
  UI.createBrainReadOut("Battery Amps: ", batteryCurrent);
  UI.createBrainReadOut("Bat Degrees F: ", batteryTemp, red);

  UI.createBrainReadOut("Primary Axis 1: ", axis1, vexClrDarkCyan);
  UI.createBrainReadOut("Primary Axis 2: ", axis2, vexClrDarkCyan);
  UI.createBrainReadOut("Primary Axis 3: ", axis3, vexClrDarkCyan);
  UI.createBrainReadOut("Primary Axis 4: ", axis4, vexClrDarkCyan);

  UI.createBrainReadOut("Counter: ", counter, vexClrBlueViolet);
  UI.createBrainReadOut("Timer: ", brainTimer, vexClrSeaGreen);
  UI.createBlankBrainReadOut();
  UI.createBrainReadOut("THIS IS TESTING TEXT.", vexClrBlueViolet);

  //Setup Controller UI
  UI.createControllerReadOut("Battery: ", batteryCapacity);
  UI.createBlankControllerReadOut();
  UI.createControllerReadOut("Just some text.");

  //Start UI
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
    case 0:

      break;

    case 1:

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
  while(1) {
    //=================================================================================

    leftSpeed = (Controller1.Axis3.position(pct) + Controller1.Axis1.position(pct));
    rightSpeed = (Controller1.Axis3.position(pct) - Controller1.Axis1.position(pct));
    driveBase.spinBase(leftSpeed, rightSpeed);

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

  // Run the pre-autonomous function.
  pre_auton();

  while (true) {
    batteryCapacity = Brain.Battery.capacity();
    batteryVolt = Brain.Battery.voltage(volt);
    batteryCurrent = Brain.Battery.current(amp);
    batteryTemp = Brain.Battery.temperature(temperatureUnits::fahrenheit);

    axis1 = Controller1.Axis1.position(pct);
    axis2 = Controller1.Axis2.position(pct);
    axis3 = Controller1.Axis3.position(pct);
    axis4 = Controller1.Axis4.position(pct);

    countUp();

    brainTimer = Brain.timer(seconds);

    this_thread::sleep_for(10);
  }
}