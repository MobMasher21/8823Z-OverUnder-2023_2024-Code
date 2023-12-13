#include "global.h"

// Driver control settings -------------------------------------
// driving vars
int cataSpeed = 75;

brain Brain;

// Global object definitions
controller primaryController = controller(primary); 
controller secondaryController = controller(partner);
competition Competition = competition();
AutoSelector UI = AutoSelector();
Drive driveBase = Drive(blueGearBox);
DriverBaseControl driveContorl = DriverBaseControl(&primaryController, RCControl, &driveBase);
digital_out wingPistons = digital_out(Brain.ThreeWirePort.A);

// Controller callbacks
void tglWings() {  // Toggles the state of the wings.
  wingPistons.set(!wingPistons.value());
}

void cataInc() {  // Increments the catapult speed by 5.
  if(cataSpeed >= 100) {
    cataSpeed = 100;
  } else {
    cataSpeed += 5;
  }
}

void cataDec() {  // Decrements the catapult speed by 5.
  if(cataSpeed <= 0) {
    cataSpeed = 0;
  } else {
    cataSpeed -= 5;
  }
}