#include "../include/OdoMath.h"

namespace evAPI
{

  void OdoMath::setPosition(int xPos, int yPos) {  // sets the current robot position
    xPosition = xPos;
    yPosition = yPos;
  }

  void OdoMath::resetHeading() {  // resets the stored heading to 0
    previousHeading = 0;
  }

  void OdoMath::runMath(int travelDistance, int robotHeading, int headingChange, leftAndRight arcDirection) {  // runs the odo math and updates the counters
    int dirMod;  // direction modifier for left and right arcs
    if(arcDirection == LEFT) dirMod = 1;
    if(arcDirection == RIGHT) dirMod = -1;

    int dStart = previousHeading;  // Heading of the robot before the turn
    int dTurn = headingChange;  // The angle of the turn arc
    int dWorking = dTurn * dirMod;  // Sets the start heading to be the correct sign for right or left turn 
    int lArc = travelDistance;  // Length of the arc

    double tStart = (dStart - 90) * (M_PI / 180);  // Starting angle along arc circle
    double tArc = dWorking * (M_PI / 180);  // Overall angle of the arc
    double tSec = .5 * tArc;  // Angle of the secant line relative to the tangent lin on the turning arc of the circle
    double tTurn = (M_PI / 2) - (tSec + tStart);  // Angle of the secant line relative to the x-axis

    double r = lArc / tArc;  // Radius of the turn arc
    double rWorking = dirMod * r;  // Sets the radius to be the correct sign for the right or left turn

    double lSec = 2 * rWorking * sin(tArc / 2);  // Length of the secant line
    double lXDis = lSec * cos(tTurn);  // Length of the x vector
    double lYDis = lSec * sin(tTurn);  // Length of the y vector

    previousHeading = robotHeading;
    xPosition += lXDis;
    yPosition += lYDis;

  }

  int OdoMath::getXPosition() {  // returns the robot x position
    return(xPosition);
  }

  int OdoMath::getYPosition() {  // returns the robot y position
    return(yPosition);
  }

} // namespace evAPI