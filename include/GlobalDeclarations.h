#ifndef GLOBALDEFINITIONS_H_
#define GLOBALDEFINITIONS_H_

#include "vex.h"
#include "../evAPI/evAPIFiles.h"
#include "RobotConfig.h"

using namespace evAPI;

// Object definitons
controller primaryController = controller(primary);
Drive driveBase = Drive(blueGearBox);
DriverBaseControl driveControl = DriverBaseControl(primaryController, RCControl, driveBase);
AutoSelector UI;
competition Competition;

// Driver control settings and variables =======================================
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
#define DRIVE_HANDICAP 1
float turnHandicap;

#define LOGAN_TURNS 0.75
#define ELI_TURNS 0.5

int leftSpeed;
int rightSpeed;

// Cata stuff -------------------------------------------------
enum cataStates
{
  HIGH_CATA = 0,
  LOW_CATA = 1
};

cataStates cataLaunchMode = HIGH_CATA;
const int16_t highCataAngle = 30;
const int16_t lowCataAngle = 46;
int targetCataAngle;
double cataStartAngle;
double currentCataAngle;
int cataSpeed = 75;

// Intake stuff -----------------------------------------------
int intakeSpeed = 100;

// Information about the robot battery =========================================
int robotBatteryCapacity = (int)Brain.Battery.capacity();
double robotBatteryVolt = Brain.Battery.voltage();
double robotBatteryCurrent = Brain.Battery.current();

// Controller Callbacks ========================================================
void tglWings(); // Toggles the wings piston
void tglCataMode();  // Toggles the launch hight of the catapult
void cataInc();  // Raises the catapult speed by 5
void cataDec();  // Lowers the catapult speed by 5

#endif // GLOBALDEFINITIONS_H_