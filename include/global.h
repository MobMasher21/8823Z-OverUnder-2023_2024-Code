#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "../evAPI/evAPIFiles.h"
#include "vex.h"
 
// Select namespaces
using namespace vex;
using namespace evAPI;

//Setup global objects
extern controller primaryController;  //vex controller object set to primary mode
extern controller secondaryController;  //vex controller object set to partner mode
extern competition Competition;  //vex competition objects to work with competition controller
extern AutoSelector UI;  //evAPI auto selector with screen buttons
extern Drive driveBase;  //evAPI smart drive base for moving whole robot
extern DriverBaseControl driveContorl;  //evAPI auto base contorl

#endif // GLOBAL_H_