/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       odomPoint.h                                               */
/*    Authors:      Jayden Liffick / Cameron Barclay                          */
/*    Created:      01 Jan 2023                                               */
/*    Description:  The point subclass for evAPI's odometry.                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef __ODOMPOINT_H__
#define __ODOMPOINT_H__

#include "../../odomSupport/include/autonPathArrays.h"

namespace evAPI
{
  #define MAX_POINTS 256

  #define DEFAULT_TRIGGER_RADIUS 2

  class odomPoint
  {
    public:

      /**
       * @brief The type of point.
       * "directPoint" is going to the exact position of the point.
       * "guide point" is used as a guide for the robot.
      */
      enum pointType
      {
        directPoint = 0,
        guidePoint = 1,
        endPoint = 2
      };

      enum leftAndRight {
        LEFT = 0,
        RIGHT = 1
      };

    private:

    /**
       * @brief The number of points currently in use.
      */
      int pointCount;

      /**
      * @brief Stores all the the points that can be used in odometry.
      */
      struct odometryPoints
      { 
        double xPos;
        double yPos;
        double angle;
        bool hasAngle;
        int triggerRadius;
        pointType thisPointType;
      };

      odometryPoints * points[MAX_POINTS];

      /**
       * @author Cameron Barclay
       * @brief Finds the optional direction to turn between two angles.
       * @param startingAngle The starting angle you wants to turn from.
       * @param endingAngle The ending angle you want to turn to.
       * @returns LEFT or RIGHT depending on the optimal direction.
      */
      bool findDir(double startingAngle, double endingAngle);

    public:

      /**
       * @brief Creates a new point that can be used in odometry tracking.
       * @param x The X-location of the point.
       * @param y The Y-location of the point.
       * @param triggerRad An optional paramater that controls the radius of the triggering zone.
      */
      void createPoint(double x, double y, pointType pType = directPoint,
        int triggerRad = DEFAULT_TRIGGER_RADIUS, int nextPoint = -1);

      /**
       * @brief Creates a new point that can be used in odometry tracking.
       * @param x The X-location of the point.
       * @param y The Y-location of the point.
       * @param angle An angle referenced with the point.
      */
      void createPoint(double x, double y, double angle, pointType pType = directPoint, 
        int triggerRad = DEFAULT_TRIGGER_RADIUS, int nextPoint = -1);

      /**
       * @returns The X-position of the specified point.
      */
      double returnPointX(int point);

      /**
       * @returns The Y-position of the specified point.
      */
      double returnPointY(int point);

      /**
       * @returns The angle of the specified point.
      */
      double returnPointAngle(int point);

      /**
       * @returns True if the point has an angle attached to it. False if it doesn't.
      */
      bool pointHasAngle(int point);

      /**
       * @returns The distance from the robot to a point.
      */
      double distanceToPoint(int point);

      /**
       * @returns The distance from the robot to a specified location.
       * @param x The X-position of the location.
       * @param y The Y-position of the location.
      */
      double distanceToPoint(double x, double y);

      /**
       * @returns The angle from the robot to a point.
      */
      double angleToPoint(int point);

      /**
       * @returns The angle from the robot to a specified location.
       * @param x The X-position of the location.
       * @param y The Y-position of the location.
      */
      double angleToPoint(double x, double y);

      /**
       * @returns True if the corresponding point is being triggered by the robot.
      */
      bool isTriggeringPoint(int point);

      /**
       * @returns The type of point.
      */
      int returnPointType(int point);

      /**
       * @returns The total amount of points.
      */
      int totalPoints();

      /**
       * @brief Gets the distance between two different points on the feild.
       * @param point1 The first point.
       * @param point2 The second point.
       * @returns The distance between the two points.
      */
      double getDistanceBetweenPoints(int point1, int point2)
      { return getDistanceBetweenPoints(returnPointX(point1), returnPointY(point1), returnPointX(point2), 
        returnPointY(point2)); }

      /**
       * @brief Gets the distance between two different points on the feild.
       * @param X1 The X-Position of the first point.
       * @param Y1 The Y-Position of the first point.
       * @param X2 The X-Position of the second point.
       * @param Y2 The Y-Position of the second point.
       * @returns The distance between the two points.
      */
      double getDistanceBetweenPoints(double X1, double Y1, double X2, double Y2);

      /**
       * @brief Returns the angle needed to turn to the targetAngle
       * @param targetAngle The target angle that the robot needs to turn to
       * @returns The angle needed to turn to the targetAngle
      */
      double angleToTargetAngle(double targetAngle);
  };
}

#endif // __ODOMPOINT_H__