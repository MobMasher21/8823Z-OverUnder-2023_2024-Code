#include "GlobalDeclarations.h"

void tglWings() { // Toggles the wings piston
  wingPistons.set(!wingPistons.value());
}

void tglCataMode() {  // Toggles the launch hight of the catapult
  if(cataLaunchMode == cataStates::HIGH_CATA) {
    cataLaunchMode = cataStates::LOW_CATA;
  } else {
    cataLaunchMode = cataStates::HIGH_CATA;
  }
}

void cataInc() {  // Raises the catapult speed by 5
  if(cataSpeed >= 100) {
    cataSpeed = 100;
  } else {
    cataSpeed += 5;
  }
}

void cataDec() {  // Lowers the catapult speed by 5
  if(cataSpeed <= 0) {
    cataSpeed = 0;
  } else {
    cataSpeed -= 5;
  }
}