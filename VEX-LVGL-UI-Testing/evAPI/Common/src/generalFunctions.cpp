/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       util.cpp                                                  */
/*    Author:       Jackson Area Robotics                                     */
/*    Created:      ???                                                       */
/*    Description:  Various functions.                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <math.h>
#include "../include/constantObjects.h"
#include "../include/generalFunctions.h"

namespace evAPI
{
  float reduce_0_to_360(float angle) {
    while(!(angle >= 0 && angle < 360)) {
      if( angle < 0 ) { angle += 360; }
      if(angle >= 360) { angle -= 360; }
    }
    return(angle);
  }

  float reduce_negative_180_to_180(float angle) {
    while(!(angle >= -180 && angle < 180)) {
      if( angle < -180 ) { angle += 360; }
      if(angle >= 180) { angle -= 360; }
    }
    return(angle);
  }

  float reduce_negative_90_to_90(float angle) {
    while(!(angle >= -90 && angle < 90)) {
      if( angle < -90 ) { angle += 180; }
      if(angle >= 90) { angle -= 180; }
    }
    return(angle);
  }

  float to_volt(float percent){
    return(percent*12.0/100.0);
  }

  robotMode getCompetitionStatus()
  {
    if(!Competition.isEnabled())
    {
      return robotMode::disabled;
    }

    else if(Competition.isDriverControl())
    {
      return robotMode::driverControl;
    }

    return robotMode::autonomousControl;
  }

  bool isConnectToField()
  {
    return Competition.isCompetitionSwitch() || Competition.isFieldControl();
  }
}