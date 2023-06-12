/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       odomPoint.cpp                                             */
/*    Authors:      Jayden Liffick / Cameron Barclay                          */
/*    Created:      01 Jan 2023                                               */
/*    Description:  The point subclass for evAPI's odometry.                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../../odomSupport/include/odomMain.h"
#include "../../Common/include/arduinoDef.h"

namespace evAPI
{
  bool odomPoint::findDir(double startingAngle, double endingAngle) 
  {
    double leftDegs;
    double rightDegs;
    double x;
  
    x = startingAngle + 360; //Left turn
  
    if(x - endingAngle > 360) 
    { x = startingAngle; }
  
    leftDegs = x - endingAngle;
  
    x = endingAngle + 360; //Right turn
  
    if(x - startingAngle > 360) 
    { x = endingAngle; }
  
    rightDegs = x - startingAngle;
  
    if(leftDegs > rightDegs) //Return lines
    { return RIGHT; } 
  
    return LEFT;
  }
  
  void odomPoint::createPoint(double x, double y, pointType pType, int triggerRad, int nextPoint)
  {
    if(pointCount < MAX_POINTS)
    {
      pointCount++;
  
      points[pointCount] = new odometryPoints; //Creates the new point
      points[pointCount]->xPos = x; //Applies properties to the point
      points[pointCount]->yPos = y;
      points[pointCount]->hasAngle = false;
      points[pointCount]->triggerRadius = triggerRad;
      points[pointCount]->thisPointType = pType;
    }
  }
  
  void odomPoint::createPoint(double x, double y, double angle, pointType pType, int triggerRad , int nextPoint)
  {
    if(pointCount < MAX_POINTS)
    {
      pointCount++;
  
      points[pointCount] = new odometryPoints; //Creates the new point
      points[pointCount]->xPos = x; //Applies properties to the point
      points[pointCount]->yPos = y;
      points[pointCount]->angle = angle;
      points[pointCount]->hasAngle = true;
      points[pointCount]->triggerRadius = triggerRad;
      points[pointCount]->thisPointType = pType;
    }
  }
  
  double odomPoint::returnPointX(int point)
  { return points[point]->xPos; }
  
  double odomPoint::returnPointY(int point)
  { return points[point]->yPos; }
  
  double odomPoint::returnPointAngle(int point)
  { 
    if(pointHasAngle(point))
    { return points[point]->angle; }
  
    return 0;
  }
  
  bool odomPoint::pointHasAngle(int point)
  { return points[point]->hasAngle; }
  
  double odomPoint::distanceToPoint(int point)
  { return distanceToPoint(Odometry.Points.returnPointX(point), Odometry.Points.returnPointY(point)); }
  
  double odomPoint::distanceToPoint(double x, double y) //https://www.desmos.com/calculator/bexeoat70z
  { return (sqrt((sq(x - Odometry.Core.xPosition())) + sq((y - Odometry.Core.yPosition())))); }
  
  double odomPoint::angleToPoint(int point)
  { return angleToPoint(points[point]->xPos, points[point]->yPos); }
  
  double odomPoint::angleToPoint(double x, double y) //https://www.desmos.com/calculator/bexeoat70z
  {
    double robotPointDistance = distanceToPoint(x, y); //The distance to the target point.
  
    double robotXPosition = Odometry.Core.xPosition();
    double robotYPosition = Odometry.Core.yPosition();
  
    double robotAngle;

    if(Odometry.Core.usingInertial()) //Converts robot angle to radians
    { robotAngle = radians(Odometry.Inertial.angle()); }

    else
    { robotAngle = radians(Odometry.Core.angle()); }
    

    double turningAngle;
  
    //Facing direction point
    double facingPointXPos = cos(robotAngle) + robotXPosition; 
    double facingPointYPos = sin(robotAngle) + robotYPosition;
  
    //A form of the law of cosines is used to return the angle between the direction the robot is facing.
    turningAngle = degrees(acos(((sq((x - facingPointXPos)) + sq((y - facingPointYPos))) - 1 
      - sq(robotPointDistance)) / (-2 * robotPointDistance)));
  
    /* double rotationMatrix[2][2] = {
      {(cos(-robotAngle), (-sin(-robotAngle)))},
      {(sin(-robotAngle)), (cos(-robotAngle))}
    };
  
    double targetPositionMatrix[2][1] = {
      {x - robotXPosition},
      {y - robotYPosition}
    }; */
  
    double outputMatrix[2][1];

    outputMatrix[0][0] = x*cos(turningAngle) - y*sin(turningAngle);
    outputMatrix[1][0] = x*sin(turningAngle) + y*cos(turningAngle);
    
    if(outputMatrix[1][0] >= 0) //Needs to turn left
    { return -turningAngle; }
  
    return turningAngle; //Needs to turn right
  }
  
  bool odomPoint::isTriggeringPoint(int point) //https://www.desmos.com/calculator/13uba6ynnb
  {
    if(sq(points[point]->xPos - Odometry.Core.xPosition()) + sq(points[point]->yPos
      - Odometry.Core.yPosition()) <= sq(points[point]->triggerRadius))
    { return true; }
  
    return false;
  }
  
  int odomPoint::returnPointType(int point)
  { return points[point]->thisPointType; }
  
  int odomPoint::totalPoints()
  { return pointCount; }
  
  double odomPoint::getDistanceBetweenPoints(double X1, double Y1, double X2, double Y2)
  { return (sqrt(sq((X1 - X2)) + sq((Y1 - Y2)))); }
  
  double odomPoint::angleToTargetAngle(double targetAngle)
  {
    double robotAngleRadians = radians(Odometry.Core.angle());
    double targetAngleRadians = radians(targetAngle);
    double finalAngle;
    #define d1 3
    double d2;
  
    double facingX = d1 * cos(robotAngleRadians);
    double facingY = d1 * sin(robotAngleRadians);
    double targetX = d1 * cos(targetAngleRadians);
    double targetY = d1 * sin(targetAngleRadians);
  
    d2 = sqrt(sq(targetX - facingX) + sq(targetY - facingY));
  
    finalAngle = degrees(acos((((d2 * d2) - (2 * d1 * d1)) / ((-2) * d1 * d1))));
  
    if(findDir(degrees(robotAngleRadians), degrees(targetAngleRadians)) == RIGHT)
    { return finalAngle; }
  
    return -finalAngle;
  }
  #undef d1
}