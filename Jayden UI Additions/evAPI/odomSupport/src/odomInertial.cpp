/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       odomInertial.h                                            */
/*    Authors:      Jayden Liffick                                            */
/*    Created:      01 Jan 2023                                               */
/*    Description:  The inertial subclass used in evAPI's odometry.           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../../odomSupport/include/odomInertial.h"
#include "../../Common/include/robotStatus.h"
#include "../../Common/include/evNamespace.h"

namespace evAPI
{
  void odomInertial::createInertial(int port)
  {
    inertialSensor = new inertial(smartPortLookupTable[port]);
    Created = true;
  }

  void odomInertial::calibrate()
  { inertialSensor->calibrate(); }

  bool odomInertial::isCalibrating()
  { return inertialSensor->isCalibrating(); }

  void odomInertial::resetHeading()
  { inertialSensor->resetHeading(); }

  void odomInertial::resetRotation()
  { inertialSensor->resetRotation(); }

  void odomInertial::setHeading(double value, rotationUnits units)
  { inertialSensor->setHeading(value, units); }

  void odomInertial::setRotation(double value, rotationUnits units)
  { inertialSensor->setRotation(value, units); }

  double odomInertial::angle(rotationUnits units)
  { return inertialSensor->angle(units); }

  double odomInertial::roll(rotationUnits units)
  { return inertialSensor->roll(units); }

  double odomInertial::pitch(rotationUnits units)
  { return inertialSensor->pitch(units); }

  double odomInertial::yaw(rotationUnits units)
  { return inertialSensor->yaw(units); }

  double odomInertial::heading(rotationUnits units)
  { return inertialSensor->heading(units); }

  double odomInertial::rotation(rotationUnits units)
  { return inertialSensor->rotation(units); }

  bool odomInertial::installed()
  { return inertialSensor->installed(); }

  bool odomInertial::wasCreated()
  { return Created; }
}