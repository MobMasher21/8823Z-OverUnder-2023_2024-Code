#include "../../../robotControl/Drivetrain/include/Drive.h"

namespace evAPI {
  extern Drive* threadReference;
  
  void hiddenOdoThreadFunction();  // function for odo thread

  void Drive::odoThreadFunction() {  // command only called by odo thread loop
    int positionChange = (leftTracker->readTrackerPosition(leftOdoTracker) + rightTracker->readTrackerPosition(rightOdoTracker)) / 2;
    int headingChange = turnSensor->rotation(deg);
    int robotHeading = turnSensor->heading(deg);
    leftAndRight arcDirection;
    if(leftTracker->readTrackerPosition(leftOdoTracker) > rightTracker->readTrackerPosition(rightOdoTracker)) {
      arcDirection = RIGHT;
    }
    if(leftTracker->readTrackerPosition(leftOdoTracker) < rightTracker->readTrackerPosition(rightOdoTracker)) {
      arcDirection = LEFT;
    }
    odoTracker.runMath(positionChange, robotHeading, headingChange, arcDirection);

    turnSensor->resetRotation();
    leftTracker->resetTrackerPosition(leftOdoTracker);
    rightTracker->resetTrackerPosition(rightOdoTracker);
  }

  void Drive::startOdoThread() {  // starts the odo tracking thread
    odoThread = new thread(hiddenOdoThreadFunction);
  }

  void hiddenOdoThreadFunction() {  // function for odo thread
    while(1) {
      threadReference->odoThreadFunction();
      vex::this_thread::sleep_for(20);
    }
  }
}  // namespace evAPI
