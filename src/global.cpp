#include "global.h"

controller primaryController = controller(primary); 
controller secondaryController = controller(partner);
competition Competition = competition();
AutoSelector UI = AutoSelector();
Drive driveBase = Drive(blueGearBox);
DriverBaseControl driveContorl = DriverBaseControl(&primaryController, RCControl, &driveBase);