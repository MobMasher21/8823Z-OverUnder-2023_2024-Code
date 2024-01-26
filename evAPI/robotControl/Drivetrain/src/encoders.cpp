#include "../../../robotControl/Drivetrain/include/Drive.h"

namespace evAPI {
  //======================================== private =============================================
  /****** encoders ******/
  void Drive::leftFullReset() {  //resets all position data about left encoder
    leftTracker->resetAll();
  }

  void Drive::rightFullReset() {  //resets all position data about right encoder
    rightTracker->resetAll();
  }

  //======================================== private =============================================
  /****** encoders ******/
  double Drive::getBackPosition(rotationUnits units) {    //get the position of the back side on motor or rotation sensor
    if(backEncoder) {
      return(backEncoder->position(units));
    } else {
      return(0);
    }
  }

  void Drive::resetBackPosition() {    //resets position of back encoder to 0
    if(backEncoder) {
      backEncoder->resetPosition();
    }
  }

}