#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "../evAPI/evAPIFiles.h"
#include "vex.h"
 
// Driver control settings -------------------------------------
// contorl buttons
#define CATA_FIRE_BUTTON ButtonR2
#define CATA_SET_BUTTON ButtonA
#define CATA_STOP_BUTTON ButtonX
#define CATA_SPEED_INC ButtonUp
#define CATA_SPEED_DEC ButtonDown
#define INTK_IN_BUTTON ButtonL1
#define INTK_OUT_BUTTON ButtonL2
#define WINGS_BUTTON ButtonR1
// driving vars
extern int cataSpeed;

// Select namespaces -------------------------------------------
using namespace vex;
using namespace evAPI;

// Global object declarations ----------------------------------
extern controller primaryController;  //vex controller object set to primary mode
extern controller secondaryController;  //vex controller object set to partner mode
extern competition Competition;  //vex competition objects to work with competition controller
extern AutoSelector UI;  //evAPI auto selector with screen buttons
extern Drive driveBase;  //evAPI smart drive base for moving whole robot
extern DriverBaseControl driveContorl;  //evAPI auto base contorl
extern digital_out wingPistons; //Wings

// Controller callbacks ----------------------------------------
void tglWings();  // Toggles the state of the wings.
void cataInc();  // Increments the catapult speed by 5.
void cataDec();  // Decrements the catapult speed by 5.

#endif // GLOBAL_H_