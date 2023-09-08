/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Jayden Liffick                                            */
/*    Created:      Mon Mar 06 2023                                           */
/*    Description:  8823Z Competition Code                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

// --- Start EVAPI CONFIGURED DEVICES -------
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// primaryController    Controller
// secondaryController  Controller             
// ---- END EVAPI CONFIGURED DEVICES ------

#include "vex.h"
#include "evAPI.h"

using namespace evAPI;

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

void preAuto()
{
  //Drivetrain Setup
  Drivetrain.setDebugState(false);
  Drivetrain.setGearbox(blueCartridge);
  Drivetrain.setBaseType(HDriveStandard);
  Drivetrain.setControlType(RCControl, leftStick);

  Drivetrain.leftPortSetup(7, 8);
  Drivetrain.rightPortSetup(9, 10);
  Drivetrain.leftReverseSetup(true, true);
  Drivetrain.rightReverseSetup(false, false);
  Drivetrain.geartrainSetup(4, 48, 72);

  Drivetrain.setGeneralHandicap(1);
  Drivetrain.setTurningHandicap(.75);

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

void autonomous()
{
  switch(UI.getProgNumber())
  {
    case 0:

      break;

    case 1:

      break;
  }
}

void driver()
{

}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  preAuto();

  robotInfo.Competition.autonomous(autonomous);
  robotInfo.Competition.drivercontrol(driver);

  while(true)
  {
    Drivetrain.controllerDrive(); //Operates the base wheels

    batteryCapacity = Brain.Battery.capacity();
    batteryVolt = Brain.Battery.voltage(volt);
    batteryCurrent = Brain.Battery.current(amp);
    batteryTemp = Brain.Battery.temperature(temperatureUnits::fahrenheit);

    axis1 = primaryController.Axis1.position(pct);
    axis2 = primaryController.Axis2.position(pct);
    axis3 = primaryController.Axis3.position(pct);
    axis4 = primaryController.Axis4.position(pct);

    countUp();

    brainTimer = Brain.timer(seconds);

    this_thread::sleep_for(10);
  }
}
