#include "../include/OdoMath.h"

void OdoMath::setPosition(int xPos, int yPos) {  // sets the current robot position
  xPosition = xPos;
  yPosition = yPos;
}

void OdoMath::resetHeading() {  // resets the stored heading to 0
  previousHeading = 0
}

void OdoMath::runMath(int travalDistance, int robotHeading, int headingChage, leftAndRight arcDirection) {  // runs the odo math and updates the counters
  int dirMod;  // direction modifier for left and right arcs
  if(arcDirection == LEFT) dirMod = 1;
  if(arcDirection == RIGHT) dirMod = -1;
  
}

int OdoMath::getXPosition() {  // returns the robot x position
  return(xPosition);
}

int OdoMath::getYPosition() {  // returns the robot y position
  return(yPosition)
}
