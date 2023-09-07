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
#include "BallVisionConfig.h"

using namespace vex;

#define LOCK_RANGE 40
#define LOCK_TOP (158 + LOCK_RANGE / 2)
#define LOCK_BOTTOM (158 - LOCK_RANGE / 2)

enum directions {
  LEFT,
  RIGHT
};

int ballXPos;
int ballYPos;
int ballXDim;
int ballYDim;

bool lockedOn;
bool offDirection;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  fflush(stdout);
  while (true) {
    BallVision.takeSnapshot(BALL_GREEN);
    if (BallVision.objectCount > 0) {
      ballXPos = BallVision.objects[0].centerX;
      ballYPos = BallVision.objects[0].centerY;
      ballXDim = BallVision.objects[0].width;
      ballYDim = BallVision.objects[0].height;
    }
    
    if(ballXPos >= LOCK_BOTTOM && ballXPos <= LOCK_TOP) {
      lockedOn = 1;
    } else {
      lockedOn = 0;
      if(ballXPos > LOCK_TOP) {
        offDirection = LEFT;
      }
      if(ballXPos < LOCK_BOTTOM) {
        offDirection = RIGHT;
      }
    }

    if(BallVision.objectCount > 0) {
      if(lockedOn) {
        leftMotor.spin(fwd, 20, pct);
        rightMotor.spin(fwd, 20, pct);
      } else {
        if(offDirection == LEFT) {
          leftMotor.spin(fwd, 5, pct);
          rightMotor.spin(fwd, -5, pct);
        }
        if(offDirection == RIGHT) {
          leftMotor.spin(fwd, -5, pct);
          rightMotor.spin(fwd, 5, pct);
        }
      }
    } else {
      leftMotor.stop();
      rightMotor.stop();
    }

    if(lockedOn) {
      Brain.Screen.setFillColor(blue);
    } else {
      if(offDirection == LEFT) {
        Brain.Screen.setFillColor(green);
      }
      if(offDirection == RIGHT) {
        Brain.Screen.setFillColor(red);
      }
    }

    printf("%i, %i, %i, %i\n", ballXPos, ballYPos, ballXDim, ballYDim);
    if (BallVision.objectCount > 0) {
      ballXPos = BallVision.objects[0].originX;
      ballYPos = BallVision.objects[0].originY;
    }
    Brain.Screen.clearScreen();
    Brain.Screen.setPenColor(red);
    Brain.Screen.drawRectangle(ballXPos, ballYPos, ballXDim, ballYDim);

    wait(5, msec);
  }
}
