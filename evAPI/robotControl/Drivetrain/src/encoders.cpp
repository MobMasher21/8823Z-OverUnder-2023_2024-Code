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


}