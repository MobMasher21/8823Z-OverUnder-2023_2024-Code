/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       odomCore.h                                                */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      26 Dec 2022                                               */
/*    Description:  Class for using odometry tracking with a robot.           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef __ODOMETRY_H__
#define __ODOMETRY_H__

#include "vex.h"

namespace evAPI
{
  /**
   * @brief A class for using odometry with a robot.
  */
  class odomCore
  {
    private:

    public:

      /** 
      * @brief The names for each encoder.
      */
      enum encoderNames 
      { 
        noEncoder = -1,
        leftEncoder = 0,
        rightEncoder = 1,
        backEncoder = 2
      };

      //CONFIGURATION

      /**
      * @brief Configures the encoders for a three encoder system.
      * @param leftEncoderPort The port the left encoder is in.
      * @param leftEncoderReversed If the left encoder is reversed.
      * @param rightEncoderPort The port the right encoder is in.
      * @param rightENcoderReversed If the right encoder is reversed.
      * @param backEncoderPort The port the back encoder is in.
      * @param backEncoderReversed If the back encoder is reversed.
      */
      void createEncoders(int leftEncoderPort, bool leftEncoderReversed, int rightEncoderPort,
        bool rightENcoderReversed, int backEncoderPort, bool backEncoderReversed);

      /**
      * @brief Configures the encoders for a three encoder system.
      * @param leftEncoderPort The port the left encoder is in.
      * @param leftEncoderReversed If the left encoder is reversed.
      * @param backEncoderPort The port the back encoder is in.
      * @param backEncoderReversed If the back encoder is reversed.
      */
      void createEncoders(int leftEncoderPort, bool leftEncoderReversed, int backEncoderPort,
        bool backEncoderReversed)
      { createEncoders(leftEncoderPort, leftEncoderReversed, backEncoderPort,
        backEncoderReversed, -1, false); }

      /**
       * @brief Controls the distance of the encoder wheels from the center of the robot and their diameter.
      */
      void configureEncoderWheels(double leftDistance, double rightDistance, double backDistance,
        double WheelDiameter);

      /**
       * @brief Controls the distance of the encoder wheels from the center of the robot and their diameter.
      */
      void configureEncoderWheels(double leftDistance, double backDistance,
        double WheelDiameter)
      { configureEncoderWheels(leftDistance, 0, backDistance, WheelDiameter); }

      void startingParameters(double xPos, double yPos, double angle);

      /**
       * @brief Starts the odometry tracking. ONLY CALL AFTER EVERYTHING ELSE HAS BEEN SET UP!
      */
      void startOdometry();

      //POSITION VALUES

      /**
       * @returns The X-Position of the robot.
      */
      double xPosition();

      /**
       * @returns The Y-Position of the robot.
      */
      double yPosition();

      /**
       * @returns The angle of the robot.
      */
      double angle();

      /**
       * @param encoder The desired encoder.
       * @return The value of the encoder.
      */
      double encoderAngle(encoderNames encoder);

      /**
       * @brief Forces te use of the inertial sensor for tracking.
       * @param stat A boolean value that sets the flag for always using the inertial sensor.
      */
      void useInertial(bool stat);

      bool usingInertial();
  };
}

#endif // __ODOMETRY_H__