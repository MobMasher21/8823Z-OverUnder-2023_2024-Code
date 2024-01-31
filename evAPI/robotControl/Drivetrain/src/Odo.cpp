#include "../../../robotControl/Drivetrain/include/Drive.h"

namespace evAPI {
  extern Drive* threadReference;
  
  void hiddenOdoThreadFunction();  // function for odo thread

  void Drive::odoThreadCall() {  // command only called by odo thread loop

  }

  void hiddenOdoThreadFunction() {  // function for odo thread
    while(1) {
      threadReference->odoThreadCall();
      vex::this_thread::sleep_for(20);
    }
  }
}  // namespace evAPI
