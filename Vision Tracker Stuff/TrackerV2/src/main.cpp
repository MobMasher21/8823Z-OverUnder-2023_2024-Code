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

//used to calculate single eye distance using downward exponential curve
//desmos calculator link https://www.desmos.com/calculator/g95kkfwprb
//format y=a^(-(x+b))+c
#define DIS_FUNC_A 1.05589
#define DIS_FUNC_B -95.6794
#define DIS_FUNC_C 9.0166
#define DISTANCE_FUNCTION(BALL_X_DIM) (pow(DIS_FUNC_A, -(BALL_X_DIM + DIS_FUNC_B)) + DIS_FUNC_C)
#define AVERAGE_COUNT 100

enum directions {
  LEFT,
  RIGHT
};

int ballXPos;
int ballYPos;
int ballXDim;
int ballYDim;

double ballDistance;
int distanceCount;

bool lockedOn;
bool offDirection;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  fflush(stdout);
  while (true) {

    //take snapshot of sensor looking for green
    BallVision.takeSnapshot(BALL_GREEN);

    //gets the location and size of the biggest green object
    if (BallVision.objectCount > 0) {
      ballXPos = BallVision.objects[0].centerX;
      ballYPos = BallVision.objects[0].centerY;
      ballXDim = BallVision.objects[0].width;
      ballYDim = BallVision.objects[0].height;
    }
    
    //look to see if the robot is straight on, to far left, or to far right
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

    //looks to see which direction the robot needs to move and spins motors to move that way
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

    //sets brain color and vision sensor led color to signify ball state
    if(BallVision.objectCount > 0) {
      if(lockedOn) {
        Brain.Screen.setFillColor(blue);
        BallVision.setLedColor(0, 0, 255);
      } else {
        if(offDirection == LEFT) {
          Brain.Screen.setFillColor(green);
          BallVision.setLedColor(0, 255, 0);
        }
        if(offDirection == RIGHT) {
          Brain.Screen.setFillColor(red);
          BallVision.setLedColor(255, 0, 0);
        }
      }
    } else {
      BallVision.setLedColor(0, 0, 0);
    }

    //calculate distance to ball over an average of many snaps
    ballDistance = ballDistance + DISTANCE_FUNCTION(ballXDim);
    if(distanceCount == AVERAGE_COUNT) {
      ballDistance = ballDistance / AVERAGE_COUNT;
    
      printf("ball distance = %f\n", ballDistance);

      distanceCount = 0;
      ballDistance = 0;
    }
    distanceCount++;

    //prints ball data in terminal and prints color signature on brain screen
    //printf("%i, %i, %i, %i\n", ballXPos, ballYPos, ballXDim, ballYDim);
    if (BallVision.objectCount > 0) {
      ballXPos = BallVision.objects[0].originX;
      ballYPos = BallVision.objects[0].originY;
    }
    Brain.Screen.clearScreen();
    Brain.Screen.setPenColor(black);
    Brain.Screen.drawRectangle(ballXPos, ballYPos, ballXDim, ballYDim);

    wait(5, msec);
  }
}
