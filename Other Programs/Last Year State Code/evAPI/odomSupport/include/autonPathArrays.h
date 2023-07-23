/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autonPathArrays.h                                         */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      ?? Jan 2023                                               */
/*    Description:  The paths used in odometry with evAPI.                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef __AUTONPATHS_H__
#define __AUTONPATHS_H__

/*
  Array Format:

  double arrayNameHere[2][MAX_LINE_POINTS+3] = {
    {Number of points, Turning Angle, Turn when Complete, Point X Values...}
    {Driving Speed,    Turning Speed, Unused,             Point Y Values...}
  };
*/

namespace evAPI
{
  #define MAX_LINE_POINTS 10

  struct autonPathArrays
  {
    double testPath[2][MAX_LINE_POINTS+3] = {
     {5,  90, 1, /*X Cords -> */ 10, 20, 30, 50, 50},
     {75, 45, 5, /*Y Cords -> */ 10, 20, 30, 40, 50}
    };

    double redLowGoal1[2][MAX_LINE_POINTS+3] = {
      {3,  0,  0, /*X Cords -> */ 10, 20, 40},
      {75, 60, 0, /*Y Cords -> */ 10, 20, 20}
    };

    double redLowGoal2[2][MAX_LINE_POINTS+3] = {
      {3,  0,  0, /*X Cords -> */ 10, 20, 20},
      {75, 60, 0, /*Y Cords -> */ 10, 20, 40}
    };
  };

  extern autonPathArrays autonPaths;
}

#endif // __AUTONPATHS_H__