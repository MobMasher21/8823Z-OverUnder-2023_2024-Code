/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\19.cameron.barclay                               */
/*    Created:      Wed May 10 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor            motor         20              
// rightMotor           motor         11              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "VisionConfig.h"
#include "../VisionTracker/VisionTracker.h"

using namespace vex;

#define DIS_FUNC_A 1.03553
#define DIS_FUNC_B -136.357
#define DIS_FUNC_C 8.69977

VisionTracker ballTracker(&BallVision, &BALL_GREEN);
double distanceToBall;
void ballTrackingTask( void ) {
  while(1) {
    ballTracker.trackObject();
    distanceToBall = ballTracker.returnAverageDistance();
    vex::this_thread::sleep_for(20);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!

  vexcodeInit();
  fflush(stdout);

  ballTracker.setLockRange(20);
  ballTracker.setupDistanceMath(DIS_FUNC_A, DIS_FUNC_B, DIS_FUNC_C);
  ballTracker.tglDebugMode(false);
  ballTracker.tglLEDIndicator(true);
  ballTracker.tglScreenIndicator(true);
  ballTracker.tglDistanceCalculation(true);
  vex::thread trackBall(ballTrackingTask);

  while (true) {

    //looks to see which direction the robot needs to move and spins motors to move that way
    if(ballTracker.objectCount > 0) {
      if(ballTracker.isLocked) {
        leftMotor.spin(fwd, 40, pct);
        rightMotor.spin(fwd, 40, pct);
      } else {
        if(ballTracker.directionOff == ballTracker.LEFT) {
          leftMotor.spin(fwd, 5, pct);
          rightMotor.spin(fwd, -5, pct);
        }
        if(ballTracker.directionOff == ballTracker.RIGHT) {
          leftMotor.spin(fwd, -5, pct);
          rightMotor.spin(fwd, 5, pct);
        }
      }
    } else {
      leftMotor.stop();
      rightMotor.stop();
    }

    wait(50, msec);
  }
}
