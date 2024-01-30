#ifndef __ODOMATH_H__
#define __ODOMATH_H__

#include <math.h>

class OdoMath {
  public:
    void setPosition(int xPos, int yPos);  // sets the current robot position
    void resetHeading();  // resets the stored heading to 0
    void runMath(int travalDistance, int robotHeading, int headingChage, leftAndRight arcDirection);  // runs the odo math and updates the counters
    int getXPosition();  // returns the robot x position
    int getYPosition();  // returns the robot y position

  private:
    int xPosition;  // coordinate of the robot x
    int yPosition;  // coordinate of the robot y
    int previousHeading;  // heading last time the math was run

};

#endif // __ODOMATH_H__