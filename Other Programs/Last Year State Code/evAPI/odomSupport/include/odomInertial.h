/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       odomInertial.h                                            */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      01 Jan 2023                                               */
/*    Description:  The inertial subclass used in evAPI's odometry.           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef __ODOMINERTIAL_H__
#define __ODOMINERTIAL_H__

#include "vex.h"

namespace evAPI
{
  class odomInertial
  {
    private:

      inertial * inertialSensor;

      bool Created = false;

    public:

      /**
       * @brief Configures an inertial sensor.
       * @param port The port the inertial sensor is in.
      */
      void createInertial(int port);

      void calibrate();

      /**
       * @brief Returns true while the inertial sensor is performing a requested recalibration, changing to false once recalibration has completed.
       * @return Returns true if inertial sensor is still calibrating.
      */
      bool isCalibrating(void);

      /**
        * @brief reset the heading of the sensor to 0
      */
      void resetHeading();

      /**
        * @brief reset the rotation angle of the sensor to 0
      */
      void resetRotation();

      /**
       * @brief set the inertial sensor heading to a new value
       * @param value The new heading for the inertial sensor
       * @param units The rotation unit for the angle
      */
      void setHeading( double value, rotationUnits units );

      /**
        * @brief set the inertial sensor rotation to angle
        * @param value The new absolute rotation angle for the inertial sensor
        * @param units The rotation unit for the angle
      */
      void setRotation( double value, rotationUnits units );

      /**
       * @brief Gets the angle (yaw angle) of the inertial sensor.
       * @return Returns a double that represents the unit value specified by the parameter of the inertial sensor.
       * @param units The measurement unit for the inertial device.
      */
      double angle( rotationUnits units = rotationUnits::deg );

      /**
       * @brief Gets the roll angle of the inertial sensor.
       * @return Returns a double that represents the unit value specified by the parameter of the inertial sensor.
       * @param units The measurement unit for the inertial sensor.
      */
      double roll( rotationUnits units = rotationUnits::deg );

      /**
       * @brief Gets the pitch angle of the inertial sensor.
       * @return Returns a double that represents the unit value specified by the parameter of the inertial sensor.
       * @param units The measurement unit for the inertial device.
      */
      double pitch( rotationUnits units = rotationUnits::deg );

      /**
       * @brief Gets the yaw angle of the inertial sensor.
       * @return Returns a double that represents the unit value specified by the parameter of the inertial sensor.
       * @param units The measurement unit for the inertial sensor.
      */
      double yaw( rotationUnits units = rotationUnits::deg );        

      /**
       * @brief Gets the heading (yaw angle as 0-360 deg) of the inertial sensor.
       * @return Returns a double that represents the unit value specified by the parameter of the inertial sensor.
       * @param units The measurement unit for the inertial sensor.
      */
      double heading( rotationUnits units = rotationUnits::deg );

      /**
       * @brief Gets the absolute angle (yaw angle without limits) of the inertial sensor.
       * @return Returns a double that represents the unit value specified by the parameter of the inertial sensor.
       * @param units The measurement unit for the inertial sensor.
      */
      double rotation( rotationUnits units = rotationUnits::deg );

      bool installed();

      /**
       * @returns True if an inertial object has been created.
      */
      bool wasCreated();
  };
}

#endif // __ODOMINERTIAL_H__